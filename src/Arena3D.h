#ifndef ARENA3D_H
#define ARENA3D_H

#include "Vector3D.h"
#include "Wall.h"
#include "Food.h"
#include <iostream>

class Arena3D {
    //3D Arena class
    
    public:
    //Array of flies has to be a pointer to declare size

    //Array of walls has to be a pointer to declare size in constructor

    //Constructor
    /**
     * @brief Construct a new Arena 2D object
     * Arena 2D is always a circular arena composed of walls evenly spaced within it.
     * 
     * @param c coordinate of center of the arena
     * @param r radius of the arena
     * @param h height of arena
     * @param nb_walls number of walls
     * @param w_width wall width
     */
    Arena3D(const Vector3d<double>& c, const double& r, const double& h, int nb_walls = 0, const int& nb_ent = 4, const double& w_width = 0);
    /**
     * @brief Construct a new Arena 2D object
     * 
     * @param c1 x coordinate of center
     * @param c2 y coordinate of center
     * @param c3 z coordinate of center
     * @param r radius of the arena
     * @param h height of arena
     * @param nb_walls number of walls 
     * @param w_width wall width
     */
    Arena3D(const double& c1, const double& c2, const double& c3, const double& r, const double& h, int nb_walls = 0, const int& nb_ent = 4, const double& w_width = 0);

    // Destructor for pointers


    // Others
    /**
     * @brief Get the Room From Position object
     * 
     * @param point 
     * @return int room corresponding to position
     */
    int GetRoomFromPosition(const Vector3d<double>& point);
    int GetRoomFromPosition(const double& x, const double& y, const double& z);

    /**
     * @brief Indicate if move a to b is legal in arena
     * 
     * @param a starting point 
     * @param b ending point
     * @return true move is legal, does not cross wall, not outside arena or going through real entrance to next room
     * @return false outside arena, through wall, going through fake entrance to next room
     */
    bool AllowMove(const Vector3d<double>& a, const Vector3d<double>& b);

    //Getters
    /**
     * @brief Get the Center object, center coordinates of cylinder at mid height
     * 
     * @return Vector3d<double> center coordinates
     */
    Vector3d<double> GetCenter() const;

    /**
     * @brief Get the Radius object
     * 
     * @return double radius
     */
    double GetRadius() const;

    /**
     * @brief Get the Height object
     * 
     * @return double height
     */
    double GetHeight() const;

    /**
     * @brief Get the number of walls, equivalent to getting the number of rooms
     * 
     * @return int number of walls
     */
    int GetNbWalls() const;
    
    /**
     * @brief Get the list of walls in the arena
     * 
     * @return std::vector<Wall> vector of walls
     */
    std::vector<Wall> GetWalls() const;

    /**
     * @brief Get the vector of room center
     * 
     * @return std::vector<Vector3d<double> > list of room center
     */
    std::vector<Vector3d<double> > GetRoomCenter() const;
    /**
     * @brief Get the center of room based on index
     * 
     * @param room 
     * @return Vector3d<double> room center of interest
     */
    Vector3d<double> GetRoomCenter(const int& room) const;

    /**
     * @brief Check wether a point is inside or outside the arena
     * 
     * @param point Vector3D
     * @return true point is within the arena
     * @return false point is outside the arena
     */
    bool PointIsInside(const Vector3d<double>& point);

    /**
     * @brief Get food of arena
     * 
     * @return Food* 
     */
    Food* GetFood();

    bool GetFoodbool() const;


    /**
     * @brief Set the Food object
     * 
     * @param food 
     */
    void SetFood(Food* food);

    /**
     * @brief Set food in room
     * 
     * @param room room 
     * @return true 
     * @return false 
     */
    void SetFoodRoom(const int& room);

    void SetFoodPosition(const Vector3d<double>& position);

    /**
     * @brief check if position is in same room as food
     * 
     * @param room 
     * @return true position is in same room
     * @return false position is not in same room/ food is nullptr
     */
    bool OnFood(const int& room);
        
    

    private:
    //Attributes
    //Radius of arena
    double radius;
    // Height
    double height;
    //Center coordinates
    Vector3d<double> center;
    //List of walls 
    std::vector<Wall> walls;
    // Lists of angles
    std::vector<double> walls_cos;
    std::vector<double> walls_sin;
    // Food object
    Food* food;

    //Methods
    /**
     * @brief Build evenly spaced number of walls within the arena to create rooms
     * 
     * @param nb_walls number of walls
     * @param w_width wall width
     */
    void BuildWalls(int nb_walls = 0, const int& nb_ent = 4, const double& w_width = 0);

};

#endif