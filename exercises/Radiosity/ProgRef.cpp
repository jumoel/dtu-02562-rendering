#include <math.h>
#include <vector>
#include <float.h>

#include "CGLA/Vec3f.h"
#include "Hemicube.h"
#include "Dataformat.h"
#include "ProgRef.h"

using namespace CGLA;
using namespace std;

extern int hemicube_size;
extern Hemicube* hemicube;
extern vector<MyPolygon*> newpolygons;
extern vector<MyVertex*> newvertices;
extern int option;



// Cotangens eliminating infinity problems on the interval [-pi,pi]
double cot(double x)
{
  const double SMALL_F = 1e-6;

  if((x > -M_PI_2 - SMALL_F && x < -M_PI_2 + SMALL_F) ||
     (x > M_PI_2 - SMALL_F && x < M_PI_2 + SMALL_F))
    return 0;

  double tanx = tan(x);
  if(tanx > -SMALL_F && tanx < SMALL_F)
    return DBL_MAX;

  return 1.0/tanx;
}

MyPolygon* calcAnalyticalFF(vector<MyPolygon*>& pvec)
{
  double cosTheta = 0.0,
         rSq      = 0.0,
         hSq      = 0.0,
         RSq      = 0.0,
         pSq      = 0.0,
         x        = 0.0,
         xSq      = 0.0,
         s        = 0.0,
         deltaF   = 0.0;

  Vec3f r;

  for(unsigned int i = 0; i<pvec.size(); i++)
    pvec[i]->formF = 0;

  MyPolygon* maxP = maxenergy_patch(pvec);
  if(maxP == 0)
    return 0;

  // cerr << "Hello" << endl;
  for(unsigned int i = 0; i < pvec.size(); i++)
    if(maxP != pvec[i] && pvec[i]->area > 0)
    {
      cosTheta = -dot(maxP->normal, pvec[i]->normal);
      if(cosTheta < 0 || pvec[i]->center[2]*cot(acos(cosTheta)) < 1)
        continue;
      r = pvec[i]->center - maxP->center;
      rSq = dot(r,r);
      r.normalize();
      // cerr << ' ' << pvec[i]->area;
      RSq = pvec[i]->area/M_PI;
      hSq = pow(dot(r, pvec[i]->normal), 2)/RSq;
      pSq = rSq/RSq - hSq;
      x   = 1 + hSq + pSq;
      xSq = x * x;
      s   = sqrt(xSq - 4*pSq);
      deltaF = 0.5 * ((2 - x)/s + 1) * cosTheta
               + (pow(dot(r,pvec[i]->normal), 2)*cosTheta
               - dot(r,pvec[i]->normal)*dot(r,maxP->normal))
               / (x*(x + s)*RSq);
      if(deltaF > 0)
        pvec[i]->formF += deltaF;
      if(pvec[i]->formF > 1)
        cerr << " FF " << pvec[i]->formF;
    }

  return maxP;
}



