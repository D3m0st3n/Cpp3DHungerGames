#include <iostream>
#include <vector>
#include <chrono>
#include <stdlib.h>

#include "Vector3D.h"
#include "Cuboid.h"
#include "Wall.h"
#include "Arena3D.h"
#include "Simulation3D.h"

using namespace std;
using namespace std::chrono;


int main (int argc, char** argv) {
    // Simulation variables 
    bool start_sim = true;
    unsigned int number_sim = 1;
    unsigned int nb_flies = 2000;
    unsigned int nb_rooms = 4;
    unsigned int nb_ent = 4;
    int s_room = 0;
    int f_room = s_room + 1;
    double maxtime = 1000.0;
    double dt = 0.1;
    double food_shift = 100.0;
    double wall_width = 10.0;
    bool nfood = 0;
    bool dataR = 1;

    for (int i = 0; i < argc; ++i){
        // Help command
        if(std::string(argv[i]) == "-h"  || std::string(argv[i]) == "--help" ){
            start_sim = false;
            std::cout<<"\n\n";
            std::cout<<"-h , --help             Help command, shows and describes all simulation paramters";
            std::cout<<"\n";
            std::cout<<"-n , --number           Number of simulation, >0";
            std::cout<<"\n";
            std::cout<<"-f , --flies            Number of flies in simulation, >0";
            std::cout<<"\n";
            std::cout<<"-r , --rooms            Number of rooms in simulation, >=0";
            std::cout<<"\n";
            std::cout<<"-sr , --start_room      Starting room for flies, >=0";
            std::cout<<"\n";
            std::cout<<"-e , --entrances        Number of entrances on each wall, 1st entrance is real, next ones are fake, >0";
            std::cout<<"\n";
            std::cout<<"-t , --timestep         Timestep of simulation, >0";
            std::cout<<"\n";
            std::cout<<"-T , --time             Duration of simulation, >0";
            std::cout<<"\n";
            std::cout<<"-fs , --food_shifting   Food shifting time, >0";
            std::cout<<"\n";
            std::cout<<"-nf, --no_food          If food has to be simulated or not, 1 or 0";
            std::cout<<"\n";
            std::cout<<"-d , --data             Data recording, 1 to record data,  0 not to";
            std::cout<<"\n\n";

        }
        // Number of simulation
        if(std::string(argv[i]) == "-n"  || std::string(argv[i]) == "--number" ){
            if(stoi(argv[i + 1]) > 0){
                number_sim = stoi(argv[i + 1]);
            }
        }
        // Number of flies
        if(std::string(argv[i]) == "-f"  || std::string(argv[i]) == "--flies" ){
            if(stoi(argv[i + 1]) > 0){
                nb_flies = stoi(argv[i + 1]);
            }
        }
        // Number of rooms
        if(std::string(argv[i]) == "-r"  || std::string(argv[i]) == "--rooms" ){
            if(stoi(argv[i + 1]) > 0){
                nb_rooms = stoi(argv[i + 1]);
            }
        }
        // Starting room
        if(std::string(argv[i]) == "-sr"  || std::string(argv[i]) == "--start_room" ){
            if(stoi(argv[i + 1]) >= 0 && stoi(argv[i + 1]) < nb_rooms){
                s_room = stoi(argv[i + 1]);
                f_room = s_room + 1;
            }
        }
        // Number of entrances
        if(std::string(argv[i]) == "-e"  || std::string(argv[i]) == "--entrances" ){
            if(stoi(argv[i + 1]) > 0){
                nb_ent = stoi(argv[i + 1]);
            }
        }
        // Timestep
        if(std::string(argv[i]) == "-t"  || std::string(argv[i]) == "--timestep" ){
            if(stod(argv[i + 1]) > 0.0){
                dt = stod(argv[i + 1]);
            }
        }
        // Time of simulation
        if(std::string(argv[i]) == "-T"  || std::string(argv[i]) == "--time" ){
            if(stod(argv[i + 1]) > 0.0){
                maxtime = stod(argv[i + 1]);
            }
        }
        // Food shifting time
        if(std::string(argv[i]) == "-fs"  || std::string(argv[i]) == "--food_shifting" ){
            if(stod(argv[i + 1]) > 0.0 && stod(argv[i + 1]) < maxtime){
                food_shift = stod(argv[i + 1]);
            }
        }
        // Food/No food
        if(std::string(argv[i]) == "-nf" || std::string(argv[i]) == "--no_food"){
            if(stoi(argv[i + 1]) == 0){ nfood = 0;}
            if(stoi(argv[i + 1]) == 1){ nfood = 1;}
        }
        // Data recording
        if(std::string(argv[i]) == "-d" || std::string(argv[i]) == "--data"){
            if(stoi(argv[i + 1]) == 0){ dataR = 0;}
            if(stoi(argv[i + 1]) == 1){ dataR = 1;}
        }
        // Force run
        if(std::string(argv[i]) == "-R"  || std::string(argv[i]) == "--run" ){
            start_sim = true;
        }



    }

    if(start_sim){
        for(int i = 0; i < number_sim; i++){

            // Create arena
            Arena3D arena(Vector3d<double>(500, 500, 250), 500, 500, nb_rooms, nb_ent, wall_width);
            if(f_room >= arena.GetNbWalls()){ f_room = 0;}
            // Set food object in arena
            if(!nfood){
                Food food(&arena, f_room, food_shift);
                arena.SetFood(&food);
            }
            // Create simulation
            Simulation3D Sim3D( &arena, nb_flies, s_room, maxtime, dt, dataR);
            
            auto start = high_resolution_clock::now();
            
            std::cout<<" ----Simulation "<<i<<" start---- \n";
            // Line to limit system clear command in Simualtion3D::Verbose()
            std::cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

            for(int i = 0; i < maxtime / dt; i++){

                Sim3D.Update(dt);


            }
            std::cout<<" ----Simulation "<<i<<" end----  \n";
            auto stop = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(stop - start);
            std::cout<<" Simulation duration : "<<duration.count() / pow(10.0,6) <<" s \n";
        }
    }
    return 0;
};

