#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "Ray.h"
#include <string>
#include <fstream>
#include <vector>
class Shape{
public:
	virtual float SIntersect(Ray ToIn) = 0;
	virtual int GetMaterial() = 0;
	virtual Vector3 GetNormal(Vector3 intPoint) = 0;
};

#endif
