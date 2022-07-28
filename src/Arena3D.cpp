#include <iostream>
#include <cmath>
#include "Vector3D.h"
#include "Wall.h"
#include "Food.h"
#include "Arena3D.h"

using namespace std;

Arena3D::Arena3D(const Vector3d<double>& c, const double& r, const double& h, int nb_walls, const int& nb_ent, const double& w_width) : center(c), radius(r), height(fabs(h)){
    food = nullptr;

    //If nb of walls is enough
    if(nb_walls > 1){
        std::cout << "---Wall Building---" <<"\n";
        this->BuildWalls(nb_walls, nb_ent, w_width);
        std::cout << endl;

        std::cout<<"---End Wall Building---\n\n";
        std::cout << "Walls Built / Nb walls : " << this->walls.size()<<"\n\n";
        
        Vector3d<double> uvec(1.0, 0.0, 0.0);
        // Fill lists
        for(int i = 0; i<this->GetNbWalls(); i++){
            // Use diagonal of the rectangle to avoid weird collisions
            Vector3d<double> wvec = this->walls[i].GetCoord()[2]-this->walls[i].GetCoord()[0];
            // Nullify z component
            wvec.z = 0.0;

            double cos_ = DotProduct(uvec, wvec) / (EuclideanNorm(uvec) * EuclideanNorm(wvec));
            double sin_ = CrossProduct(uvec, wvec).z / (EuclideanNorm(uvec) * EuclideanNorm(wvec));
            this->walls_cos.push_back(cos_);
            this->walls_sin.push_back(sin_);
        }
    }    
}


Arena3D::Arena3D(const double& c1, const double& c2, const double& c3, const double& r, const double& h, int nb_walls, const int& nb_ent, const double& w_width) : center(Vector3d<double>(c1, c2, c3)), radius(r), height(fabs(h)){
    food = nullptr;

    //If nb of walls is enough
    if(nb_walls > 1){
        std::cout << "Wall Building ... " <<"\n";
        this->BuildWalls(nb_walls, nb_ent, w_width);
        std::cout << endl;
    }


}



void Arena3D::BuildWalls(int nb_walls, const int& nb_ent, const double& w_width){
    
    if(nb_walls == 1) nb_walls = 0;

    for(int i = 0; i < nb_walls; i++){

            std::cout << endl;

            Vector3d<double> c1(this->center.x, this->center.y, this->center.z - height/2.0);
            Vector3d<double> c2(this->center.x + this->radius * cos(i * 2 * M_PI / nb_walls), this->center.y + this->radius * sin(i * 2 * M_PI / nb_walls), c1.z);
            Vector3d<double> c3(c2.x + w_width * cos(i * 2 * M_PI / nb_walls + M_PI_2), c2.y + w_width * sin(i * 2 * M_PI / nb_walls + M_PI_2), c1.z);
            Vector3d<double> c4(this->center.x + w_width * cos(i * 2 * M_PI / nb_walls + M_PI_2), this->center.y + w_width * sin(i * 2 * M_PI / nb_walls + M_PI_2), c1.z);
            
            this->walls.push_back(Wall(c1, c2, c3, c4, this->GetHeight(), nb_ent, this));
            std::cout << " Wall coordinates : " << c1 << c2 << c3 << c4 << " ";
            std::cout <<" Angle "<< i * 2 * M_PI / nb_walls * 180 / M_PI <<" deg "<<"Center "<<walls[i].GetCenter()<<"\n";
        }

}

