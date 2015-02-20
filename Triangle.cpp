#include <cfloat>
#include "Triangle.h"
#include <iostream>

using namespace std;

Triangle::Triangle(Vector3 a, Vector3 b, Vector3 c, int matI, float mint){
	Vertex_a = a;
	Vertex_b = b;
	Vertex_c = c;
	MaterialIndex = matI;
	t_min = mint;
	normal = (Vertex_b - Vertex_a).cross(Vertex_c - Vertex_a);
	normal.normalize();
}


float Triangle::SIntersect(Ray ToIn){
	ab = Vertex_a - Vertex_b;
	ac = Vertex_a - Vertex_c;
	dir = ToIn.getDirection();
	ao = Vertex_a - ToIn.getOrigin();
	
	A = determinant(
							ab.x(), ac.x(), dir.x(),
							ab.y(), ac.y(), dir.y(),
							ab.z(), ac.z(), dir.z()
						);
						
	ToIn.t = determinant(
						ab.x(), ac.x(), ao.x(),
						ab.y(), ac.y(), ao.y(),
						ab.z(), ac.z(), ao.z()
						) / A;			
	
	/*if((ToIn.t < t_min))//t checki ne olcak
		return FLT_MAX;*/
						
	beta = determinant(
						ao.x(), ac.x(), dir.x(),
						ao.y(), ac.y(), dir.y(),
						ao.z(), ac.z(), dir.z()	
						) / A;
	if(beta <= 0)
		return FLT_MAX;
	gamma = determinant(
						ab.x(), ao.x(), dir.x(),
						ab.y(), ao.y(), dir.y(),
						ab.z(), ao.z(), dir.z()
						) / A;
	if(gamma <= 0)
		return FLT_MAX;
	else if((beta + gamma) >= 1)
		return FLT_MAX;
	else
		return ToIn.t;
}


float Triangle::determinant(float a, float b, float c, float d, float e, float f, float g, float h, float i){
	float retval = a * e * i + b * f * g + c * d * h - c * e * g - b * d * i - a * f * h;
	return retval;
}
