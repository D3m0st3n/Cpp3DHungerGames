#include <iostream>
#include <vector>
#include "Vector3D.h"
#include "Cuboid.h"
#include "Wall.h"
#include "Entrance.h"

Entrance::Entrance(const Vector3d<double>& c1, const Vector3d<double>& c2, const Vector3d<double>& c3, const Vector3d<double>& c4, const double& h, const bool& isFake,  Wall* wall) : Cuboid(c1, c2, c3, c4, h), isFake(isFake) {
    this->wall = wall;
}
Entrance::Entrance(const Vector3d<double>& p, const double& length, const double& width, const double& height, const bool& isFake, Wall* wall) : Cuboid(p, length, width, height), isFake(isFake) {
    this->wall = wall;
}

bool Entrance::IsFake(){ return isFake;}