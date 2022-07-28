#ifndef WALL_H
#define WALL_H

#include <vector>
#include "Vector3D.h"
#include "Cuboid.h"
#include "Entrance.h"

class Arena3D;

//Object limiting movement within the arena
class Wall : public Cuboid {

    private:
    // List of entrances
    std::vector<Entrance> ents;
    // Arena pointer
    Arena3D* arena;

    /**
     * @brief Create non overlapping entrances on the wall 
     * 
     * @param nb_ent number of entrances
     * @param length_e length of entrances
     */
    void BuildEntrances(const int& nb_ent, const double& length_e);

    public:
    //Constructor
    /**
     * @brief Construct a new Wall object using 4 points
     * 
     * @param c1 point one
     * @param c2 point two
     * @param c3 point three
     * @param c4 point four
     * @param h height of wall
     * @param nb_ent number of entrances
     * @param arena 
     */
    Wall(const Vector3d<double>& c1, const Vector3d<double>& c2, const Vector3d<double>& c3, const Vector3d<double>& c4, double h, int nb_ent, Arena3D* arena = nullptr);

    /**
     * @brief Construct a new Wall object using a starting point, a length and a width
     * 
     * @param p a starting point
     * @param length length of the wall
     * @param width width of the wall
     * @param h height of wall
     * @param nb_ent number of entrances
     * @param arena
     */
    Wall(const Vector3d<double>& p, const double& length, const double& width, double h, int nb_ent, Arena3D* arena = nullptr);

    /**
     * @brief Get the Entrances 
     * 
     * @return std::vector<Entrance> list of entrances
     */
    std::vector<Entrance> GetEntrances() const;

    /**
     * @brief Get the number of entrances in wall
     * 
     * @return int number of entrances
     */
    int GetNbEnts() const;


};

#endif