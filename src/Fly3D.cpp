#include <iostream>
#include <random>
#include "Vector3D.h"
#include "Fly3D.h"

using namespace std;

Fly3D::Fly3D(const Vector3d<double>& position, const int& index, Arena3D* arena ) : r(position), v(Vector3d<double>(0,0,0)), v_pref(Vector3d<double>(0,0,0)), a(Vector3d<double>(0,0,0)), angle(0.0), index(index), arena(arena), room(arena->GetRoomFromPosition(position))
    , Fint(Vector3d<double>(0,0,0)), Ffric(Vector3d<double>(0,0,0)), Fres(Vector3d<double>(0,0,0)), Fnoise(Vector3d<double>(0,0,0)), rcog(100.0), timeonfood(0.0){

    this->GenerateNewAim();
    }

Fly3D::Fly3D(const double& x, const double& y, const double& z, const int& index, Arena3D* arena) : r(Vector3d<double>(x, y, z)), v(Vector3d<double>(0,0,0)), v_pref(Vector3d<double>(0,0,0)), a(Vector3d<double>(0,0,0)), angle(0.0), index(index), arena(arena), room(arena->GetRoomFromPosition(x, y, z))
    , Fint(Vector3d<double>(0,0,0)), Ffric(Vector3d<double>(0,0,0)), Fres(Vector3d<double>(0,0,0)), Fnoise(Vector3d<double>(0,0,0)), rcog(100.0), timeonfood(0.0){

    this->GenerateNewAim();
    }

Fly3D::Fly3D(const int& room, const int& index, Arena3D* arena) : v(Vector3d<double>(0,0,0)), v_pref(Vector3d<double>(0,0,0)), a(Vector3d<double>(0,0,0)), angle(0.0), index(index), arena(arena)
    , Fint(Vector3d<double>(0,0,0)), Ffric(Vector3d<double>(0,0,0)), Fres(Vector3d<double>(0,0,0)), Fnoise(Vector3d<double>(0,0,0)), rcog(100.0), timeonfood(0.0){
    
    if(this->arena != nullptr && room < this->arena->GetNbWalls() && room >= 0){
        r = this->arena->GetRoomCenter(room);
        this->room = room;
    }
    this->GenerateNewAim();
}


int Fly3D::GetRoom() const{ return this->room;}


double Fly3D::GetAngle() const{ return this->angle;}

Vector3d<double> Fly3D::GetPosition() const{ return this->r;}

Vector3d<double> Fly3D::GetVelocity() const{ return this->v;}

Vector3d<double> Fly3D::GetVelocitypref() const{ return this->v_pref;}

Vector3d<double> Fly3D::GetFres() const{ return this->Fres;}

Vector3d<double> Fly3D::GetAim() const{ return this->aim;}

void Fly3D::SetAim(const Vector3d<double>& point){ this->aim = point;}

void Fly3D::SetAim(const double& x, const double& y, const double& z){ this->aim = Vector3d<double>(x, y, z);}

void Fly3D::GenerateNewAim(){
    // Random number generator initialization
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::normal_distribution<double> Gauss(0.0, 50.0); //or rcog/2
    std::uniform_real_distribution<double> Uniform(-rcog,rcog);
    // New aim generation
    Vector3d<double> dr;
    if(arena->OnFood(room)){ aim = arena->GetRoomCenter(room);}
    else{
        do{
            double x(Uniform(gen));
            double y(Uniform(gen));
            double z(Uniform(gen));
            dr = Vector3d<double>(x, y, z);
        } while (!arena->PointIsInside(r + dr) && EuclideanNorm(dr) > rcog);
        this->aim = r + dr;
    }
    // std::cout<<"Aim :"<<aim.x<<" ; "<<aim.y<<" ; "<<aim.z<<" "<<arena->GetRoomFromPosition(aim)<<" "<<arena->PointIsInside(aim)<<"\n";
    // std::cout<<" pos : "<<r.x<<" ; "<<r.y<<" ; "<<r.z<<"\n";

}

void Fly3D::UpdateAim(const double& dt){
    if(EuclideanNorm(r - aim) <= EuclideanNorm(v_pref) * dt * 2.5|| EuclideanNorm(r - aim) > rcog){
        this->GenerateNewAim();
    }
    if(arena->OnFood(room)){
        this->GenerateNewAim();
    }
}

void Fly3D::Update(const double& dt){
    // Update reponse to environment
    this->UpdateFres();
    // Update preferred velocity
    this->UpdateVpref(dt);
    // Update velocity
    this->UpdateV(dt);
    // Update angle
    this->UpdateAngle();
    // Update position
    this->UpdatePosition(dt);
    // Update aim
    this->UpdateAim(dt);
    // Update room of fly
    this->UpdateRoom();
    // Update time of food
    this->UpdateTimeOmFood(dt);
}

void Fly3D::UpdateAngle(){
    if(this->v != Vector3d<double>(0.0, 0.0, 0.0)){
        Vector3d<double> orient(this->r + this->v);
        Vector3d<double> uvec(1.0, 0.0, 0.0);
        uvec+= this->r;
        this->angle = atan2(this->v.y, this->v.x);
    }

}

void Fly3D::UpdateFres(){
    Vector3d<double> rie(aim - r);
    // Formula : Fres = Xres * H(rcog - |rie|) * (se * rie/|rie| * R(n, theta) - (1 - se) * rie / |rie|)
    if(arena->OnFood(room)){ 
        double rcog_ = 1000.0;
        Fres = 10.0 * std::max(0.0, (rcog_ - EuclideanNorm(rie)) / fabs(rcog_ - EuclideanNorm(rie))) * (rie/EuclideanNorm(rie)); 
    }
    else{
        Fres = 100 * std::max(0.0, (rcog - EuclideanNorm(rie)) / fabs(rcog - EuclideanNorm(rie))) * (rie/EuclideanNorm(rie));
    }
}

void Fly3D::UpdateVpref(const double& dt){
    v_pref = v + Fres * dt;
}

void Fly3D::UpdateV(const double& dt){
    v = v_pref;
    // If v_pref norm exceeds max observed fly speed
    if(EuclideanNorm(v) > 25) v *= 25 / EuclideanNorm(v);
}

void Fly3D::UpdatePosition(const double& dt){
    Vector3d<double> new_r (r + v * dt);
    if(arena->AllowMove(r, new_r)){ r = new_r;}
    else if(arena->OnFood(room)){ GenerateNewAim();}
    else{GenerateNewAim();}

    // std::cout<<"Pos : "<<r.x<<" ; "<<r.y<<" ; "<<r.z<<"  "<<arena->GetRoomFromPosition(r)<<"\n";
}

void Fly3D::UpdateRoom(){ room = arena->GetRoomFromPosition(r);}


double Fly3D::GetTimeOnFood() const { return timeonfood;} 

void Fly3D::UpdateTimeOmFood(const double& dt){
    if(arena->OnFood(room)){ timeonfood+= dt;}}
