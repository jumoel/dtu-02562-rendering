//----------------------------------------------------------------------
//	
//
// This file is scanned from HWJ: Realistic image Sythesis Using 
// Photon Mapping, AK Peters, July 2001 by Marianne Bilsted Pedersen, 
// Anders Kyster  & Olav Madsen
//
// It has been slightly modified (October 2002) by Andreas Bærentzen
// in order to use CGLA my Linear Algebra library.
//----------------------------------------------------------------------

#ifndef __PHOTONMAP_H__
#define __PHOTONMAP_H__
 
//___________________________________________________________________
//Photonmap.cpp
//An example implementation of the photonMap datastructure
//
//Henrik Wann Jensen feb. 2001
//___________________________________________________________________

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "CGLA/Quaternion.h"
#include "CGLA/Vec3f.h"

//This is the photon
//The power is not compressed so the size is 28 bytes
struct Photon	
{
	CGLA::Vec3f pos;					        	//photon position
	short plane;						      //splitting plane for kd_tree
	unsigned char theta, phi;			//incoming direction
	CGLA::Vec3f power;       						//photon power (uncompressed)
	unsigned int m_type;
};

// This structure is used only to locate the nearest photons
struct NearestPhotons	
{
	int max;
	int found;
	int got_heap;
	CGLA::Vec3f pos;
	float *dist2;
	const Photon **index;
};

//This is the Photon_map class
class Photon_map	
{
private:

	void balance_segment(
		Photon **pbal,
		Photon **porg,
		const int index,
		const int start,
		const int end );

	void median_split(
		Photon **p,
		const int start,
		const int end,
		const int median,
		const int axis );

	Photon *photons;

	int half_stored_photons;
	int max_photons;
	int prev_scale;

	float costheta[256];
	float sintheta[256];
	float cosphi[256];
	float sinphi[256];

	CGLA::Vec3f bbox_min;			// use bbox_min; 
	CGLA::Vec3f bbox_max;			    // use bbox_max;

public:
	
	Photon_map( int max_phot );
	~Photon_map();

	int stored_photons;

	int getPhotonCount() {
		return stored_photons;
	}

	void store(
		const CGLA::Vec3f& power,               // photon power
		const CGLA::Vec3f& pos,                 // photon position
		const CGLA::Vec3f& dir); 				        // photon direction
			
	void scale_photon_power(
		const float scale );				        // l/(number of emitted photons)

	void balance(void);						        // balance the kd_tree (before use!)
	
	const CGLA::Vec3f irradiance_estimate(
		const CGLA::Vec3f& pos,		          // surface position
		const CGLA::Vec3f& normal,          // surface normal at pos
		const float max_dist,               // max distance to look for photons
		const int nphotons ) const;         // number of photons to use

	void locate_photons(
		NearestPhotons *const np,           // np is used to locate the photons
		const int index ) const;            // call with index = 1

	const CGLA::Vec3f photon_dir(
		const Photon *p) const;            // the photon

};

#endif // __PHOTONMAP_H__
