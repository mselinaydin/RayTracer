

#include "Ray.h"
#include <cfloat>

Ray::Ray(Vector3 vOrg, Vector3 vDir){
	Origin = vOrg;
	Direction = vDir;
	t = FLT_MAX;
}
