#ifndef FOOD_H
#define FOOD_H

class Arena3D;

class Food{

    public :
    /**
     * @brief Construct a new Food object
     * 
     * @param arena pointer to arena
     * @param room position of food in arena
     * @param max_lifetime time spent in each room
     */
    Food(Arena3D* arena, const int& room, const double& max_lifetime);
    
    /**
     * @brief Construct a new Food object
     * 
     * @param arena pointer to arena
     * @param pos poisition
     * @param max_lifetime time spent in each room
     */
    Food(Arena3D* arena, const Vector3d<double>& pos, const double& max_lifetime);

    /**
     * @brief Construct a new Food from already existing object
     * 
     * @param food 
     */
    Food(Food* food);

    /**
     * @brief Get the room 
     * 
     * @return int room, position of food in arena
     */
    int GetRoom() const;

    /**
     * @brief Set the room
     * 
     * @param room 
     */
    void SetRoom(const int& room);

    /**
     * @brief Set the food position
     * 
     * @param pos position 3D vector
     */
    void SetPosition(const Vector3d<double>& pos);

    /**
     * @brief Set the food posiiton
     * 
     * @param x x coordinate
     * @param y y coordinate
     * @param z z coordinate
     */
    void SetPosition(const double& x, const double& y, const double& z);

    /**
     * @brief update food
     * Move food everytime it reaches its max_lifetime
     * 
     * @param  dt timestep of simulation
     */
    void Update(const double& dt);
    /**
     * @brief Get the Arena object
     * 
     * @return Arena3D* in which Food is in
     */
    Arena3D* GetArena();

    /**
     * @brief Get the Max Lifetime object
     * 
     * @return double lifetime before switching room
     */
    double GetMaxLifetime() const;

    /**
     * @brief Get the Lifetime object
     * 
     * @return double current time spent in room
     */
    double GetLifetime() const;

    /**
     * @brief Get the position of food in simulation
     * 
     * @return const Vector3d<double>& position vector 
     */
    Vector3d<double> GetPosition() const;

    private :
    // Arena
    Arena3D* arena;
    // Location of food in arena
    int room;
    // Position
    Vector3d<double> position;
    // Max Lifetime
    double max_lifetime;
    // Lifetime
    double lifetime;
    };
#endif