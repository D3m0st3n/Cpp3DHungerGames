// C++ Standard Libraries
#include <iostream>
// Third party
#include <SDL.h>
// Project files
#include "Utility_SDL.h"
#include "Wall.h"
#include "Food.h"
#include "Arena3D.h"
#include "Simulation3D.h"

int main(int argc, char* argv[]){
    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window=nullptr;

    // Grab the window surface.
    SDL_Surface* screen;

    // Initialize the video subsystem.
    // If it returns less than 1, then an
    // error code will be received.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }
    
    else{
        std::cout << "SDL video system is ready to go\n";
    }

    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("C++ SDL2 Window",
            800,
            100,
            1100,
            1100,
            SDL_WINDOW_SHOWN);
    
    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    
    // Create an arena
    // Simulation variables 
    double dt = 0.1;
    unsigned int nb_flies = 200;
    unsigned int nb_rooms = 4;
    unsigned int nb_ent = 4;
    int s_room = 0;
    int f_room = s_room + 1;
    double maxtime = 10000.0;
    double food_shift = 100.0;
    double wall_width = 20.0;
    bool no_food = 1;
    bool dataR = 0;


    // Arena initialization
    Arena3D arena(Vector3d<double>(550, 550, 250), 500, 500, nb_rooms, nb_ent, wall_width);
    
    // Food initialization
    if(f_room >= arena.GetNbWalls() || f_room < 0){ f_room = 0;}
    if(!no_food){
        Food food(&arena, f_room, food_shift);
        arena.SetFood(&food);
    }
    // Simulation initialization
    Simulation3D Sim3D( &arena, nb_flies, s_room, maxtime, dt, dataR);

    std::cout<<" Simulation start  \n";
    
    // Infinite loop for our application
    bool simIsRunning = true;
    bool restart = false;
    bool pause = false;

    // height variable increment
    int z = 50;
    // Main application loop
    while(simIsRunning){
        SDL_Event event;

        int x, y;
        Uint32 buttons;
        buttons = SDL_GetMouseState(&x,&y);

        // (1) Handle Input
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.key.keysym.sym == SDLK_r){
                restart = true;
                simIsRunning = false;
            }
            // Pause
            if(event.key.keysym.sym == SDLK_p && event.type == SDL_KEYDOWN){
                if(pause) pause = false; 
                else if(!pause) pause = true;
            }
            // Change height in window
            if(event.key.keysym.sym == SDLK_o && event.type == SDL_KEYDOWN){
                z +=  50;
                std::cout<<"z : "<<z<<"\n";
            }
            if(event.key.keysym.sym == SDLK_i && event.type == SDL_KEYDOWN){
                z -= 50;
                std::cout<<"z : "<<z<<"\n";
            }
            // Change timestep during simulation
            if(event.key.keysym.sym == SDLK_l && event.type == SDL_KEYDOWN){
                dt += 0.1;
                std::cout<<"timestep :  "<<dt<<"\n";
            }
            if(event.key.keysym.sym == SDLK_k && event.type == SDL_KEYDOWN){
                if(dt > 0.0){ dt -= 0.1;}
                std::cout<<"timestep :  "<<dt<<"\n";
            }
            // Quit event
            if(event.type == SDL_QUIT){
                simIsRunning= false;
            }
            if(event.type == SDL_KEYDOWN){
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    simIsRunning = false;
                }
            }
            // Print mouse position in simulation
            if ((buttons & SDL_BUTTON_LMASK) != 0) {
                std::cout<< "Clicked on ( " << x << ", "<< y <<" , "<< z << " ) \n";
                std::cout<<" Clicked in room : "<<arena.GetRoomFromPosition(Vector3d<double>(x, y, z))<<"\n";
            }
            // Change aim of flies in simulation
            if((buttons & SDL_BUTTON_RMASK) != 0){
                std::cout<< "Clicked on ( " << x << ", "<< y <<" , "<< z <<" ) \n";
                for( auto fly : Sim3D.GetFlies()){
                    fly->SetAim(Vector3d<double>(x, y, z));
                }
            }
        }

        if(!Sim3D.IsRunning()){
            simIsRunning = false;
        }
        
        
        // (2) Handle Updates

        // (3) Clear Draw the Screen
        // Gives us a clear canvas
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Wall points drawing
        /* SDL_SetRenderDrawColor(renderer, 255, 125, 0, SDL_ALPHA_OPAQUE);
        for(int i = 0; i< arena.GetNbWalls(); i++){
            for(int j = 0; j<4; j++){
                SDL_RenderDrawPointF(renderer, arena.GetWalls()[i].GetCoord()[j].x, arena.GetWalls()[i].GetCoord()[j].y);
            }
        } */
        // Arena drawing
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_Utility::DrawArena(renderer, &arena);

        for(int i = 0; i<Sim3D.GetFlies().size(); i++){
            SDL_Utility::DrawAgent(renderer, Sim3D.GetFlies()[i], &arena);
            SDL_SetRenderDrawColor(renderer, 255, 255, 100, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLineF(renderer, Sim3D.GetFlies()[i]->GetAim().x - 2.5, Sim3D.GetFlies()[i]->GetAim().y - 2.5, Sim3D.GetFlies()[i]->GetAim().x + 2.5, Sim3D.GetFlies()[i]->GetAim().y + 2.5);
            SDL_RenderDrawLineF(renderer, Sim3D.GetFlies()[i]->GetAim().x - 2.5, Sim3D.GetFlies()[i]->GetAim().y + 2.5, Sim3D.GetFlies()[i]->GetAim().x + 2.5, Sim3D.GetFlies()[i]->GetAim().y - 2.5);
        }

        bool info = false;
        if(info){
            for(auto fly : Sim3D.GetFlies()){
                std::cout<<fly->GetPosition()<<"\n";
            }
        } 

        // Finally show what we've drawn 
        SDL_RenderPresent(renderer);

        if(!pause){
            // Update simulation
            Sim3D.Update(dt);
        }

    }

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);
    
    // Create datafile in csv format
    // Utility::MakeCSVFromSim(Sim3D);

    // Quit program.
    SDL_Quit();

    if(restart) return main(argc, argv);
    return 0;

};