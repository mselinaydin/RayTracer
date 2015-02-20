#ifndef __SPHERE_H__
#define __SPHERE_H__


#include "Ray.h"
#include "Shape.h"
#include "vector3.h"
#include <string>
#include <fstream>
#include <vector>

class Sphere: public Shape{
	
private:
	Vector3 Center;
	float Radius;
	int matIndex;
	
	//optimization
	Vector3 normal;
	float discriminant; //B2-4AC

public:
	virtual float SIntersect(Ray ToIn);
	virtual int GetMaterial(){return matIndex;};	
	virtual Vector3 GetNormal(Vector3 intPoint);
	Sphere(float cx, float cy, float cz, float R, int ind);
};

#endif
