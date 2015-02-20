
#include "Camera.h"
#include <fstream>

using namespace std;
Camera::Camera(float posX, float posY, float posZ, 
float gazeX, float gazeY, float gazeZ, 
float upX, float upY, float upZ, 
float left, float right, float bottom, float top, float dist){
	
	//CamX = posX;
	//CamY = posY;
	//CamZ = posZ;
	Vector3 temp(posX, posY, posZ);
	Position = temp;	
	Vector3 myVec(gazeX, gazeY, gazeZ);
	Gaze = myVec;
	Vector3 secVec(upX, upY, upZ);
	Up = secVec;
	
	Left = left;
	Right = right;
	Bottom = bottom;
	Top = top;
	distance = dist;
	UAxis = Gaze.cross(Up);
}