int Arena3D::GetRoomFromPosition(const Vector3d<double>& point){

    
    // Unitary vector of comparison
    Vector3d<double> uvec(1.0, 0.0, 0.0);
    // Position vector
    Vector3d<double> vec_ = point - this->center;
    // Nullify z component
    vec_.z = 0.0;
    
    // If there are no walls
    if(this->GetNbWalls() == 0) return 0;

    // Point outside arena
    if(sqrtf(vec_.x * vec_.x + vec_.y * vec_.y)>= this->radius || (point.z <= fmin(center.z - height/2.0, center.z + height/2.0) || point.z >= fmax(center.z - height/2.0, center.z + height/2.0))){
        return -1;
    }

    double cos = DotProduct(uvec, vec_) / (EuclideanNorm(vec_) * EuclideanNorm(uvec));
    double sin = CrossProduct(uvec, vec_).z / (EuclideanNorm(vec_) * EuclideanNorm(uvec));

    int room = -2;
    
    // Check in which section the point is based on sin / cos values
    for(int i = 0; i<this->GetNbWalls(); i++){
        // Check if in wall / entrance
        if(this->walls[i].PointIsInside(point)){
            
            for(int j = 0; j<this->walls[i].GetNbEnts(); j++){
                if(this->walls[i].GetEntrances()[j].PointIsInside(point)){
                    // In last room
                    if(i == 0) return this->GetNbWalls() - 1;
                    
                    else return i - 1;
                }
            }
            // Inside wall
            return -3;
        }

        if(i + 1 == this->walls_cos.size()){
            // General case
            if((std::min(this->walls_cos[i], this->walls_cos[0]) <= cos && cos <= std::max(this->walls_cos[i], this->walls_cos[0])) 
                &&  std::min(this->walls_sin[i], this->walls_sin[0]) <= sin && sin <= std::max(this->walls_sin[i], this->walls_sin[0])){
                room = i;
            }
            
            // Crossing sin = -1 or 1
            // Check if this->walls_cos are in different quadrant && if abs value of sin is always above this->walls_sin[i] and this->walls_sin[i+1]
            if(this->walls_cos[i] * this->walls_cos[0] < 0 && fabs(sin / this->walls_sin[i]) >= 1  && fabs(sin / this->walls_sin[0]) >= 1){
                
                // Sin passes through -1
                if(sin < 0){
                    if(cos < 0){
                        if(this->walls_sin[i] / fabs(this->walls_sin[i]) <= sin && sin <= this->walls_sin[i]) room = i;
                    }
                    if(cos >= 0){
                        if(this->walls_sin[0] / fabs(this->walls_sin[0]) <= sin && sin <= this->walls_sin[0]) room = i; 
                    }
                }
                // Sin passes through 1
                if(sin > 0){
                    if(cos < 0){
                        if(this->walls_sin[i] <= sin && sin <= this->walls_sin[i] / fabs(this->walls_sin[i])) room = i;
                    }
                    if(cos >= 0){
                        if(this->walls_sin[0] <= sin && sin <= this->walls_sin[0] / fabs(this->walls_sin[0])) room = i; 
                    }
                }
            }
            // Crossing cos = -1 or 1
            // Sins in different quadrant && if abs value of sin is always above this->walls_cos[i] and this->walls_cos[i+1]
            if(this->walls_sin[i] * this->walls_sin[0] < 0 && fabs(cos / this->walls_cos[i]) >= 1  && fabs(cos / this->walls_cos[0]) >= 1){
                // Cos passes through -1
                if(cos < 0){
                    if(sin < 0){
                        if(this->walls_cos[i] / fabs(this->walls_cos[i]) <= cos && cos <= this->walls_cos[i]) room = i;
                    }

                    if(sin >= 0){
                        if(this->walls_cos[0] / fabs(this->walls_cos[0]) <= cos && cos <= this->walls_cos[0]) room = i;
                    }
                }
                // Cos passes through 1
                if(cos > 0){
                    if(sin < 0){
                        if(this->walls_cos[i] <= cos && cos <= this->walls_cos[i] / fabs(this->walls_cos[i])) room = i;
                    }

                    if(sin >= 0){
                        if(this->walls_cos[0] <= cos && cos <= this->walls_cos[0] / fabs(this->walls_cos[0])) room = i;
                    }
                }
            }

        }
        else{
            // General case            
            if((std::min(this->walls_cos[i], this->walls_cos[i+1]) <= cos && cos <= std::max(this->walls_cos[i], this->walls_cos[i+1])) 
                &&  std::min(this->walls_sin[i], this->walls_sin[i+1]) <= sin && sin <= std::max(this->walls_sin[i], this->walls_sin[i+1])){
                                
                room = i;
            }
            
            // Crossing sin = -1 or 1
            // Check if this->walls_cos are in different quadrant && if abs value of sin is always above this->walls_sin[i] and this->walls_sin[i+1]
            if(this->walls_cos[i] * this->walls_cos[i+1] < 0 && fabs(sin / this->walls_sin[i]) >= 1  && fabs(sin / this->walls_sin[i+1]) >= 1){
                // Sin passes through -1
                if(sin < 0){
                    if(cos < 0){
                        if(this->walls_sin[i] / fabs(this->walls_sin[i]) <= sin && sin <= this->walls_sin[i]) room = i;
                    }
                    if(cos >= 0){
                        if(this->walls_sin[i+1] / fabs(this->walls_sin[i+1]) <= sin && sin <= this->walls_sin[i+1]) room = i;
                    }
                }
                // Sin passes through 1
                if(sin > 0){
                    if(cos < 0){
                        if(this->walls_sin[i] <= sin && sin <= this->walls_sin[i] / fabs(this->walls_sin[i])) room = i;
                    }
                    if(cos >= 0){
                        if(this->walls_sin[i+1] <= sin && sin <= this->walls_sin[i+1] / fabs(this->walls_sin[i+1])) room = i;
                    }
                }
            }
            // Crossing cos = -1 or 1
            // Sins in different quadrant && if abs value of sin is always above this->walls_cos[i] and this->walls_cos[i+1]
            if(this->walls_sin[i] * this->walls_sin[i+1] < 0 && fabs(cos / this->walls_cos[i]) >= 1  && fabs(cos / this->walls_cos[i+1]) >= 1){
                // Cos passes through -1
                if(cos < 0){
                    if(sin < 0){
                        if(this->walls_cos[i] / fabs(this->walls_cos[i]) <= cos && cos <= this->walls_cos[i]) room = i;
                    }

                    if(sin >= 0){
                        if(this->walls_cos[i+1] / fabs(this->walls_cos[i+1]) <= cos && cos <= this->walls_cos[i+1]) room = i;
                    }
                }
                // Cos passes through 1
                if(cos > 0){
                    if(sin < 0){
                        if(this->walls_cos[i] <= cos && cos <= this->walls_cos[i] / fabs(this->walls_cos[i])) room = i;
                    }

                    if(sin >= 0){
                        if(this->walls_cos[i+1] <= cos && cos <= this->walls_cos[i+1] / fabs(this->walls_cos[i+1])) room = i;
                    }
                }
            }
            
        }
        
    }

    // No room found -2
    return room;
}

