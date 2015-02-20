#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Material{
public:
	Material(float, float, float, float, float, float, float, float, float, int, float, float, float);
	unsigned char getAmbR(){return (unsigned char)ambR;}
	unsigned char getAmbG(){return (unsigned char)ambG;}
	unsigned char getAmbB(){return (unsigned char)ambB;}
	float ambR, ambG, ambB; //the percentage the object reflects each band of ambient light
	float difR, difG, difB;
	float speR, speG, speB;
	int speExpP;
	float refR, refG, refB;
	
};

#endif
