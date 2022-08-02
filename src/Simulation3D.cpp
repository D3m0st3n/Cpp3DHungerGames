#include "Vector3D.h"
#include "Fly3D.h"
#include "Arena3D.h"
#include "Simulation3D.h"

#include <fstream>
#include <sys/stat.h>
#include <cmath>
#include <string.h>

Simulation3D::Simulation3D(const Vector3d<double>& c, const double& r, const double& h, int nb_walls, const int& nb_ent, const int& nb_flies, const int& starting_room, const double& maxtime, const double& dt, const bool& datarec, const bool& v) : 
maxtime(maxtime), time(0.0), dt(dt), dataRec(datarec), VERBOSE(v){

    this->arena = new Arena3D(c, r, h, nb_walls, nb_ent);
    for(int i = 0; i<nb_flies; i++){
        this->flies.push_back(new Fly3D(starting_room, i, this->arena));
    }
    if(dataRec){ InitializeFile();}
}

Simulation3D::Simulation3D(const double& c1, const double& c2, const double& c3, const double& r, const double& h, int nb_walls, const int& nb_ent, const int& nb_flies, const int& starting_room, const double& maxtime, const double& dt, const bool& datarec, const bool& v) : 
maxtime(maxtime), time(0.0), dt(dt), dataRec(datarec), VERBOSE(v){

    this->arena = new Arena3D(c1, c2, c3, r, h, nb_walls, nb_ent);
    for(int i = 0; i<nb_flies; i++){
        this->flies.push_back(new Fly3D(starting_room, i, this->arena));
    }
    if(dataRec){ InitializeFile();}
}

Simulation3D::Simulation3D(Arena3D* arena, const int& nb_flies, const int& starting_room, const double& maxtime, const double& dt, const bool& datarec, const bool& v) : maxtime(maxtime), time(0.0), dt(dt), VERBOSE(v){
    this->arena = arena;
    this->dataRec = datarec;
    for(int i = 0; i<nb_flies; i++){
        this->flies.push_back(new Fly3D(starting_room, i, this->arena));
    }
    if(dataRec){ InitializeFile();}
}

Simulation3D::~Simulation3D(){
    std::cout<<"Total Running Time : "<<time<<"\n";
    // Delete agents
    for(int i=0; i < this->flies.size(); i++) delete(this->flies[i]);
    // Delete arena
    // TODO : Comprehensive deletion of arena if created using NEW command
    // delete arena;

    if(dataRec){ this->CloseFile();}
}

Vector3d<double> Simulation3D::GetArenaCenter() const{ return (*arena).GetCenter();}

double Simulation3D::GetArenaRadius() const{ return (*arena).GetRadius();}

double Simulation3D::GetArenaHeight() const{ return (*arena).GetHeight();}

void Simulation3D::Update(const double& dt){


    // std::cout<<"Update Sim\n";
    if(time < maxtime){
        // Flies update
        for(int i=0; i<this->flies.size(); i++){

            // Agent update
            flies[i]->Update(dt);

        }
        // Food update
        if(arena->GetFood() != nullptr){
            arena->GetFood()->Update(dt);
        }

        // Data recording
        if(dataRec){
            // Values of variables
            Simfile<< time <<", ";
            for(int i = 0; i < this->GetFlies().size(); i++){
                Simfile<< this->flies[i]->GetPosition().x <<", "<<this->flies[i]->GetPosition().y<<", "<<this->flies[i]->GetPosition().z<<", "<<this->flies[i]->GetRoom()<<", "<<this->flies[i]->GetTimeOnFood();
                if(i < this->flies.size() - 1){ Simfile<<", ";}
            }
            Simfile<<"\n";
        }

        if(VERBOSE) Verbose();

        
        time += dt;
    }



}

void Simulation3D::Verbose(){
    /* system("clear");

    std::cout<<"%";
    for(int i = 0; i < 10; i++){
        if(i <= floor(time / maxtime * 10)){
            std::cout<<"=";
        }
        if( i > floor(time / maxtime * 10)){
            std::cout<<" ";
        }
    }
    std::cout<<"%   "<<ceil(time / maxtime * 100.0)<<" %";

    std::cout<<"\n\n"; */
}

Arena3D* Simulation3D::GetArena(){ return this->arena;}

double Simulation3D::GetWindowWidth() const{ return arena->GetCenter().x + arena->GetRadius();}

double Simulation3D::GetWindowHeight() const{ return arena->GetCenter().y + arena->GetRadius();}

std::vector<Fly3D* > Simulation3D::GetFlies(){ return this->flies;}

double Simulation3D::GetTime() const{ return time;}
    
double Simulation3D::Getdt() const{ return dt;}

double Simulation3D::GetMaxTime() const{return maxtime;}

bool Simulation3D::IsRunning() const{ return time < maxtime;}

void Simulation3D::InitializeFile(){
    // filename
    std::string directory("SimData/");
    std::string filename("SimData_");
    std::string number("000");
    std::string ext(".csv");
    // Check if datafile already exists
    for(int i = 0; i < 1000; i++){
        // Initialize file number
        if(i < 10){ number = "00" + std::to_string(i);}
        if(i >= 10 && i < 100 ){ number = "0" + std::to_string(i);}
        if(i >= 100){ number = std::to_string(i);}
        // Check existence of datafile
        if(!fileExists(directory + filename + number + ext)){
            break;
        }
    }

    // Initialize datafile
    Simfile.open(directory + filename + number + ext);
    Simfile << "time, ";
    for(int i = 0; i < this->flies.size(); i++){
        std::string nb = std::to_string(i);
        Simfile << "fly"<<i<<".x "<<", "<<"fly"<<i<<".y"<<", "<<"fly"<<i<<".z"<<", "<<"fly"<<i<<".room"<<", "<<"fly"<<i<<".TOF";
        if(i < this->flies.size() - 1){ Simfile<<", ";}
    }
    Simfile << "\n";

    WriteConfig(number);
}

void Simulation3D::WriteConfig(const std::string& number){
    // filename 
    std::string directory("SimConfig/");
    std::string filename("SimConfig_");
    std::string ext(".csv");

    // Initialize datafile
    Configfile.open(directory + filename + number + ext);
    Configfile << "time, timestep, flies, rooms, entrances, height, radius, center.x, center.y, center.z, food, food shifting \n";
    Configfile << maxtime <<", "<< dt <<", "<<flies.size();
    if(arena != nullptr){ Configfile<<", "<<arena->GetNbWalls()<<", "<<arena->GetWalls()[0].GetNbEnts()<<", "<<GetArenaHeight()<<", "<<GetArenaRadius()<<", "<<GetArenaCenter().x<<", "<<GetArenaCenter().y<<", "<<GetArenaCenter().z;}
    else{ Configfile<<", "<<0<<", "<<0<<", "<<0<<", "<<0<<", "<<0<<", "<<0;}
    
    if(arena != nullptr && arena->GetFood() != nullptr){ Configfile<<", "<<"yes"<<", "<<arena->GetFood()->GetMaxLifetime()<<"\n";}
    else{ Configfile<<", "<<"no"<<", "<<0;}

    Configfile<<"\n";

}

void Simulation3D::CloseFile(){
    if(Simfile.is_open()){ Simfile.close();}
    if(Configfile.is_open()){ Configfile.close();}
};

bool fileExists(const std::string& filename){
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}
