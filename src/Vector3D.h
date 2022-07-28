#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <tuple>
#include <cmath>
#include <cfloat>
#include <climits>

/*The Vector3d class is an object consisting of simply an x and
  y value. Certain operators are overloaded to make it easier
  for vector math to be performed.*/
template<class T> 
class Vector3d {
public:
    /*The x and y values are public to give easier access for
      outside funtions. Accessors and mutators are not really
      necessary*/
    T x;
    T y;
    T z;

    //Constructor assigns the inputs to x and y.
    Vector3d(): x(T(0)), y(T(0)), z(T(0)) {}
    Vector3d(const T& vx, const T& vy, const T& vz): x(vx), y(vy), z(vz) {}
    Vector3d(const Vector3d& v): x(v.x), y(v.y), z(v.z) {}

    /*The following operators simply return Vector2ds that
      have operations performed on the relative (x, y) values*/
    Vector3d& operator+=(const Vector3d& v) { x += v.x; y += v.y; z += v.z; return *this; }
    Vector3d& operator-=(const Vector3d& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    Vector3d& operator*=(const Vector3d& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
    Vector3d& operator/=(const Vector3d& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

    //Check if the Vectors have the same values (uses pairwise comparison of `std::tuple` on the x,y values of L and R.
    friend bool operator==(const Vector3d& L, const Vector3d& R) { return L.x == R.x && L.y == R.y && L.z == R.z;}//return std::tie(L.x, L.y) == std::tie(R.x, R.y);  }
    friend bool operator!=(const Vector3d& L, const Vector3d& R) { return !(L == R); }

    //Negate both the x and y values.
    Vector3d operator-() const { return Vector3d(-x, -y, -z); }

    //Apply scalar operations.
    Vector3d& operator*=(const T&  s) { x *= s; y *= s; z *= s; return *this; }
    Vector3d& operator/=(const T& s) { x /= s; y /= s; z /= s; return *this; }
};

template<class T> Vector3d<T> operator+(const Vector3d<T>& L, const Vector3d<T>& R) { return Vector3d<T>(L) += R; }
template<class T> Vector3d<T> operator-(const Vector3d<T>& L, const Vector3d<T>& R) { return Vector3d<T>(L) -= R; }
template<class T> Vector3d<T> operator*(const Vector3d<T>& L, const Vector3d<T>& R) { return Vector3d<T>(L) *= R; }
template<class T> Vector3d<T> operator/(const Vector3d<T>& L, const Vector3d<T>& R) { return Vector3d<T>(L) /= R; }

template<class T> Vector3d<T> operator*(const T& s, const Vector3d<T>& v) { return Vector3d<T>(v) *= s; }
template<class T> Vector3d<T> operator*(const Vector3d<T>& v, const T& s) { return Vector3d<T>(v) *= s; }
template<class T> Vector3d<T> operator/(const T& s, const Vector3d<T>& v) { return Vector3d<T>(v) /= s; }
template<class T> Vector3d<T> operator/(const Vector3d<T>& v, const T& s) { return Vector3d<T>(v) /= s; }

//Product functions
template<class T> T DotProduct(const Vector3d<T>& a, const Vector3d<T>& b) {return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));};
template<class T> Vector3d<T> CrossProduct(const Vector3d<T>& a, const Vector3d<T>& b) {return Vector3d<T>(a.y * b.z - a.z * b.y, -(a.x * b.z - a.z * b.x), a.x * b.y - a.y * b.x);};

//Returns the length of the vector from the origin.
template<class T> T EuclideanNorm(const Vector3d<T>& v) {return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));};

//Return the unit vector of the input
// template<class T> Vector3d<T> Normal(const Vector3d<T>& v) {float magnitude = EuclideanNorm(v); return Vector3d<T>(v.x / magnitude, v.y / magnitude, v.z / magnitude);};
template<class T> Vector3d<T> Normal(const Vector3d<T>& v) {return v / EuclideanNorm(v);};


//Return a vector perpendicular to the left.
// template<class T> Vector3d<T> Perpendicular(const Vector3d<T>& v) {return Vector3d<T>(v.y, -v.x);};

