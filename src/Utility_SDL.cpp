// Standard library
#include <iostream>
#include <fstream>

//Utility file
#include "Utility_SDL.h"
#include "Food.h"
#include "Wall.h"


void SDL_Utility::DrawCircle(SDL_Renderer* renderer, const int32_t& centreX, const int32_t& centreY, const int32_t& radius)
{
   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

void SDL_Utility::DrawCircleF(SDL_Renderer* renderer, const float& centreX, const float& centreY, const float& radius){
   const float diameter = (radius * 2);

   float x = (radius - 1);
   float y = 0;
   float tx = 1;
   float ty = 1;
   float error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPointF(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPointF(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPointF(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPointF(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPointF(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPointF(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPointF(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPointF(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}

void SDL_Utility::DrawRing(SDL_Renderer* renderer, const int32_t& centreX, const int32_t& centreY, const int32_t& radius, const int32_t& width){
   for(int i = radius; i <= radius + width; i++){
      SDL_Utility::DrawCircle(renderer, centreX, centreY, i);
   }
}

void SDL_Utility::DrawRingF(SDL_Renderer* renderer, const float& centreX, const float& centreY, const float& radius, const float& width){
   // Add step parameter for drawing?
   for(float i = radius; i <= radius + width; i += 0.1){
      SDL_Utility::DrawCircleF(renderer, centreX, centreY, i);
   }
}

void SDL_Utility::DrawFood(SDL_Renderer* renderer, Arena3D* arena, const double& radius){

   if(arena->GetFood() != nullptr){
      Vector3d<double> room_center = arena->GetRoomCenter(arena->GetFood()->GetRoom());
      SDL_SetRenderDrawColor(renderer, 255, 0, 125, SDL_ALPHA_OPAQUE);
      SDL_Utility::DrawCircleF(renderer,room_center.x, room_center.y, radius);
   }

}

void SDL_Utility::DrawArena(SDL_Renderer* renderer, Arena3D* arena){
   
   // Outer ring wall
   double width = 1.0;
   if(arena->GetNbWalls() != 0){
      width = arena->GetWalls()[0].GetWidth();
   }

   SDL_Utility::DrawCircleF(renderer, arena->GetCenter().x, arena->GetCenter().y, arena->GetRadius());
   SDL_Utility::DrawCircleF(renderer, arena->GetCenter().x, arena->GetCenter().y, arena->GetRadius() + width);

   // Wall drawing
   for(int i = 0; i<arena->GetNbWalls(); i++){
      // Use RenderDrawLines as we need tilted shapes
      // Wall coordinates
      std::vector<Vector3d<double> > coords = arena->GetWalls()[i].GetCoord();
      // Set color to white
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

      for(int j = 0; j < arena->GetWalls()[i].GetNbSides(); j++){
         
         if(j+1 == arena->GetWalls()[i].GetNbSides()){
            SDL_RenderDrawLineF(renderer, coords[0].x, coords[0].y, coords[j].x, coords[j].y);
         }
         
         else{
            SDL_RenderDrawLineF(renderer, coords[j].x, coords[j].y, coords[j+1].x, coords[j+1].y);
            }

      }

      // Draw entrances
      // Set color to green
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);      
      for(int j=0; j<arena->GetWalls()[i].GetNbEnts(); j++){
         // Entrance coordinates
         std::vector<Vector3d<double> > coords_e = arena->GetWalls()[i].GetEntrances()[j].GetCoord();

         if(arena->GetWalls()[i].GetEntrances()[j].IsFake()){SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);}

         if(!arena->GetWalls()[i].GetEntrances()[j].IsFake()){SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);}


         for(int k = 0; k < arena->GetWalls()[i].GetNbSides(); k++){

            if(k+1 == arena->GetWalls()[i].GetNbSides()){
               SDL_RenderDrawLineF(renderer, coords_e[0].x, coords_e[0].y, coords_e[k].x, coords_e[k].y);
            }
            
            else{
               SDL_RenderDrawLineF(renderer, coords_e[k].x, coords_e[k].y, coords_e[k+1].x, coords_e[k+1].y);
               }
         }
   
      } 
   }

   // Draw Food object
   SDL_Utility::DrawFood(renderer, arena);
}

void SDL_Utility::DrawAgent(SDL_Renderer* renderer, Fly3D* fly, Arena3D* arena){
   Vector3d<double> orient = fly->GetPosition() - fly->GetVelocity();
   
   int z = fly->GetPosition().z * 255/(std::fmax(arena->GetCenter().z + arena->GetHeight()/2.0, arena->GetCenter().z - arena->GetHeight()/2.0) - std::fmin(arena->GetCenter().z + arena->GetHeight()/2.0, arena->GetCenter().z - arena->GetHeight()/2.0)); 

   double radius = 10.0;
   SDL_SetRenderDrawColor(renderer, z, 0, 255 - z, SDL_ALPHA_OPAQUE); 
   SDL_Utility::DrawCircleF(renderer, fly->GetPosition().x, fly->GetPosition().y, radius);

   // Draw Fres
   SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); 
   if(EuclideanNorm(fly->GetFres()) != 0){
      SDL_RenderDrawLineF(renderer, fly->GetPosition().x, fly->GetPosition().y, fly->GetPosition().x + fly->GetFres().x * 10 / EuclideanNorm(fly->GetFres()), fly->GetPosition().y + fly->GetFres().y * 10/ EuclideanNorm(fly->GetFres()));
   }

   // Draw velocity
   SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);      

   Vector3d<double> v(fly->GetVelocity());
   SDL_RenderDrawLineF(renderer, fly->GetPosition().x, fly->GetPosition().y, fly->GetPosition().x + v.x, fly->GetPosition().y + v.y);

}
