#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include "Vector3D.h"
#include "Cuboid.h"
#include "Wall.h"
#include "Entrance.h"
#include "Arena3D.h"

Wall::Wall(const Vector3d<double>& c1, const Vector3d<double>& c2, const Vector3d<double>& c3, const Vector3d<double>& c4, double h, int nb_ent, Arena3D* arena) : Cuboid(c1, c2, c3, c4, h) {
    this->BuildEntrances(nb_ent, 0.1 * this->GetLength());
    this->arena = arena;

}

Wall::Wall(const Vector3d<double>& p, const double& length, const double& width, double h, int nb_ent, Arena3D* arena) : Cuboid(p, length, width, h) {
    this->BuildEntrances(nb_ent, 0.1 * this->GetLength());
    this->arena = arena;

}

void Wall::BuildEntrances(const int& nb_ent, const double& length_e){
    // Random Number Generator initialization
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> Uniform(0.1 * GetLength(), 0.9 * GetLength());
    
    // Tries to place entrances until they do not superpose
    do
    {   
        bool add_flag = true;
        Vector3d<double> c1, c2, c3, c4;

        c1 = this->coord[0] + this->GetLengthVec() * Uniform(gen) + this->GetHeightVec() * Uniform(gen);
        c2 = c1 + this->GetLengthVec() * length_e;
        c3 = c2 + this->GetWidthVec() * this->GetWidth();
        c4 = c1 + this->GetWidthVec() * this->GetWidth();
        bool isFake = false;

        if(ents.size() > 0){

            isFake = true;

            for(int i=0; i<ents.size();i++){
                if(EuclideanNorm(ents[i].GetCoord()[0] - c1) <= 1.1 * length_e){
                    add_flag = false;
                }
            }
        }
        if(add_flag){ this->ents.push_back(Entrance(c1, c2, c3, c4, length_e, isFake, this));}
    } while (ents.size() < nb_ent);

    std::cout << "Entrances built, nb ents : "<< this->GetNbEnts()<<"\n";

}

std::vector<Entrance> Wall::GetEntrances() const{ return this->ents;}

int Wall::GetNbEnts() const{ return this->ents.size();}
