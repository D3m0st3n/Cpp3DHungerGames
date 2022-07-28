#include <iostream>
#include <vector>
#include <chrono>
#include <stdlib.h>

#include "Vector3D.h"
#include "Cuboid.h"
#include "Wall.h"
#include "Arena3D.h"
#include "Simulation3D.h"

using namespace std;
using namespace std::chrono;


int main (int argc, char** argv) {

    cout << "You have entered " << argc<< " arguments:" << "\n";

    Vector3d<double> o (0.0, 0.0, 0.0);
    Vector3d<double> a (1.5, 1.5, 1.5);
    Vector3d<double> b (2.0, 2.0, 2.0);

    // Common operations
    assert(a + a == Vector3d<double>(3.0, 3.0, 3.0));

    assert(a - a == Vector3d<double>(0.0, 0.0, 0.0));

    assert(a * 2.0 == Vector3d<double>(3.0, 3.0, 3.0));

    assert(a / 1.5 == Vector3d<double>(1.0, 1.0, 1.0));

    assert(EuclideanNorm(b) == sqrt(12.0));

    assert(Normal(a) == a / EuclideanNorm(a));

    assert(EuclideanNorm(Normal(a)) == 1.0 );

    assert(DotProduct(a, b) == 9.0);

    assert(CrossProduct(a, b) == Vector3d<double> (0.0, 0.0, 0.0));

    // Segments crossing
    Vector3d<double> aa(-1.0, 0.0, 0.0);
    Vector3d<double> ab(1.0, 0.0, 0.0);
    Vector3d<double> ba(0.0, -1.0, 0.0);
    Vector3d<double> bb(0.0, 1.0, 0.0);
    assert(Intersect(aa, ab, ba, bb) == 1);
    
    assert(GetIntersect(aa, ab, ba, bb) == Vector3d<double> (0.0, 0.0, 0.0));

    // Segments not crossing
    Vector3d<double> ca (-1.0, 0.0, 2.0);
    Vector3d<double> cb (1.0, 0.0, 2.0);
    assert(Intersect(aa, ab, ca, cb) == 0);

    Vector3d<double> bbb (0.0, -0.5, 0.0);
    assert(Intersect(aa, ab, ba, bbb) == 0);

    Vector3d<double> abb (1.0, 0.0, 0.5);
    Vector3d<double> bbbb (0.0, 1.0, 0.5);
    assert(Intersect(aa, abb, ba, bbbb) == 1);

    assert(GetIntersect(aa, abb, ba, bbbb) == Vector3d<double> (0.0, 0.0, 0.25));

    assert(Colinear(o, a, o, b) == 1);

    assert(PointAligned(a, b, o) == 1);

    assert(PointAligned(a, b, Vector3d<double>(2.0, 2.0, 0.0)) == 0);

    Vector3d<double> n (1, 0, 0);
    Vector3d<double> c (1, 0, 0);
    aa  = Vector3d<double> (0,0,0);
    ab  = Vector3d<double> (2, 1, 0);

    assert(IntersectPlane(aa, ab, n, c) == 1);

    assert(GetIntersectPlane(aa, ab, n, c) == Vector3d<double>(1, 0.5, 0));

    std::cout<<"Vec 3D Intersect "<<Intersect(aa, ab, ba, bb)<<GetIntersect(aa, ab, ba, bb)<<"\n"; 

    Vector3d<double> p (1, 1, 0);
    Cuboid C (p, 1.0, 1.0, 1.0);
    std::cout<<"--Cuboid---\n";
    for(int i = 0; i<8; i++){
        std::cout<<" Point "<<i<<" : "<<C.GetCoord()[i]<<"\n";
    }

    std::cout<<" Center point : "<<C.GetCenter()<<"\n";

    std::cout<<"---End---\n\n";

    assert(C.PointIsInside(Vector3d<double> (1.5, 1.5, 0.5)) == 1);
    
    assert(C.PointIsInside(Vector3d<double> (0, 0, 0.5)) == 0);

    
    return 0;
};