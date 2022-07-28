#include <iostream>
#include <vector>
#include "Vector3D.h"
#include "Cuboid.h"

Cuboid::Cuboid(const Vector3d<double>& c1, const Vector3d<double>& c2, const Vector3d<double>& c3, const Vector3d<double>& c4, const double& z) {
    // Height vector
    Vector3d<double> height (0, 0, z);

    // Coordinates initialization
    this->coord[0] = c1;
    this->coord[1] = c2;
    this->coord[2] = c3;
    this->coord[3] = c4;
    this->coord[4] = c1 + height;
    this->coord[5] = c2 + height;
    this->coord[6] = c3 + height;
    this->coord[7] = c4 + height;

}

Cuboid::Cuboid(const Vector3d<double>& p, const double& length, const double& width, const double& height) {

    // Coordinates initialization
    this->coord[0] = p;
    this->coord[1] = Vector3d<double>(p.x + length, p.y, p.z);
    this->coord[2] = Vector3d<double>(p.x + length, p.y + width, p.z);
    this->coord[3] = Vector3d<double>(p.x, p.y + width, p.z);
    this->coord[4] = p + Vector3d<double> (0, 0, height);
    this->coord[5] = Vector3d<double>(p.x + length, p.y, p.z + height);
    this->coord[6] = Vector3d<double>(p.x + length, p.y + width, p.z + height);
    this->coord[7] = Vector3d<double>(p.x, p.y + width, p.z + height);
}

std::vector<Vector3d<double> > Cuboid::GetCoord() const{

    std::vector<Vector3d<double> > coord;
    // Fill coordinate vector
    coord.push_back(this->coord[0]);
    coord.push_back(this->coord[1]);
    coord.push_back(this->coord[2]);
    coord.push_back(this->coord[3]);
    coord.push_back(this->coord[4]);
    coord.push_back(this->coord[5]);
    coord.push_back(this->coord[6]);
    coord.push_back(this->coord[7]);
    return  coord;
}

int Cuboid::GetNbSides() const{
    return 4;
}

int Cuboid::GetNbFaces() const{
    return 6;
}

double Cuboid::GetLength() const{
    return EuclideanNorm(this->coord[1] - this->coord[0]);
}

double Cuboid::GetWidth() const{
    return EuclideanNorm(this->coord[3] - this->coord[0]);
}

double Cuboid::GetHeight() const{
    return EuclideanNorm(this->coord[4] - this->coord[0]);
}

Vector3d<double> Cuboid::GetLengthVec() const{ return (this->coord[1] - this->coord[0]) / this->GetLength();}

Vector3d<double> Cuboid::GetWidthVec() const{ return (this->coord[3] - this->coord[0]) / this->GetWidth();}

Vector3d<double> Cuboid::GetHeightVec() const{ return (this->coord[4] - this->coord[0]) / this->GetHeight();}

Vector3d<double> Cuboid::GetCenter() const{ return (this->coord[0] + this->coord[6]) / 2.0;}

std::vector<std::vector< Vector3d<double> > > Cuboid::GetFaces() const{
    std::vector<std::vector<Vector3d<double> > > vec;
    for(int i = 0; i < this->GetNbFaces(); i++){
        vec.push_back(this->GetFace(i));
    }

    return vec;
}

std::vector<Vector3d<double> > Cuboid::GetFace(const int& face) const{
    // Point, normal pair vector
    std::vector<Vector3d<double> > vec;
    // Point of plane
    Vector3d<double> c;
    // Normal of plane
    Vector3d<double> n;
    switch (face)
    {
    case 0:
        n = CrossProduct(coord[1] - coord[0], coord[3] - coord[0]);
        c = coord[0];

        break;
    case 1:
        n = CrossProduct(coord[1] - coord[0], coord[4] - coord[0]);
        c = coord[0];

        break;
    case 2:
        n = CrossProduct(coord[5] - coord[1], coord[2] - coord[1]);
        c = coord[1];

        break;

    case 3:
        n = CrossProduct(coord[6] - coord[2], coord[3] - coord[2]);
        c = coord[2];

        break;
    case 4:
        n = CrossProduct(coord[0] - coord[3], coord[7] - coord[3]);
        c = coord[3];

        break;
    case 5:
        n = CrossProduct(coord[5] - coord[4], coord[7] - coord[4]);
        c = coord[4];

        break;
    default:
        break;
    }
    vec.push_back(n);
    vec.push_back(c);
    
    return vec;
}

bool Cuboid::PointInBB(const Vector3d<double>& point){

    bool x (point.x >= std::min(std::min(this->coord[0].x, this->coord[1].x), std::min(this->coord[2].x, this->coord[3].x)) 
                && point.x <= std::max(std::max(this->coord[0].x, this->coord[1].x), std::max(this->coord[2].x, this->coord[3].x)));
    
    bool y (point.y >= std::min(std::min(this->coord[0].y, this->coord[1].y), std::min(this->coord[2].y, this->coord[3].y)) 
                && point.y <= std::max(std::max(this->coord[0].y, this->coord[1].y), std::max(this->coord[2].y, this->coord[3].y)));
    
    bool z (point.z >= std::min(std::min(std::min(this->coord[0].z, this->coord[4].z) , this->coord[1].z), std::min(this->coord[2].z, this->coord[3].z)) 
                    && point.z <= std::max(std::max(std::max(this->coord[0].z, this->coord[4].z) , this->coord[1].z), std::max(this->coord[2].z, this->coord[3].z)));
    return x && y && z;
}

 

bool Cuboid::PointInBB(const double& x, const double& y, const double& z){
    return this->PointInBB(Vector3d<double>(x, y, z));
}

bool Cuboid::PointIsInside(const Vector3d<double>& point) {
    // Check if two points are on the same with each plane
    bool flag = true;

    for(int i = 0; i<GetNbFaces(); i++){
        // Normal vector
        Vector3d<double> n = GetFace(i)[0];
        // Point of face
        Vector3d<double> p0 = GetFace(i)[1];
        Vector3d<double> p = GetCenter();
        double sign = DotProduct(n, point - p0) / fabs(DotProduct(n, point - p0));
        double sign0 = DotProduct(n, p - p0) / fabs(DotProduct(n, p - p0));

        if(sign != sign0){
            flag = false;
        }
    }

    return flag;
}

bool Cuboid::PointIsInside(const double& x, const double& y, const double& z){
    return this->PointIsInside(Vector3d<double>(x, y, z));
}

