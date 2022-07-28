#ifndef CUBOID_H 
#define CUBOID_H

#include "Vector3D.h"

class Cuboid{

    protected:
    // Coordinate
    Vector3d<double> coord[8];

    public:
    //Constructor
    /**
     * @brief Construct a new rectangle object using 4 points
     * 
     * @param c1 point one
     * @param c2 point two
     * @param c3 point three
     * @param c4 point four
     * @param z height
     */
    Cuboid(const Vector3d<double>& c1, const Vector3d<double>& c2, const Vector3d<double>& c3, const Vector3d<double>& c4, const double& z);

    // TODO : ADD ORIENTATION PARAMETER TO CREATE TILTED RECT
    /**
     * @brief Construct a new rectangle object using a starting point, a length and a width
     * 
     * @param p a starting point
     * @param length length of the rectangle
     * @param width width of the rectangle
     * @param height height
     */
    Cuboid(const Vector3d<double>& p, const double& length, const double& width, const double& height);

    //Getters
    /**
     * @brief Get the Coord object
     * 
     * @return std::vector< Vector3d<double> > vector of coordinates
     */
    // std::vector< Vector3d<double> > GetCoord_();

    /**
     * @brief Get the coordinates of the rectangle
     * 
     * @return Vector3d<double> vector of coordinates
     */
    std::vector<Vector3d<double> > GetCoord() const;

    /**
     * @brief Get the number of sides of rectangles
     * 
     * @return int number of sides in 2D plane, i.e. 4
     */
    int GetNbSides() const;

    /**
     * @brief Get the number of faces of rectangle
     * 
     * @return int number of faces, i.e. 6
     */
    int GetNbFaces() const;

    /**
     * @brief Get the Length object
     * 
     * @return double length EuclNorm(c2 - c1)
     */
    double GetLength() const;

    /**
     * @brief Get the Width object
     * 
     * @return double width EuclNorm(c4 - c1)
     */
    double GetWidth() const;

    /**
     * @brief Get the Height object
     * 
     * @return double height EuclNorm(c5 - c1)
     */
    double GetHeight() const;

    /**
     * @brief Get the normalized length vector
     * 
     * @return Vector3d<double> coord2 - coord1
     */
    Vector3d<double> GetLengthVec() const;

    /**
     * @brief Get the normalized width vector
     * 
     * @return Vector3d<double> coord4 - coord1
     */
    Vector3d<double> GetWidthVec() const;

    /**
     * @brief Get the normalized height vector
     * 
     * @return Vector3d<double> coord5 - coord1
     */
    Vector3d<double> GetHeightVec() const;

    /**
     * @brief Get the rectangle center
     * 
     * @return Vector3d<double> center coordinate
     */
    Vector3d<double> GetCenter() const;

    /**
     * @brief Get a list of all faces of the polyhedron
     * 
     * @return std::vector<std::vector< Vector3d<double> > > lists of <normal, point> of the plane
     */
    std::vector<std::vector< Vector3d<double> > > GetFaces() const;

    /**
     * @brief Get the face i of the polyhedron
     * 
     * @param face int from 0 to 5
     * @return std::vector<Vector3d<double> > charaterise a plane, <normal, point> belonging to the plane
     */
    std::vector<Vector3d<double> > GetFace(const int& face) const;

    /**
     * @brief Point in Bounding Box NOT RELEVANT IN 3D
     * Only used in 2D
     * 
     * @param point 
     * @return true if point in boudning box
     * @return false if point not in bounding box
     */
    bool PointInBB(const Vector3d<double>& point);
    bool PointInBB(const double& x, const double& y, const double& z);
   
    /**
     * @brief If point in BB, tell if point is inside cuboid
     * Check if all vectors to point are oriented inward, i.e. opposite sign to normal vector of each face
     * 
     * @param point 
     * @return true if point is in rectangle
     * @return false if point not in rectangle
     */
    bool PointIsInside(const Vector3d<double>& point);
    bool PointIsInside(const double& x, const double& y, const double& z);
};

#endif