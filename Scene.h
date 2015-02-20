#ifndef __SCENE_H__
#define __SCENE_H__


#include "Ray.h"
#include "Shape.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Sphere.h"
#include "Triangle.h"
#include "vector3.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Scene{
public:
	unsigned char *ImageMatrix;

	Scene(string FilePath);
	void ParseScene(string);
	Camera ReadCam(ifstream&);
	Material ReadMaterial(ifstream&);
	Shape* ReadTri(ifstream&);
	Shape* ReadSph(ifstream&);
	Light ReadLight(ifstream&);
	
	int getWidth();
	int getHeight();
	
	Vector3 GetPxPos(int indX, int indY);
	void GetPxIndex(Vector3 pixelPos, int& indX, int& indY);
	Ray GetRay(Vector3 pxPos, Vector3 camPos);
	Ray GetRay(int pxIndX, int pxIndY, Vector3 camPos);
	void Render();
	void SetPxColor(int indX, int indY, unsigned char r, unsigned char g, unsigned char b);
	
	float getDiffuseR(Vector3 point, Light myLight, float kdR, Vector3 normal);
	float getDiffuseG(Vector3 point, Light myLight, float kdG, Vector3 normal);
	float getDiffuseB(Vector3 point, Light myLight, float kdB, Vector3 normal);
	
	float getSpecR(Vector3 point, Light myLight, float speR, Vector3 normal, int exp, Vector3 bakis);
	float getSpecG(Vector3 point, Light myLight, float speG, Vector3 normal, int exp, Vector3 bakis);
	float getSpecB(Vector3 point, Light myLight, float speB, Vector3 normal, int exp, Vector3 bakis);
	
	void RayColor(Ray viewingRay, float &colorR, float &colorG, float &colorB, int refCount, int flag);
	
	
	void print();
private:
	int ImageWidth, ImageHeight;
	float TMin;
	int RayReflectCount;
	int IAmbR, IAmbG, IAmbB; //ambient light’s intensity
	int backR, backG, backB; //background values
	Camera SceneCam;
	Vector3 vpBottomLeft, vpBottomRight, vpTopLeft, vpTopRight; //viewport corners
	float PixelSizeX, PixelSizeY;
	vector<Material> MaterialList;
	vector<Shape*> ShapeList;
	vector<Light> LightList;
};

#endif
