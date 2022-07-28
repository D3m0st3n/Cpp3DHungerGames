#ifndef FLY3D_H
#define FLY3D_H

#include <iostream>

#include "Vector3D.h"
#include "Arena3D.h"

class Simulation3D;

class Fly3D {

    // friend class Simulation3D;

    // 3D agent navigating inside the arena
    private:

    int room;
    // x, y position
    Vector3d<double> r;
    // velocity of agent
    Vector3d<double> v;
    // Velocity of preference
    Vector3d<double> v_pref;
    // Acceleration
    Vector3d<double> a;
    // orientation of agent
    double angle;
    // Cognition range
    double rcog;
    // index of agent in the simulation
    int index;
    // Time on food
    double timeonfood;
    // Access to arena
    Arena3D* arena;
    // Forces applioed on agent, interaction force, response to environment, friction, inherent noise
    Vector3d<double> Fint, Fres, Ffric, Fnoise; 
    // Point of aim
    Vector3d<double> aim;



    public:
    /**
     * @brief Construct a new Fly3D agent
     * 
     * @param position Vector3D starting position
     * @param index index of agent in list
     * @param arena arena in which agent is in
     */
    Fly3D(const Vector3d<double>& position, const int& index, Arena3D* arena = nullptr);

    /**
     * @brief Construct a new Fly3D
     * 
     * @param x x position
     * @param y y position
     * @param z z position
     * @param index index of agent in list
     * @param arena arena in which agent is in
     */
    Fly3D(const double& x, const double& y, const double& z, const int& index, Arena3D* arena = nullptr);

    /**
     * @brief Construct a new Fly3D
     * 
     * @param room starting room, center of the room
     * @param index index of agent in list
     * @param arena arena in which agent is in
     */
    Fly3D(const int& room, const int& index, Arena3D* arena = nullptr);

    /**
     * @brief Get room of agent
     * 
     * @return int room
     */
    int GetRoom() const;

    /**
     * @brief Get the agent's position
     * 
     * @return Vector3d<double> position
     */
    Vector3d<double> GetPosition() const;

    /**
     * @brief Get the agent's velocity
     * 
     * @return Vector3d<double> velocity vector
     */
    Vector3d<double> GetVelocity() const;

    /**
     * @brief Get agent's prefered velocity
     * 
     * @return Vector3d<double> preferred velocity
     */
    Vector3d<double> GetVelocitypref() const;

    /**
     * @brief Get repsonse force, response to environment 
     * 
     * @return Vector3d<double> 
     */
    Vector3d<double> GetFres() const;

    /**
     * @brief Get agent's aim
     * 
     * @return Vector3d<double> aim
     */
    Vector3d<double> GetAim() const;

    /**
     * @brief Get the Angle object
     * 
     * @return double 
     */
    double GetAngle() const;

    /**
     * @brief Get the arena in which the fly
     * 
     * @return Arena3D* 
     */
    Arena3D* GetArena();

    /**
     * @brief Get the time spent on food by the agent
     * When the agent is in the same room as the food, time on food increases
     * 
     * @return double timeonfood
     */
    double GetTimeOnFood() const; 

    /**
     * @brief Set aiming point
     * 
     * @param point point of aim
     */
    void SetAim(const Vector3d<double>& point);
    
    /**
     * @brief Set aiming point
     * 
     * @param x coordinate
     * @param y coordinate
     * @param z coordinate
     */
    void SetAim(const double& x, const double& y, const double& z);

    /**
     * @brief Update agent, updates each component of the agent
     * 
     * @param dt timestep
     */
    void Update(const double& dt);

    /**
     * @brief Update agent's angle
     * 
     */
    void UpdateAngle();

    /**
     * @brief Update forces
     * 
     */
    void UpdateForces();

    /**
     * @brief Updates response force
     * 
     */
    void UpdateFres();

    /**
     * @brief Updates interaction force
     * 
     */
    void UpdateFint();

    /**
     * @brief Updates friction force 
     * 
     */
    void UpdateFfric();

    /**
     * @brief Updates noise force
     * 
     */
    void UpdateFnoise();

    /**
     * @brief Updates room index 
     * 
     */
    void UpdateRoom();

    /**
     * @brief Updates preferred velocity
     * 
     * @param dt timestep
     */
    void UpdateVpref(const double& dt);
    /**
     * @brief Updates velocity
     * 
     * @param dt timestep 
     */
    void UpdateV(const double& dt);

    /**
     * @brief Updates position
     * 
     * @param dt timestep
     */
    void UpdatePosition(const double& dt);

    /**
     * @brief Updates time on food
     * 
     * @param dt timestep
     */
    void UpdateTimeOmFood(const double& dt);

    /**
     * @brief Generate new aiming point for the agent
     * 
     */
    void GenerateNewAim();

    /**
     * @brief Updates aiming point
     * 
     * @param dt timestep 
     */
    void UpdateAim(const double& dt);

};

#endif