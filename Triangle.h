#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__


#include "Ray.h"
#include "Shape.h"
#include "vector3.h"
#include <string>
#include <fstream>
#include <vector>

class Triangle:public Shape {
private:
	Vector3 Vertex_a, Vertex_b, Vertex_c;
	float beta, gamma;
	int MaterialIndex;
	Vector3 normal;
	float A;
	
	//bunlara elleşme
	Vector3 ab;
	Vector3 ac;
	Vector3 dir;
	Vector3 ao;
public:
	Triangle(Vector3 a, Vector3 b, Vector3 c, int matI, float mint);
	virtual float SIntersect(Ray ToIn);
	virtual int GetMaterial(){return MaterialIndex;};
	inline float determinant(float, float, float, float, float, float, float, float, float);
	float t_min;
	
	virtual Vector3 GetNormal(Vector3 intPoint){return normal;};
	
};



#endif