bool Arena3D::PointIsInside(const Vector3d<double>& point){
    Vector3d<double> r = center - point;
    if((r.x * r.x + r.y * r.y) < (radius * radius) && (point.z > fmin(center.z - height/2.0, center.z + height/2.0) && point.z < fmax(center.z - height/2.0, center.z + height/2.0))){ return true;}
    else{ return false;}
}
 
int Arena3D::GetRoomFromPosition(const double& x, const double& y, const double& z){
    return this->GetRoomFromPosition(Vector3d<double>(x, y, z));
}

bool Arena3D::AllowMove(const Vector3d<double>& a, const Vector3d<double>& b){
    int room_a = GetRoomFromPosition(a);
    int room_b = GetRoomFromPosition(b);
    // Trajectory in room
    if(room_a == room_b){ return true;}
    // Trajectory crossing rooms
    if(room_a == room_b - 1 || (room_a == GetNbWalls() - 1 && room_b == 0)){ 
        int index = room_a + 1;

        if(room_a + 1 == GetNbWalls()){ index = 0;}

        for(int i = 0; i<walls[index].GetNbEnts(); i++){

            if(walls[index].GetEntrances()[i].PointIsInside(a) && !walls[index].GetEntrances()[i].IsFake()){ return true;}

        }
    }
    
    return false;

}


std::vector<Vector3d<double> > Arena3D::GetRoomCenter() const{
    std::vector<Vector3d<double> > vec;
    for(int i = 0; i<this->GetNbWalls();i++){
        double frac = (i - 0.5) / GetNbWalls();
        vec.push_back(center + Vector3d<double>(this->radius / 2.0 * cos(frac * 2.0 * M_PI), this->radius / 2.0 * sin(frac * 2.0 * M_PI), this->height / 2.0));

    }
    return vec;
}

Vector3d<double> Arena3D::GetRoomCenter(const int& room) const{
    // If room is invalid return 0 point
    if(room < 0 || room >= this->GetNbWalls()){
        return this->center;
    }
    else{
        double frac = (room + 0.5)/ GetNbWalls();
        return center +  Vector3d<double>(this->radius / 2.0 * cos(frac * 2.0 * M_PI ), this->radius / 2.0 * sin(frac * 2.0 * M_PI), 0.0);
    }
    return Vector3d<double>(0.0, 0.0, 0.0);
}

Food* Arena3D::GetFood(){
    if(food != nullptr){ return food;}
    else{ return nullptr;}
}

bool Arena3D::GetFoodbool() const{
    if(food != nullptr){ return true;}
    else{ return false;}
}


void Arena3D::SetFood(Food* food){ this->food = food;}


void Arena3D::SetFoodRoom(const int& room){
    if(&food != nullptr){
        food->SetRoom(room);
    }
}

void Arena3D::SetFoodPosition(const Vector3d<double>& position){
    if(&food != nullptr){
        food->SetPosition(position);
    }
}

bool Arena3D::OnFood(const int& room){
    if(food != nullptr && room < GetNbWalls()){
        return room == food->GetRoom();
    }
    return false;
}



Vector3d<double> Arena3D::GetCenter() const{ return this->center;}

double Arena3D::GetRadius() const{ return this->radius;}

int Arena3D::GetNbWalls() const{ return this->walls.size();}

double Arena3D::GetHeight() const{ return this->height;}

vector<Wall> Arena3D::GetWalls() const{ return this->walls;}