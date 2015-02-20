#include "Light.h"

using namespace std;


Light::Light(float x, float y, float z, int r, int g, int b){
	Vector3 tvec(x, y, z);
	Pos = tvec;
	iR = r;
	iG = g;
	iB = b;
}
