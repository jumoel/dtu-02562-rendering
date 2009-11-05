#ifndef __MESH_H__
#define __MESH_H__

/***********

TODO: This trimesh class can be improved in numerous ways.

- In some cases, we want separate faces for texture, colour and normals.
This opens up the possibility that we can have discontinuties in shading
colour and texture. However, at present there are only separate faces for
texture. To extend this to normals and colour is easy, but if we always 
use separate faces it will be very memory consuming. Sometimes having common
and at other times separate faces is somewhat harder to implement in a safe
efficient way.

*/

#include <vector>
#include <CGLA/Vec3f.h>
#include <CGLA/Vec2f.h>


namespace BMesh
{
  class X3DBMesh;
  class Object;
  bool obj_load(const std::string&, Object&);

  typedef CGLA::Vec3i Face;
  typedef CGLA::Vec3f Vertex;
  typedef CGLA::Vec2f UVVertex;
  typedef CGLA::Vec3f CVertex;
  typedef CGLA::Vec3f Normal;

  class TriMesh 
  {
    friend class X3DBMesh;
    friend bool obj_load(const std::string&, Object&);

    /// The triangles that make up the mesh
    std::vector<Face> faces;

    /// The triangles in texture space.
    std::vector<Face> t_faces;

    /// The vertices (spatial coordinates) of the mesh
    std::vector<Vertex> verts;
		
    /// The texture vertices of the mesh
    std::vector<UVVertex> t_verts;

    /// The colour vertices of the mesh.
    std::vector<CVertex> c_verts;

    /// The normals of the mesh
    std::vector<Normal> normals;
		
    /// The normals of the mesh
    std::vector<Normal> face_normals;

    int mtl_id;
    int tex_id;

    void build_face_normals();
    void build_vertex_normals();

  public:

    TriMesh(): mtl_id(-1), tex_id(-1) {}

    virtual ~TriMesh() {}

    // Size queries ------------------------------

    int no_faces() const {return faces.size();}

    int no_vertices() const {return verts.size();}

    int no_tfaces() const {return t_faces.size();}

    int no_tvertices() const {return t_verts.size();}

    // Add properties

    int add_face(const Face& face) 
    {
      int n = faces.size();
      faces.push_back(face);
      return n;
    }

    int add_tface(const Face& face) 
    {
      int n = t_faces.size();
      t_faces.push_back(face);
      return n;
    }

    int add_vertex(const Vertex& vert) 
    {
      int n = verts.size();
      verts.push_back(vert);
      return n;
    }

    int add_normal(const CGLA::Vec3f& normal) 
    {
      int n = normals.size();
      normals.push_back(normal);
      return n;
    }

    int add_tvertex(const UVVertex& tvert) 
    {
      int n = t_verts.size();
      t_verts.push_back(tvert);
      return n;
    }

    int add_cvertex(const CVertex& cvert) 
    {
      int n = c_verts.size();
      c_verts.push_back(cvert);
      return n;
    }


    // Get property functions -----------------------------

    const Face& get_face(int i) const{
      assert(i<faces.size());
      return faces[i];
    }

    const Face& get_tface(int i) const{
      assert(i<t_faces.size());
      return t_faces[i];
    }

    const Normal& get_normal(int i) const {
      assert(i<normals.size());
      return normals[i];
    }

    const Normal& get_face_normal(int i) const 
    {
      assert(i<face_normals.size());
      return face_normals[i];
    }

    const Vertex& get_vertex(int i) const 
    {
      assert(i<verts.size());
      return verts[i];
    }

    const Vertex& get_face_vertex(int i, int j) const 
    {
      assert(i<faces.size());
      assert(faces[i][j]<verts.size());
      return verts[faces[i][j]];
    }

    const UVVertex& get_tvertex(int i) const {
      assert(i<t_verts.size());
      return t_verts[i];
    }

    const CVertex& get_cvertex(int i) const {
      assert(i<c_verts.size());
      return c_verts[i];
    }

    // Set property functions ------------------------------

    void set_normal(int i, const CGLA::Vec3f& normal) 
    {
      normals[i]=normal;
    }

    void set_vertex(int i, const Vertex& newv)
    {
      assert(i<verts.size());
      verts[i] = newv;
    }

    void set_tvertex(int i, const UVVertex& newv)
    {
      assert(i<t_verts.size());
      t_verts[i] = newv;
    }

    // Qualitative queries ------------------------

    bool has_texture() const
    {
      return tex_id != -1;
    }

    bool has_color_vertices() const
    {
      return c_verts.size() != 0;
    }

    // Overall methods

    /// Will build the normals
    void build_normals(); 
		
    /// Check if the normals are present - if not build them
    void check_normals(); 

    // Material methods
    void set_mtl_index(int i) {mtl_id=i;}
    int get_mtl_index() const {return mtl_id;}

    // Texture methods
    void set_tex_index(int i) {tex_id=i;}
    int get_tex_index() const {return tex_id;}

    void get_bsphere(CGLA::Vec3f& c, float r) const;
		
    void get_bbox(CGLA::Vec3f& p0, CGLA::Vec3f& p7) const;
  };
}
#endif
