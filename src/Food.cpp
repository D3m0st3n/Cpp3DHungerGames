#include <iostream>
#include "Vector3D.h"
#include "Arena3D.h"
#include "Food.h"

Food::Food(Arena3D* arena, const int& room, const double& max_lifetime) : lifetime(0.0) {
    this->arena = arena;
    if(max_lifetime > 0){ this->max_lifetime = max_lifetime;}
    if(room >= 0 && room < this->arena->GetNbWalls()){ this->room = room;}
    else{ this->room = 0;}
    // Set position as room center
    this->position = arena->GetRoomCenter(this->room);
    this->position.z = 0.0;

}

Food::Food(Arena3D* arena, const Vector3d<double>& pos, const double& max_lifetime): lifetime(0.0){
    this->arena = arena;
    if(max_lifetime > 0){ this->max_lifetime = max_lifetime;}
    this->position = pos;
    this->room = arena->GetRoomFromPosition(position);
}

Food::Food(Food* food) : lifetime(0.0) { 
    if(food != nullptr){
        this->max_lifetime = food->GetMaxLifetime();
        this->arena = food->GetArena();
        this->room = food->GetRoom();
        this->position = food->GetPosition();
    }

}

int Food::GetRoom() const{ return room;}

Arena3D* Food::GetArena(){ return arena;}

double Food::GetMaxLifetime() const{ return max_lifetime;}

double Food::GetLifetime() const{ return lifetime;}

Vector3d<double> Food::GetPosition() const{ return position;}

void Food::SetPosition(const Vector3d<double>& pos){ 
    this->position = pos;
    this->room = arena->GetRoomFromPosition(position);    
}

void Food::SetPosition(const double& x, const double& y, const double& z){
    this->SetPosition(Vector3d<double> (x, y, z));
}


void Food::SetRoom(const int& room){
    if( room >= 0 && room < arena->GetNbWalls()){
        this->room = room;
        this->position=arena->GetRoomCenter(this->room);
    }
}

void Food::Update(const double& dt){
    double rate = 1;

    if(lifetime < max_lifetime){lifetime += rate * dt;}
    else{ 
        lifetime = 0.0;
        if(room >= arena->GetNbWalls() - 1){
            room = 0;
        }
        else{
            room += 1;
        }

    }

}
