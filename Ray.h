#ifndef __RAY_H__
#define __RAY_H__


#include "vector3.h"
//#include "Shape.h"
#include <string>
#include <fstream>
#include <vector>

class Ray {
private:
	Vector3 Origin;
	Vector3 Direction;
			
public:
	Ray() : Origin( Vector3(0, 0, 0) ), Direction( Vector3(0, 0, 0) ){};
	Ray(Vector3 vOrg, Vector3 vDir);
	float t;
	Vector3 getDirection(){return Direction;};
	Vector3 getOrigin(){return Origin;};	
};


#endif
