#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#if defined(_MSC_VER)
#include <io.h>
#else
#include <unistd.h>
#endif

#include "Components/Timer.h"
#include "BMesh/x3d_load.h"
#include "BMesh/X3DBMesh.h"
#include <iostream>

using namespace CGLA;
using namespace std;
//using namespace CMP;

namespace BMesh
{

  namespace
  {
    X3DBMesh* x3d_bmesh;
  }
	
  void startElement(void *userData, const char *name, const char **atts) 
  {
    if (strcmp(name,"IndexedFaceSet")==0)
      {
	x3d_bmesh->parse_indexed_face_set(atts);
      } 
    else if (strcmp(name,"Shape")==0) 
      {
	x3d_bmesh->parse_shape();
      }
    else if (strcmp(name,"TextureCoordinate")==0) 
      {  
	x3d_bmesh->parse_texture_coordinate(atts);
      } 
    else if (strcmp(name,"Coordinate")==0) 
      {  
	x3d_bmesh->parse_coordinate(atts);
      } 
    else if (strcmp(name,"Color")==0) 
      {  
	x3d_bmesh->parse_color(atts);
      } 
    else if (strcmp(name,"Normal")==0) 
      {  
	x3d_bmesh->parse_normal(atts);
      } 
    else if (strcmp(name,"ImageTexture")==0) 
      {
	x3d_bmesh->parse_image_texture(atts);
      } 
    else if (strcmp(name,"Transform")==0) 
      {
	x3d_bmesh->parse_transform(atts);
      }
    else if (strcmp(name,"Material")==0) 
      {
	x3d_bmesh->parse_material(atts);
      }

  }

  void endElement(void *userData, const char *name) 
  {
    if (strcmp(name,"Shape")==0) 
      {
	x3d_bmesh->parse_shape_end();			
      } 
    else if (strcmp(name,"ImageTexture")==0) 
      {
	x3d_bmesh->parse_image_texture_end();
      } 
    else if (strcmp(name,"Material")==0) 
      {
	x3d_bmesh->parse_material_end();
      } 
    else if (strcmp(name,"Transform")==0) 
      {
	x3d_bmesh->parse_transform_end();
      }
  }

  bool x3d_load(const std::string& filename, Object& obj) 
  {

    CMP::Timer tim;
    tim.start();

    std::string baseurl;
#define FIND_LAST_OF(F,C) (int)(F.find_last_of(C) == string::npos ? -1 : F.find_last_of(C))	
    int idx = max(FIND_LAST_OF(filename, "\\"), FIND_LAST_OF(filename, "/"));
#undef FIND_LAST_OF

    if(idx != -1)
      baseurl = std::string(filename.substr(0, idx+1));


    X3DBMesh _x3d_bmesh(obj, baseurl);
    x3d_bmesh = & _x3d_bmesh;


    XML_Parser parser = XML_ParserCreate(NULL);
    int done=0;
    XML_SetElementHandler(parser, startElement, endElement);

    int in;
    if ((in=open(filename.data(),O_RDONLY)) == -1) {
      cout << "Error. "<<  filename << " not found" << endl;
      assert(0);
      return false;
    }

    struct stat stat_buf;
    fstat(in, &stat_buf);

    const int BUF_SIZE = s_min(5000000, static_cast<int>(stat_buf.st_size));
    char* buf2 = new char[BUF_SIZE];
    size_t len;
    do {
      len = read(in, buf2, BUF_SIZE);
      if (len!=BUF_SIZE)
	done=1;
      if (!XML_Parse(parser, buf2, len, done)) {
	cerr << "%s at line %d\n" 
	     << XML_ErrorString(XML_GetErrorCode(parser))
	     << XML_GetCurrentLineNumber(parser);
	assert(0);
	return false;
      }
    } while (!done);
    close(in);
    XML_ParserFree(parser);
    delete buf2;

    cout << " Loading took " << tim.get_secs() << endl;
    return true;
  }
}
