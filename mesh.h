#ifndef MESH_H
#define MESH_H

#include "defines.h"

#include "c_math.h"
#include <vector>

// typedef Vec3 Triangle;

struct Triangle
{
    Vec3 p[3]; 
};

struct Mesh
{
    std::vector<Triangle> tris;
};

#endif // MESH_H