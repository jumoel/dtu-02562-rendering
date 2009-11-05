#include "BMesh/TriMesh.h"
#include <iostream>

using namespace std;
using namespace CGLA;

namespace BMesh
{

  void TriMesh::build_face_normals() 
  {
    int i;
    int NF = faces.size();
    face_normals.resize(NF);
    for(i=0;i<NF; ++i)
      {
	const Face& f  = faces[i];
	const Vec3f p0 = verts[f[0]];
	const Vec3f a  = verts[f[1]] - p0;
	const Vec3f b  = verts[f[2]] - p0;
	face_normals[i] = cross(a,b);
	float l = sqr_length(face_normals[i]);
	if(l > 0.0f)
	  face_normals[i] /= sqrt(l);
      }
  }

  void TriMesh::build_vertex_normals() 
  {
    int i;
		
    int NV = verts.size();
    int NF = faces.size();

    if(normals.size() != NV)
      {
	normals.resize(NV);
	for(i=0;i<NV; ++i)
	  normals[i] = Vec3f(0);
      }
    for(i=0;i<NF; ++i)
      {
	const Face& f  = faces[i];
	const Vec3f p0 = verts[f[0]];
	const Vec3f a  = verts[f[1]] - p0;
	const Vec3f b  = verts[f[2]] - p0;
	Vec3f face_normal = cross(a,b);
	float l = sqr_length(face_normal);
	if(l > 0.0f)
	  face_normal /= sqrt(l);

	for(int j=0;j<3; ++j)
	  {
	    const Vec3f p0 = verts[f[j]];
	    const Vec3f a = normalize(verts[f[(j+1)%3]] - p0);
	    const Vec3f b = normalize(verts[f[(j+2)%3]] - p0);
	    normals[f[j]] += face_normal * acos(dot(a,b));
	  }
      }
    for(i=0;i<NV; ++i)
      normals[i].normalize();
  }

  void TriMesh::build_normals() 
  {
    build_face_normals();
    build_vertex_normals();
  }


  void TriMesh::check_normals() 
  {
    if(face_normals.size() != faces.size())
      build_face_normals();
    if (normals.size() != verts.size())
      build_vertex_normals();
  }

  void TriMesh::get_bbox(CGLA::Vec3f& p0, CGLA::Vec3f& p7) const
  {
    int i;
    p0 = verts[0];
    p7 = verts[0];
    for(i=1;i<verts.size();i++) 
      {
	p0 = v_min(verts[i], p0);
	p7 = v_max(verts[i], p7);
      }
  }

  void TriMesh::get_bsphere(CGLA::Vec3f& c, float r) const
  {
    Vec3f p0,p7;
    get_bbox(p0, p7);
    Vec3f rad = (p7 - p0)/2.0;
    c = p0 + rad;
    r = rad.length();
  }

}
