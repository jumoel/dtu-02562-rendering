
#include <fstream>
#include "x3d_save.h"
#include "CGLA/Vec3f.h"
#include "TriMesh.h"
#include "expat.h"

using namespace CGLA;
using namespace std;

namespace
{
  const string X3D_BEGIN = 
    "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
    "<!DOCTYPE X3D PUBLIC \"http://www.web3D.org/TaskGroups/x3d/translation/x3d-compact.dtd\"\n"
    "\"/www.web3d.org/TaskGroups/x3d/translation/x3d-compact.dtd\">\n"
    "<X3D>\n"
    "  <head>\n"
    "  </head>\n"
    "  <Scene>\n"
    "		<Viewpoint description=\"Pyramid\" orientation=\"0 1 0 .2\" position=\"4 0 25\"/>\n"
    "    <NavigationInfo type=\"EXAMINE ANY\"/>\n";
	
  const string X3D_END = 
    "  </Scene>\n"
    "</X3D>\n";

}

namespace BMesh
{

  bool x3d_save(const std::string& filename, Object& bobj,
				unsigned char flags)
  {
    ofstream os(filename.data());

    if(os.bad()) return false;

    os << X3D_BEGIN << endl;

    for(int j=0;j<bobj.no_meshes();++j)
      {
	int i;
	const TriMesh& bmesh = *bobj.get_mesh(j);
				
	os << "<Shape>\n"
	   << "<Appearance>\n"
	   << "<Material diffuseColor=\"0.8 0.8 0.2\" specularColor=\"0 0 0.5\"/>\n"
	   << "</Appearance>\n";
	
	os << "<IndexedFaceSet coordIndex=\"" << endl;
	for(i=0;i<bmesh.no_faces(); ++i)
	  {
	    const Face& p = bmesh.get_face(i);
	    os << p[0] << " " 
	       << p[1] << " " 
	       << p[2] << " ";
	    os << " -1";
	    os << "\n";
	  }
	os << "\">" << endl;

	// Save coordinates
	os <<  "<Coordinate point=\"" << endl;
	for(i=0;i<bmesh.no_vertices(); ++i)
	  {
	    Vec3f v = bmesh.get_vertex(i);
	    os << v[0] << " " 
	       << v[1] << " " 
	       << v[2] << " \n";
	  }
	os << "\"/>" << endl;

	// Save colors
	if((flags&SAVE_VERTEX_COLORS)&& bmesh.has_color_vertices())
	  {
	    os <<  "<Color color=\"" << endl;
	    for(i=0;i<bmesh.no_vertices(); ++i)
	      {
		Vec3f c = bmesh.get_cvertex(i);
		os << c[0] << " " 
		   << c[1] << " " 
		   << c[2] << " \n";
	      }
	    os << "\"/>" << endl;
	  }

  	// Save normals
	if(flags&SAVE_VERTEX_NORMALS)
	  {
	    os <<  "<Normal vector=\"" << endl;
	    for(i=0;i<bmesh.no_vertices(); ++i)
	      {
		Vec3f n = bmesh.get_normal(i);
		os << n[0] << " " 
		   << n[1] << " " 
		   << n[2] << " \n";
	      }
	    os << "\"/>" << endl;
	  }


	os << "</IndexedFaceSet>\n"
	   << "</Shape>\n";
      }
    os << X3D_END << endl;
  }

}
