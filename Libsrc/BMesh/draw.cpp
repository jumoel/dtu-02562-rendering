#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include "BMesh/draw.h"

using namespace CGLA;
using namespace std;


namespace BMesh
{
  void gl_apply_material(Material& material) 
  {
    material.alpha = 1 - material.transparency;

    float diffuse[4];
    diffuse[0]=material.diffuse_color[0];
    diffuse[1]=material.diffuse_color[1];
    diffuse[2]=material.diffuse_color[2];
    diffuse[3]=material.alpha;

    float ambient[4];
    ambient[0]=material.ambient_intensity*diffuse[0];
    ambient[1]=material.ambient_intensity*diffuse[1];
    ambient[2]=material.ambient_intensity*diffuse[2];
    ambient[3]=material.alpha;

    float specular[4];
    specular[0]=material.specular_color[0];
    specular[1]=material.specular_color[1];
    specular[2]=material.specular_color[2];
    specular[3]=material.alpha;

    float emission[4];
    emission[0]=material.emissive_color[0];
    emission[1]=material.emissive_color[1];
    emission[2]=material.emissive_color[2];
    emission[3]=material.alpha;

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.shininess);

    glColor3fv(material.diffuse_color.get());
  }


  void gl_init_textures(Texmap& texmap) 
  {
    GLint internalFormat=0;
    GLenum format=0;
    GLuint texName;


    glGenTextures(1, &texName);
    switch (texmap.bpp) 
      {
      case 8:
	internalFormat =  GL_LUMINANCE;
	format = GL_LUMINANCE;
	break;
      case 24:
	internalFormat =  GL_RGB;
	format = GL_RGB;
	break;
      case 32:
	internalFormat =  GL_RGBA;
	format = GL_RGBA;
	break;
      default:
	assert(0);
      }
		

    glBindTexture(GL_TEXTURE_2D, texName);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, texmap.size_x, 
		 texmap.size_y, 0, format, GL_UNSIGNED_BYTE, 
		 texmap.image); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    texmap.id = texName;
  }

  void gl_init_textures(Object& obj)
  {
    for(int i=0;i<obj.no_texmaps();++i)
      gl_init_textures(*obj.get_texmap(i));
  }

  void gl_draw_object(Object& object, 
		      bool smooth,
		      bool use_texture,
		      bool use_material) 
  {
    glPushAttrib(GL_ENABLE_BIT|GL_LIGHTING_BIT);
    for(int i=0;i<object.no_meshes();i++) 
      {
	int mtl_id=-1;
	int tex_id=-1;
	if(use_material && !object.get_mesh(i)->has_color_vertices())
	  {
	    mtl_id = object.get_mesh(i)->get_mtl_index();
	    if(mtl_id!=-1)
	      gl_apply_material(*object.get_material(mtl_id));
	  }
	if(use_texture)
	  {
	    int tex_id = object.get_mesh(i)->get_tex_index();
	    if (tex_id!=-1 && tex_id<object.no_texmaps()) 
	      {
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, object.get_texmap(tex_id)->id);
		if (object.get_texmap(tex_id)->bpp==32) 
		  {
		    glEnable(GL_ALPHA_TEST);
		    glAlphaFunc(GL_GREATER, 0.4);
		  }
	      }
	  }
	if(smooth)
	  gl_draw_mesh_smooth(*object.get_mesh(i), use_texture, use_material);
	else
	  gl_draw_mesh(*object.get_mesh(i), use_texture, use_material);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
      }
    glPopAttrib();
  }
	
  void gl_draw_mesh(TriMesh& mesh, bool use_texture, bool use_material) 
  {
    int k_max = 99;
    mesh.check_normals();


    if (mesh.has_color_vertices() && use_material) 
      {
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
      }
    for(int k=0;k<mesh.no_faces(); k += k_max)
      {
	glBegin(GL_TRIANGLES);
	for(int i=k;i<s_min(mesh.no_faces(),k+k_max);i++) 
	  {
	    glNormal3fv(mesh.get_face_normal(i).get());
	    for(int j=0;j<3;j++) 
	      {
		if (use_texture && mesh.has_texture()) 
		  glTexCoord2fv(mesh.get_tvertex(mesh.get_tface(i)[j]).get());
		if (mesh.has_color_vertices()) 
		  glColor3fv(mesh.get_cvertex(mesh.get_face(i)[j]).get());

		glVertex3fv(mesh.get_face_vertex(i,j).get());
	      }
	  }
	glEnd();
      }
    glDisable(GL_COLOR_MATERIAL);
  }

  void gl_draw_mesh_smooth(TriMesh& mesh, bool use_texture, bool use_material) 
  {
    int k_max = 99;
    mesh.check_normals();

    if (mesh.has_color_vertices() && use_material) 
      {
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
      }
    for(int k=0;k<mesh.no_faces(); k += k_max)
      {
	glBegin(GL_TRIANGLES);
	for(int i=k;i<s_min(mesh.no_faces(),k+k_max);i++) 
	  {
	    for(int j=0;j<3;j++) 
	      {
		if (use_texture && mesh.has_texture()) 
		  glTexCoord2fv(mesh.get_tvertex(mesh.get_tface(i)[j]).get());
		if (mesh.has_color_vertices()) 
		  glColor3fv(mesh.get_cvertex(mesh.get_face(i)[j]).get());
		glNormal3fv(mesh.get_normal(mesh.get_face(i)[j]).get());
		glVertex3fv(mesh.get_face_vertex(i,j).get());
	      }
	  }
	glEnd();
      }
    glDisable(GL_COLOR_MATERIAL);
  }
	



}	
