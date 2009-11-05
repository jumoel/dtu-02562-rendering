#include <iostream>

#include "World.h"
#include "Surface.h"

	using namespace CGLA;
	using namespace std;
	using namespace CMN;

	Vec3f Surface::shade( const Ray& incident,
												const Vec3f& normal,
												const bool is_solid ) const
	{
		return color;
	}


