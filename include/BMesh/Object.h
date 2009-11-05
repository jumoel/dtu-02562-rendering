#ifndef __BOBJECT_H__
#define __BOBJECT_H__

#include "TriMesh.h"
#include "Texmap.h"
#include "Material.h"

#include <vector>
#include <string>

/* TODO:

It is quite clear, that a smart pointer type should be used for the pointers to
meshes texmaps and materials. For instance, the boost smart pointer class.
*/


namespace BMesh
{
  class Object 
  {
    std::vector<TriMesh*> meshes;
    std::vector<Texmap*> texmaps;
    std::vector<Material*> materials;
    std::string id;
	  
  public:
		
    int no_meshes() const {return meshes.size();}
    int no_texmaps() const {return texmaps.size();}
    int no_materials() const {return materials.size();}
	
    TriMesh* create_mesh()  
    {
      TriMesh* ptr = new TriMesh();
      meshes.push_back(ptr);
      return ptr;
    }
    Texmap* create_texmap()  
    {
      Texmap* ptr = new Texmap();
      texmaps.push_back(ptr);
      return ptr;
    }
    Material* create_material()  
    {
      Material* ptr = new Material();
      materials.push_back(ptr);
      return ptr;
    }
	
    TriMesh* get_mesh(int i) const {return meshes[i];}
    Texmap* get_texmap(int i) const {return texmaps[i];}
    Material* get_material(int i) const {return materials[i];}

    void get_bsphere(CGLA::Vec3f& center, float& radius);
    void get_bbox(CGLA::Vec3f& p0, CGLA::Vec3f& p7);

    void init_draws();
    bool has_alpha();

    void clear()
    {
      meshes.clear();
      texmaps.clear();
      materials.clear();
    }

    virtual ~Object();

  };
}
#endif
