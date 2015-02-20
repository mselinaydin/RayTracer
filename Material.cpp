
#include "Material.h"

using namespace std;

Material::Material(float aR, float aG, float aB, float dR, float dG, float dB, float sR, float sG, float sB, int P, float rR, float rG, float rB){

	ambR = aR;
	ambG = aG;
	ambB = aB;
	difR = dR;
	difG = dG;
	difB = dB;
	speR = sR;
	speG = sG;
	speB = sB;
	speExpP = P;
	refR = rR;
	refG = rG;
	refB = rB;	
}
