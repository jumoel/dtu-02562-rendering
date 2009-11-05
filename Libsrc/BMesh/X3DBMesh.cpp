#include "BMesh/X3DBMesh.h"
#include <iostream>
#include "Components/Parse.h"

using namespace std;
using namespace CMP;
using namespace CGLA;

namespace BMesh
{
  namespace 
  {
    void coord_index_to_face_vec(const vector<int>& coord_index, vector<Vec3i>& face_vec)
    {
      int tri=0;
      Face face;
      for(int i=0;i<coord_index.size();i++) 
	{
	  if (coord_index[i]==-1) 
	    {
	      tri=0;
	      continue;
	    }
	  switch(tri)
	    {
	    case 0:
	      face[tri] = coord_index[i];
	      tri++;
	      break;
	    case 1:
	      face[tri] = coord_index[i];
	      tri++;
	      break;
	    case 2:
	      face[tri] = coord_index[i];
	      tri++;
	      face_vec.push_back(face);
	      break;
	    default:
	      /* This is not a triangle. We perform a super-naive triangulation. */
	      face[0] = coord_index[i-1];
	      face[1] = coord_index[i];
	      face[2] = coord_index[i-tri];
	      face_vec.push_back(face);
	      tri++;
	      break;
	    }
	}
    }
  }
  
  void X3DBMesh::parse_indexed_face_set(const char **atts) {
    vector<int> coord_index;
    vector<int> normal_index;
    vector<int> tex_coord_index;
    //vector<int> smoothing_groups;
    float crease_angle;
    int j=0,i;
    
    while (atts[j]!=0) {
      if (strcmp(atts[j],"coordIndex")==0) 
	{ 
	  parse(atts[++j],coord_index);
	  coord_index_to_face_vec(coord_index, mesh->faces);
	} 
      else if (strcmp(atts[j],"normalIndex")==0) 
	{ 
	} 
      else if (strcmp(atts[j],"colorIndex")==0) 
	{ 
	} 
      else if (strcmp(atts[j],"texCoordIndex")==0) 
	{
	  parse(atts[++j],tex_coord_index);
	  coord_index_to_face_vec(coord_index, mesh->t_faces);
	} 
      else if (strcmp(atts[j],"creaseAngle")==0) 
	{
	  parse(atts[++j],crease_angle);
	}
      else if (strcmp(atts[j],"smoothing_groups")==0) 
	{
	  //parse(atts[++j],smoothing_groups);
	}
      j++;
    }
  }
  
  void X3DBMesh::parse_texture_coordinate(const char **atts) {
    int j=0;
    while (atts[j]!=0) {
      if (strcmp(atts[j],"point")==0) { 
	parse(atts[++j],mesh->t_verts);
      } 
      j++;
    }
    // As we in this program uses the notation of OpenGL internally - we need to invert the y coordinate
    for(j=0;j<mesh->t_verts.size();j++) 
      mesh->t_verts[j][1]=1-mesh->t_verts[j][1];
  }

  void X3DBMesh::parse_coordinate(const char **atts) 
  {
    int j=0;
    while (atts[j]!=0) {
      if (strcmp(atts[j],"point")==0) { 
	parse(atts[++j],mesh->verts);
      } 
      j++;
    }
    // All coordinates need to be transformed
    for(j=0;j<mesh->verts.size();j++) {
      mesh->verts[j] = mat.mul_3D_point(mesh->verts[j]);
      mesh->verts[j] = mesh->verts[j];
    }
  }

  void X3DBMesh::parse_color(const char **atts) 
  {
    int j=0;
    while (atts[j]!=0) {
      if (strcmp(atts[j],"color")==0) { 
	parse(atts[++j],mesh->c_verts);
      } 
      j++;
    }
  }
  
  void X3DBMesh::parse_normal(const char **atts) 
  {
    int j=0;
    while (atts[j]!=0) {
      if (strcmp(atts[j],"vector")==0) { 
	parse(atts[++j],mesh->normals);
      } 
      j++;
    }
  }
  
  void X3DBMesh::parse_image_texture(const char **atts) {
    
    assert(texmap==0);
    assert(mesh !=0);
    texmap = obj.create_texmap();
    mesh->set_tex_index(obj.no_texmaps()-1);
    
    int j=0;
    string filename;
    while (atts[j]!=0) {
      if (strcmp(atts[j],"url")==0) { 
	parse(atts[++j],filename);
      } 
      j++;
    }
    assert(filename!="");
    texmap->load((baseurl+filename).c_str());	
  }
  
  void X3DBMesh::parse_transform(const char **atts) {
    mat_vec.push_back(mat);
    Vec3f translation;
    Quaternion rotation;
    //float x,y,z,a;
    
    int j=0;
    while (atts[j]!=0) {
      if (strcmp(atts[j],"translation")==0)
	{ 
	  parse(atts[++j], translation);	
	}
      else if (strcmp(atts[j],"rotation")==0) 
	{
	  Vec4f rvec;
	  parse(atts[++j],rvec); 
	  rotation.make_rot(rvec[3],Vec3f(rvec[0],rvec[1],rvec[2]));
	} 
      j++;
    }
    mat = mat * translation_Mat4x4f(translation) * rotation.get_mat4x4f();
  }
  
  void X3DBMesh::parse_transform_end() {
    assert(mat_vec.size()>0);
    mat = mat_vec.back();
    mat_vec.pop_back();
  }
  
  void X3DBMesh::parse_material(const char **atts) {
    
    assert(material==0);
    assert(mesh !=0);
    material = obj.create_material();
    mesh->set_mtl_index(obj.no_materials()-1);
    
    int j=0;
    while (atts[j]!=0) {
      if (strcmp(atts[j],"DEF")==0) 
	{
	  parse(atts[++j],material->name);
	} 
      else if (strcmp(atts[j],"diffuseColor")==0)
	{
	  parse(atts[++j],material->diffuse_color);
	} 
      else if (strcmp(atts[j],"ambientIntensity")==0) 
	{
	  parse(atts[++j],material->ambient_intensity);
	}
      else if (strcmp(atts[j],"specularColor")==0)
	{
	  parse(atts[++j],material->specular_color);
	} 
      else if (strcmp(atts[j],"emissiveColor")==0) 
	{
	  parse(atts[++j],material->emissive_color);
	} 
      else if (strcmp(atts[j],"shininess")==0) 
	{
	  parse(atts[++j],material->shininess);
	}
      else if (strcmp(atts[j],"transparency")==0)
	{
	  parse(atts[++j],material->transparency);
	} 
      j++;
    }		
  }
}
