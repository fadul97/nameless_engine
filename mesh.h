#ifndef MESH_H
#define MESH_H

#include "defines.h"

/*
    Resources: 
        David Barr (Javidx9) - OneLoneCoder
            https://github.com/OneLoneCoder/Javidx9/blob/master/ConsoleGameEngine/BiggerProjects/Engine3D/OneLoneCoder_olcEngine3D_Part2.cpp
            https://www.youtube.com/watch?v=XgMWc6LumG4
*/

#include "c_math.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

// typedef Vec3 Triangle;

struct Triangle
{
    Vec4 p[3]; 
};


struct Mesh
{
    std::vector<Triangle> tris;

    u8 load_from_obj_file(std::string file_name)
    {
        std::ifstream f(file_name);
		if(!f.is_open())
			return ERR_OBJ_LOADER;
        
        // Local cache of verts
		std::vector<Vec4> verts;

        while(!f.eof())
		{
			char line[128];
			f.getline(line, 128);

			std::stringstream s;
			s << line;

			char junk;

			if(line[0] == 'v')
			{
				Vec4 v;
				s >> junk >> v.x >> v.y >> v.z;
                v.w = 1.0f;
				verts.push_back(v);
			}

			if(line[0] == 'f')
			{
				int f[3];
				s >> junk >> f[0] >> f[1] >> f[2];
				tris.push_back({verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1]});
			}
		}
    
        return OK;
    }
};

#endif // MESH_H