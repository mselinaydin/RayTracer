#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "vector3.h"
#include <string>
#include <fstream>
#include <vector>

class Light{
public:
	Light(float x, float y, float z, int r, int g, int b);

	Vector3 Pos; //world coordinates
	int iR, iG, iB;	
};

#endif
