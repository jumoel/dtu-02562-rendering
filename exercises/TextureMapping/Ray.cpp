#include <iostream>
#include <assert.h>
#include <math.h>
#include "Common/CommonDefs.h"
#include "Ray.h"

using namespace CGLA;
using namespace CMN;
using namespace std;


bool Ray::cond_set_parameter(const float par, const Object3D * o)
{
	// Sets the parameter of the ray to par, if par is closer to the 
	// origin than any other previous intersection
	// If the ray hits, then the object hit is also.

	if (par<get_parameter() && par > SMALLEST_DIST)
		{
			hit = true;
			t = par;
			obj = o;
			return true;
		}
	return false;
}
