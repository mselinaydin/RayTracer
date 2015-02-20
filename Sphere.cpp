#include "Sphere.h"
#include <cmath>
#include <cfloat>

float Sphere::SIntersect(Ray ToIn){
	Vector3 d = ToIn.getDirection();
	
	Vector3 OC = ToIn.getOrigin() - Center; //(o-c)
	float dede = d.dot(d);
	float opt = d.dot(OC);//for optimization
	discriminant = (opt * opt) - (dede * (OC.dot(OC) - (Radius * Radius)));
	
	if(discriminant < 0)
		return ToIn.t;		
	
	
	float toUse = (d * (-1)).dot(OC);
	if(!discriminant) //sıfırsa// teğet demektir t yi hesaplamak gerekir
	{
		ToIn.t = toUse / dede;
		return ToIn.t;
	}
	else
	{
		//for optimization
		float sqDis = sqrt(discriminant);
		float temp = ( toUse + sqDis ) / dede;
		float temp2 = ( toUse - sqDis ) / dede;
		
		if(temp <= temp2)
			return temp;
		else
			return temp2;		
	}
}
Vector3 Sphere::GetNormal(Vector3 intPoint){
	normal = 2 * (intPoint - Center);
	normal.normalize();
	
	return normal;	
}


Sphere::Sphere(float cx, float cy, float cz, float R, int ind){
	Vector3 tvec(cx, cy, cz);
	Center = tvec;
	Radius = R;
	matIndex = ind;
}
