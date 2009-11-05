#ifndef __X3DMESH_H__
#define __X3DMESH_H__

#include "CGLA/Mat4x4f.h"
#include "CGLA/Quaternion.h"

#include "TriMesh.h"
#include "Texmap.h"
#include "Material.h"
#include "Object.h"

namespace BMesh
{
  
  class X3DBMesh 
  {
    std::vector<CGLA::Mat4x4f> mat_vec;
    CGLA::Mat4x4f mat;
    Object& obj;
    
    TriMesh*   mesh;
    Texmap* texmap;
    Material* material;
    
    std::string baseurl;
    
  public:
    
    X3DBMesh(Object& _obj, const std::string& _baseurl): 
      mat(CGLA::identity_Mat4x4f()),
      obj(_obj), mesh(0), texmap(0), material(0), baseurl(_baseurl)
    {
    }
      
      
    void parse_indexed_face_set(const char **atts);

    void parse_texture_coordinate(const char **atts);
    void parse_coordinate(const char **atts);
    void parse_color(const char **atts);
    void parse_normal(const char **atts);
      
    void parse_transform(const char **atts);
    void parse_transform_end();
      
      
    void parse_shape()
    {
      assert(mesh==0);
      mesh = obj.create_mesh();
    }
    void parse_shape_end()
    {
      mesh->check_normals();
      mesh=0;
    }
      
    void parse_image_texture(const char **atts); 
    void parse_image_texture_end()
    {
      texmap=0;
    }
      
    void parse_material(const char **atts);
    void parse_material_end()
    {
      material=0;
    }
      
  };
}
#endif
