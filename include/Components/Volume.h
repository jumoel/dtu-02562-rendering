#ifndef __VOLUME_H
#define __VOLUME_H

#include <vector>
#include <deque>
#include <stack>

#include "CGLA/Vec3f.h"
#include "Common/ExceptionStandard.h"

namespace Components
{

	/// Create a general volume exception
DERIVEEXCEPTION(VolumeException,CMN::MotherException);


	/** The Volume class.
			The Volume class is a very general class that represents the concept of 
			a box shaped enclosure in space. It has functionality for transforming 
			points between world and volume coordinates and functions to check for 
			intersection */
	class Volume
	{
	protected:

		/// Two corners of the volume
		CGLA::Vec3f vol_crnr1,vol_crnr2;
  
	public:
  

		/// Default constructor. Constructs the unit volume
		Volume(): vol_crnr1(0,0,0), vol_crnr2(1.0,1.0,1.0) {}
		/// Not so default constructor. Constructs volume with specified dims.
		Volume(const CGLA::Vec3f& _vol_crnr1, const CGLA::Vec3f& _vol_crnr2): 
			vol_crnr1(_vol_crnr1), vol_crnr2(_vol_crnr2) {}

		void set_corners(const CGLA::Vec3f& _vol_crnr1, const CGLA::Vec3f& _vol_crnr2)
		{
			vol_crnr1 = _vol_crnr1;
			vol_crnr2 = _vol_crnr2;
		}
	
		/// Find two diagonally opposite corners
		void get_corners(CGLA::Vec3f& v1, CGLA::Vec3f& v2) const
		{
			v1 = vol_crnr1;
			v2 = vol_crnr2;
		}
	
		virtual ~Volume() {};
  
		/// Check whether a point is inside the volume
		bool is_inside(const CGLA::Vec3f& v) const
		{
			if (vol_crnr1.all_le(v) && vol_crnr2.all_ge(v))
				return true;
			return false;
		}
	};
}

namespace CMP = Components;


#endif






