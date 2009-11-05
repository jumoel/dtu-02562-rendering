#include "BMesh/Object.h"

using namespace std;
using namespace CGLA;

namespace BMesh
{

  Object::~Object()
  {
  }

  void Object::get_bbox(CGLA::Vec3f& p0, CGLA::Vec3f& p7)
  {
    // Find center and radius
    Vec3f old_p0, old_p7;
		
    meshes[0]->get_bbox(p0,p7);
    for(int i=1;i<meshes.size();i++) 
      {
	old_p0 = p0;
	old_p7 = p7;
	meshes[i]->get_bbox(p0,p7);				
	p0 = v_min(old_p0, p0);
	p7 = v_max(old_p7, p7);
      }
  }

  void Object::get_bsphere(CGLA::Vec3f& center, float& radius)
  {
    Vec3f p0,p7;
    get_bbox(p0, p7);
    Vec3f r = (p7-p0)*0.5f;
    center = p0 + r;
    radius = r.length();
  }


  bool Object::has_alpha() {
    for(int i=0;i<meshes.size();i++) {
      int mtl_id = meshes[i]->get_mtl_index();
      if (mtl_id!=-1 && mtl_id<texmaps.size()) 
	if (texmaps[mtl_id]->bpp==32)
	  return true;
    }
    return false;
  }
}
