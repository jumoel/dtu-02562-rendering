#ifndef __COLORVECTOR_H
#define __COLORVECTOR_H

#include <iostream>

#include <algorithm>
#ifdef WIN32
#include <minmax.h>
#endif

#include "CGLA/Vec3f.h"

#include "Common/CommonDefs.h"

namespace Graphics
{

	/// This class represents a colour as a 3D vector (r,g,b). 
	class ColorVector
	{
		/// red component of colour vector
		float red;
		/// green component of colour vector
		float green;
		/// blue component of colour vector
		float blue;

	public:

		/// Default constructor. Constructs a black colorvector.
		ColorVector(): red(0),green(0),blue(0) {};

#ifdef WIN32
		/// Construct a colorvector with the specified colors.
		ColorVector(float _red, float _green, float _blue):
			red(max(float(0), min(float(1), _red))), 
			green(max(float(0),min(float(1), _green))), 
			blue(max(float(0),min(float(1), _blue))) 
		{}

		ColorVector(const CGLA::Vec3f& v):
			red(max(float(0), min(float(1),  v[0]))), 
			green(max(float(0),min(float(1), v[1]))), 
			blue(max(float(0),min(float(1),  v[2]))) 
		{}


#else
		/// Construct a colorvector with the specified colors.
		ColorVector(float _red, float _green, float _blue):
			red(std::max(float(0), std::min(float(1), _red))), 
			green(std::max(float(0),std::min(float(1), _green))), 
			blue(std::max(float(0),std::min(float(1), _blue))) 
		{}

		ColorVector(const CGLA::Vec3f& v):
			red(std::max(float(0), std::min(float(1),  v[0]))), 
			green(std::max(float(0),std::min(float(1), v[1]))), 
			blue(std::max(float(0),std::min(float(1),  v[2]))) 
		{}

#endif

		operator CGLA::Vec3f() const { return CGLA::Vec3f(red,green,blue);}

		/// Vector subscript, Get a component 
		const float& operator[](int) const;
  
		/** Vector subscript, Get a component.  The version of 
				the operator below returns an lvalue and, hence may
				be used for assignment */
		float & operator[](int);

 
		/// Assignment add a colorvector, and clamp the value at std::max intensity.
		void operator += (const ColorVector&);

		/// Assignment add a colorvector, and clamp the value at std::max intensity.
		void operator *= (const ColorVector&);


		/// Add two colorvectors, and clamp the value at std::max intensity.
		ColorVector operator + (const ColorVector&) const;

		/** Multiply two colorvectors by multiplying each component and
				return the resultant vector. Usually one of the vectors 
				represent a material and the other light incident on a surface
				made of this material */
		ColorVector operator * (const ColorVector&) const;

		/// Modify the colorvector by multiplying it with a constant
		ColorVector operator * (float) const;

		/** For the benefit of X we need a function that converts the 
				colorvector to a representation as an unsinged long int. */
		unsigned long bgrval() const;

		/// In a ppm bitmap each color is represented as a char.
		void set_PPM_style(unsigned char*) const;

		/// Return the largest component of the color vector
		float max_contrib() const;
	};


	inline const float& ColorVector::operator[](int i) const
	{
		switch(i)
			{
			case 0:
				return red;
			case 1:
				return green;
			case 2:
				return blue;
			}
		assert(0);
		return blue;
	}
  
	inline float & ColorVector::operator[](int i)
	{
		switch(i)
			{
			case 0:
				return red;
			case 1:
				return green;
			case 2:
				return blue;
			}
		assert(0);
		return blue;
	}


	inline std::ostream& operator<<(std::ostream& os, const ColorVector cv)
	{
		os << "<red " << cv[0] << " green " << cv[1] 
			 << " blue " << cv[2] << ">" << std::endl;
		return os;
	}


	inline void ColorVector::operator += (const ColorVector& cv)
	{
#ifdef WIN32
		red   = min(float(1), red   + cv.red);
		green = min(float(1), green + cv.green);      
		blue  = min(float(1), blue  + cv.blue);
#else
		red   = std::min(float(1), red   + cv.red);
		green = std::min(float(1), green + cv.green);      
		blue  = std::min(float(1), blue  + cv.blue);
#endif
	}

	inline void ColorVector::operator *= (const ColorVector& cv)
	{
		red   = red   * cv.red;
		green = green * cv.green;      
		blue  = blue  * cv.blue;
	}


	inline ColorVector ColorVector::operator + (const ColorVector& cv) const 
	{
#ifdef WIN32
		return ColorVector(min(float(1), red + cv.red),
											 min(float(1), green + cv.green),
											 min(float(1), blue + cv.blue));
#else
		return ColorVector(std::min(float(1), red + cv.red),
											 std::min(float(1), green + cv.green),
											 std::min(float(1), blue + cv.blue));

#endif
	}

	inline ColorVector ColorVector::operator * (const ColorVector& coeff) const
	{
		return ColorVector(red   * coeff.red   ,
											 green * coeff.green ,
											 blue  * coeff.blue  );
	}



	inline ColorVector ColorVector::operator * (float k) const
	{
		assert(k>=0);
#ifdef WIN32
		return ColorVector(min(float(1), red   * k),
											 min(float(1), green * k),
											 min(float(1), blue  * k));
#else
		return ColorVector(std::min(float(1), red   * k),
											 std::min(float(1), green * k),
											 std::min(float(1), blue  * k));
#endif
	}

	inline unsigned long ColorVector::bgrval() const 
	{
		int ired   = int( 255.0 * red);
		int igreen = int( 255.0 * green);
		int iblue  = int( 255.0 * blue);

#ifdef LINUX
		return (ired << 16) + (igreen << 8) + iblue;
#else
		return (iblue << 16) + (igreen << 8) + ired;
#endif
	}

	inline void ColorVector::set_PPM_style(unsigned char* pix) const
	{
		unsigned char ired   = (unsigned char)( 255.0 * red);
		unsigned char igreen = (unsigned char)( 255.0 * green);
		unsigned char iblue  = (unsigned char)( 255.0 * blue);

		*pix     = ired;
		*(pix+1) = igreen;
		*(pix+2) = iblue;

		return;
	}

	inline float ColorVector::max_contrib() const
	{
#ifdef WIN32
		return max(max(red,green), blue);
#else
		return std::max(std::max(red,green), blue);
#endif
	}



	/// For convenience, I provided a (very) few Colour constants
	const ColorVector RED   = ColorVector(1,0,0);
	/// For convenience, I provided a (very) few Colour constants
	const ColorVector GREEN = ColorVector(0,1,0);
	/// For convenience, I provided a (very) few Colour constants
	const ColorVector BLUE  = ColorVector(0,0,1);
	/// For convenience, I provided a (very) few Colour constants
	const ColorVector WHITE = ColorVector(1,1,1);
}
#endif 
