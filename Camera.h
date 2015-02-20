#ifndef __CAMERA_H__
#define __CAMERA_H__


#include "vector3.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;
class Camera{
public:
	Camera(float, float, float, float, float, float, float, float, float, float, float, float, float, float);
	Camera(){};
	Vector3 getPosition(){return Position;};
	Vector3 getGaze(){return Gaze;};
	Vector3 getUp(){return Up;};
	Vector3 getUAxis(){return UAxis;};
	
	float Left, Right, Bottom, Top;//privattan public e cektim
	float distance;	
private:
	//float CamX, CamY, CamZ;
	Vector3 Position;
	Vector3 Gaze;
	Vector3 Up;
	Vector3 UAxis;
};


#endif
