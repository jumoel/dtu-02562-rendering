#ifndef __STANDARDSURFACE_H
#define __STANDARDSURFACE_H

#include "Surface.h"
#include "Ray.h"
#include "FileUtils.h"

class World;

// The constants below should be configurable, 
// but for now, they are constants.

// How many times can a ray be reflected ?!
const int MAX_RECURSION_DEPTH = 5;

/** The surface class represents the notion of a surface - decoupled
		from  geometry. Thus a surface instance may be associated with an
		arbitrary  number of Object3D's. A Surface knows how to shade a ray
		and how to transmit a photon. A Surface also knows about the
		World, because it may have to store a photon or trace a specular
		or transmitted ray. */
class Surface
{
	World* world;
  char *surfacefn;
  void* surfacedata;
  int surfacewidth;
  int surfaceheight;

public:

	// Variables below are all public because it is more intuitive to set them
	// individually than to pass a long string of arguments to the constructor.

	/** Colour of surface. There is only one meaning that the highlight
			is the same colour as the diffuse reflection. This is often _not_
			what you want ... so change it ;-) */
	CGLA::Vec3f color; 
	
	/// Lambertian reflectance
	float k_diffuse;      
	
	/// Highlight a la Phong
	float k_highlight;    
	
	/// Contribution from reflections
	float k_reflected;  
  
	/// Contribution from transmission
	float k_transmitted;

	/// Contribution from ambient light
	float k_ambient;
  
	/// Refraction index
	float refraction_index;

	/// Phong exponent
	float phong_exponent;

  /*	Create checkerboard texture	*/
#define	checkImageWidth 64
#define	checkImageHeight 64
unsigned char checkImage[checkImageWidth][checkImageHeight][3];
void makeCheckImage(void)
{
    int i, j, c;
    
    for (i = 0; i < checkImageWidth; i++) {
	    for (j = 0; j < checkImageHeight; j++) {
	        c = ((((i&0x8)==0)^((j&0x8))==0))*255;
	        checkImage[i][j][0] = (unsigned char) c;
	        checkImage[i][j][1] = (unsigned char) c;
	        checkImage[i][j][2] = (unsigned char) c;
	    }
    }
}

	Surface(World *w, char *surfacefile = ""):
		world(w), 
		color(0),
		k_diffuse(0.0f), 
		k_highlight(0.0f), 
		k_reflected(0.0f), 
		k_ambient(0.0f), 
		k_transmitted(0.0f), 
		phong_exponent(0.0f), 
		refraction_index(0.0f),
    surfacefn(surfacefile)
    {
      /* Load the texture */
      surfacewidth = 0;
      surfaceheight = 0;
      if (!(surfacefn == "" || surfacefn == NULL)) {
        surfacedata = load_ppm(surfacefn, surfacewidth, surfaceheight);
      }
    }

	/** Shade a ray. This function may trace rays recursively. */
	CGLA::Vec3f shade( const Ray& incident,
										 const CGLA::Vec3f& normal,
										 const bool is_solid);


  CGLA::Vec3f texture_lookup(CGLA::Vec2f texcoords);
};

#endif