//Return true if two line segments intersect.
template<class T> bool Intersect(const Vector3d<T>& aa, const Vector3d<T>& ab, const Vector3d<T>& ba, const Vector3d<T>& bb) {
  
  T t = ((ba.x - aa.x) * (ba.y - bb.y) - (ba.y - aa.y) * (ba.x - bb.x)) / ((ba.y - bb.y) * (ab.x - aa.x) - (ba.x - bb.x) * (ab.y - aa.y));
  T u = ((ab.y - aa.y) * (ba.x - aa.x) - (ab.x - aa.x) * (ba.y - aa.y)) / ((ab.y - aa.y) * (ba.x - bb.x) - (ab.x - aa.x) * (ba.y - bb.y));

  if((t * (ab.z - aa.z) + u * (ba.z - bb.z)) == ba.z - aa.z){
    if((0.0 <= t && t <= 1.0) && (0.0 <= u && u <= 1.0)){
        return true;
    }
  }

  return false;

};

//Return the point where two lines intersect.
template<class T> Vector3d<T> GetIntersect(const Vector3d<T>& aa, const Vector3d<T>& ab, const Vector3d<T>& ba, const Vector3d<T>& bb) {

  T t = ((ba.x - aa.x) * (ba.y - bb.y) - (ba.y - aa.y) * (ba.x - bb.x)) / ((ba.y - bb.y) * (ab.x - aa.x) - (ba.x - bb.x) * (ab.y - aa.y));
  T u = ((ab.y - aa.y) * (ba.x - aa.x) - (ab.x - aa.x) * (ba.y - aa.y)) / ((ab.y - aa.y) * (ba.x - bb.x) - (ab.x - aa.x) * (ba.y - bb.y));

  return Vector3d<T> (aa + t * (ab - aa));
};

// Return true if vector is crossing plane
template<class T> bool IntersectPlane(const Vector3d<T>& aa, const Vector3d<T>& ab, const Vector3d<T>& n, const Vector3d<T>& c, double epsilon = pow(10, -6)){
  Vector3d<T> p = ab - aa;
  T q = DotProduct(n, p);

  if(fabs(q) > epsilon){
    return true;
  }

  return false;

};

template<class T> Vector3d<T> GetIntersectPlane(const Vector3d<T>& aa, const Vector3d<T>& ab, const Vector3d<T>& n, const Vector3d<T>& c, double epsilon = pow(10, -6)){

  Vector3d<T> p = ab - aa;
  T q = DotProduct(n, p);


  Vector3d<T> w = aa - c;
  T fac = - DotProduct(n, w) / q;
  p *= fac;
  return aa + p;


}

template<class T> bool PointOnPlane(const Vector3d<T>& aa, const Vector3d<T>& ab, const Vector3d<T>& n, const Vector3d<T>& c){
  T d = -DotProduct(n, c);
  T abc = DotProduct(n, ab - aa);

  return (abc + d == 0);

}

//Enable vector to be passed to a ostream
template<class T> std::ostream& operator<<(std::ostream& s, const Vector3d<T>& v){ return s << "(" << v.x << ", " << v.y << ", " << v.z << ")";}

// Indicate if two vectors are colinear
template<class T> bool Colinear(const Vector3d<T>& aa, const Vector3d<T>& ab, const Vector3d<T>& ba, const Vector3d<T>& bb){
  Vector3d<T> r = ab - aa;
  Vector3d<T> s = bb - ba;

  Vector3d<T> v = CrossProduct(r, s); 

  return EuclideanNorm(v) == T(0);
};

// Indicate if two vector are colienear and aligned
template<class T> bool Aligned(const Vector3d<T>& aa, const Vector3d<T>& ab, const Vector3d<T>& ba, const Vector3d<T>& bb){
  Vector3d<T> p = ba - aa;
  Vector3d<T> r = ab - aa;
  Vector3d<T> q = bb - ab;
  Vector3d<T> s = bb - ba;

  if(Colinear(aa, ab, ba, bb)){
    Vector3d<T> t = CrossProduct(p, q);

    return EuclideanNorm(t) == T(0);
  }

  else{
    return false;
  }
};

// Indicate if a point is aligned on vector
template<class T> bool PointAligned(const Vector3d<T>& aa, const Vector3d<T>& ab, const Vector3d<T>& c){

  return Colinear(aa, ab, aa, c);
};

// Indicate if a point is on a segment
template<class T> bool PointOnSegment(const Vector3d<T>& aa, const Vector3d<T>& ab, const Vector3d<T>& c){
  if(PointAligned(aa, ab, c)){
    return (c.x >= std::fmin(aa.x, ab.x) && c.x <= std::fmax(aa.x, ab.y)) && (c.y >= std::fmin(aa.y, ab.y) && c.y <= std::fmax(aa.y, ab.y)) && (c.z <= std::fmin(aa.z, ab.z) && c.z >= std::fmax(aa.z, ab.z));
  }
  else{
    return false;
  }
};

#endif