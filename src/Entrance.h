#ifndef ENTRANCE_H
#define ENTRANCE_H

#include "Vector3D.h"
#include "Cuboid.h"

// Forward declaration of interdependent class
class Wall;

class Entrance : public Cuboid{

    private:
    // Wall pointer
    Wall* wall;
    // Wall boolean indicator
    bool isFake; 

    public:
    
    /**
     * @brief Construct a new Entrance object
     * 
     * @param c1 point one
     * @param c2 point two
     * @param c3 point three
     * @param c4 point four
     * @param h height of entrance
     * @param isFake indicate if entrance is fake or not
     * @param wall pointer to associated wall
     */
    Entrance(const Vector3d<double>& c1, const Vector3d<double>& c2, const Vector3d<double>& c3, const Vector3d<double>& c4, const double& h, const bool& isFake = false,  Wall* wall = nullptr);


    /**
     * @brief Construct a new Entrance object
     * 
     * @param p a starting point
     * @param length length of the rectangle
     * @param width width of the rectangle
     * @param height height of entrance
     * @param isFake indicate if entrance is fake or not
     * @param wall pointer to associated wall
     */
    Entrance(const Vector3d<double>& p, const double& length, const double& width, const double& height, const bool& isFake = false, Wall* wall = nullptr);

    /**
     * @brief return if entrance is real or not
     * 
     * @return true real entrance
     * @return false fake entrance
     */
    bool IsFake();

};


#endif