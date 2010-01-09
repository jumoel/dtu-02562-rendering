#ifndef PROGREF_H
#define PROGREF_H
#include <math.h>
#include <vector>
#include <algorithm>

#include "CGLA/Vec3f.h"
#include "Hemicube.h"
#include "DataFormat.h"

using namespace CGLA;
using namespace std;

extern int hemicube_size;
extern Hemicube* hemicube;
extern vector<MyPolygon*> newpolygons;
extern vector<MyVertex*> newvertices;
extern int option;

void renderHemicube()
{
  unsigned int r, g, b;

  for(unsigned int i = 0; i < newpolygons.size(); i++)
  {
    if (4==newpolygons[i]->vertices)
      glBegin(GL_QUADS);
    else if (3==newpolygons[i]->vertices)
      glBegin(GL_TRIANGLES);
    else
      assert(false); // illegal number of vertices
		
    b = (i + 1) % 256;          // (i + 1) to avoid background colour mixup
    g = ((i + 1) - b)/256 % 256;
    r = (((i + 1) - b)/256 - g)/256;

    if(r > 255)
    {
      cerr << " FATAL ERROR : Patch index out of bounds !";
      exit(0);
    }

    glColor3ub(static_cast<unsigned char>(r),
               static_cast<unsigned char>(g),
               static_cast<unsigned char>(b));
		
    for (int j = 0;j < newpolygons[i]->vertices; j++)
    {
      Vec3f position = newvertices[newpolygons[i]->vertex[j]]->position;
      glVertex3f(position[0], position[1], position[2]);
    }
    glEnd();
  }
}



bool polygon_cmp(MyPolygon* mp1, MyPolygon* mp2)
{ 
  return (mp1->unshot_rad.length() < mp2->unshot_rad.length());
}

MyPolygon* maxenergy_patch(const std::vector<MyPolygon*>& pvec)
{
  return *std::max_element(pvec.begin(), pvec.end(), polygon_cmp);
}


MyPolygon* calcFF(std::vector<MyPolygon*>& pvec, const std::vector<MyVertex*>& vvec)
{
  for(unsigned int i = 0; i < pvec.size(); i++)
  	pvec[i]->formF = 0; 
  
  MyPolygon* maxP = maxenergy_patch(pvec);
  if(maxP == 0)
  	return 0;

  Vec3f up(vvec[maxP->vertex[0]]->position - maxP->center);
  up.normalize();

  hemicube = new Hemicube(hemicube_size);
  hemicube->renderScene(maxP->center, 
			up,
                        maxP->normal,
                        renderHemicube);
  hemicube->readIndexBuffer();

  unsigned int index;
  for(int x = 0; x < hemicube->rendersize; x++)
  	for(int y = 0; y < hemicube->rendersize; y++)
    {
      index = hemicube->getIndex(x,y);
      if(index-- == 0)
        continue;

      float deltaformfactor = hemicube->getDeltaFormFactor(x,y);
      pvec[index]->formF += deltaformfactor;
    }
    
  return maxP;
}


MyPolygon* calcAnalyticalFF(std::vector<MyPolygon*>& pvec);

MyPolygon* calcAppFF(std::vector<MyPolygon*>& pvec)
{
  Vec3f r;
  double rSq = 0; //, sum;

  for(unsigned int i = 0; i < pvec.size(); i++)
    pvec[i]->formF = 0;

  MyPolygon* maxP = maxenergy_patch(pvec);
  if(maxP == 0)
  	return 0;

  for(unsigned int i = 0; i < pvec.size(); i++)
    if(maxP != pvec[i] && pvec[i]->area > 0)
    {
      r = pvec[i]->center - maxP->center;
      rSq = dot(r,r);
      r.normalize();

      pvec[i]->formF = pvec[i]->area *
                       dot(maxP->normal, r) *
                       dot(pvec[i]->normal, -r)/(M_PI * rSq);
      if(pvec[i]->formF < 0)
        pvec[i]->formF = 0;
    }

  return maxP;
}


bool distributeEnergy(std::vector<MyPolygon*>& pvec, MyPolygon* maxP)
{
  if(maxP == 0)
  	return false;

  for(unsigned int i = 0; i < pvec.size(); i++)
    if(maxP != pvec[i] && pvec[i]->area > 0)
    {
      // cerr << pvec[i]->diffuse;
      Vec3f deltaRad = pvec[i]->diffuse
	               * maxP->unshot_rad
        	       * pvec[i]->formF
          	       * (maxP->area / pvec[i]->area);
    
      pvec[i]->unshot_rad += deltaRad;
      pvec[i]->rad += deltaRad;
    }

    maxP->unshot_rad = Vec3f(0);
    return true;
}



void colorReconstruction(std::vector<MyPolygon*>& pvec, std::vector<MyVertex*>& vvec)
{
  for(unsigned int i = 0; i < vvec.size(); i++)
  {
    vvec[i]->color = Vec3f(0);
    vvec[i]->colorcount = 0;
  }

  for(unsigned int i = 0; i < pvec.size(); i++)
  {
    switch(option)
    {
      case 3: case 4:
        pvec[i]->color = pvec[i]->rad*20;
	break;
      case 5: case 6:
	pvec[i]->color = pvec[i]->rad*15;
	break;
    }
    for(int j = 0; j < pvec[i]->vertices; j++)
    {
      vvec[pvec[i]->vertex[j]]->color += pvec[i]->color;
      vvec[pvec[i]->vertex[j]]->colorcount++;
    }
  }

  for(unsigned int i = 0; i < vvec.size(); i++)
    vvec[i]->color /= static_cast<double>(vvec[i]->colorcount);  
}


#endif
