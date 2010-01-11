#include <iostream>
#include <GL/glut.h>

#include "Common/CommonDefs.h"
#include "Components/Timer.h"

#include "World.h"
#include "RenderEngine.h"
#include "Canvas.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plane.h"
#include "Surface.h"
#include "LightSource.h"
#include "PointLightSource.h"
#include "AreaLightSource.h"

using namespace CMN;
using namespace CMP;
using namespace std;
using namespace CGLA;

namespace {
	Timer timer;
	Canvas* canvas;
	RenderEngine * engine;
	int sizex = 512, sizey = 512;
	unsigned int tex_no;
}


// ----------------------------------------------------------------------
// Write to disk and exit
//
void arrividerci()
{
	canvas->write("out.ppm");
	exit(0);
}


// ----------------------------------------------------------------------
// GLUT functions (for interactive display while ray tracing)

// Check for key press (esc or 'q' quits)
void key(unsigned char k, int x, int y)
{
	switch(k)
		{
		case 'a':
			{
				int w = glutGet(GLUT_WINDOW_WIDTH);
				int h = glutGet(GLUT_WINDOW_HEIGHT);
				if(w*sizey < h*sizex)
					{
						glutReshapeWindow(w,static_cast<int>(sizey*(float(w)/sizex)));
						glutPostRedisplay();
					}
				else if(w*sizey > h*sizex)
					{
						glutReshapeWindow(static_cast<int>(sizex*(float(h)/sizey)),h);
						glutPostRedisplay();
					}
			}
			break;
		case 'q':
		case 27: 
			arrividerci();
		}
}

// Draw ray traced image as textured square.
void display()
{
	const Vec3f p[4] = {Vec3f(0,0,0),	Vec3f(1,0,0),	Vec3f(0,1,0),	Vec3f( 1,1,0)};
	const Vec2f t[4] = {Vec2f(0,0),	Vec2f(1,0),Vec2f(0,1),	Vec2f(1,1)};

	glBegin(GL_TRIANGLES);
	glTexCoord2fv(t[0].get());
	glVertex3fv(p[0].get());
	glTexCoord2fv(t[1].get());
	glVertex3fv(p[1].get());
	glTexCoord2fv(t[2].get());
	glVertex3fv(p[2].get());
	glTexCoord2fv(t[2].get());
	glVertex3fv(p[2].get());
	glTexCoord2fv(t[1].get());
	glVertex3fv(p[1].get());
	glTexCoord2fv(t[3].get());
	glVertex3fv(p[3].get());
	glEnd();
	glFlush();
}


// Idle function:
// Trace some rays, and make sure window is updated.
void idle()
{
	static bool done = false;
	// Draw some pixels
	if(!done)
		{
			if(engine->render_some(1000))
				{
					done = true;
					cout << " time " << timer.get_secs() << endl;
				}
			canvas->update_texture();
			// schedule window for redrawing.
			glutPostRedisplay();
		}
}

void reshape(int w, int h)
{
	glViewport(0,0,w,h);
}

// main function - parse arguments and begin rendering.
int main(int argc, char* argv[])
{
	cout << "This is tint. " << endl;
	cout << " press 'a' to constrain to aspect ratio " << endl;
	cout << " press 'q' or esc to exit " << endl;


	// The image is rendered as a texture. Therefore, the dimensions must 
	// be power of two!
  int sizex = 512, sizey = 512;

  // ----------------------------------------------------------------------
  // Set up viewing parameters and create a camera.
  //
  Vec3f camera_position(2,1.5,2);
  Vec3f looking_at(0,0.5,0);
  Vec3f up(0,1,0);
  float focal_dist = 1;
	Camera camera(camera_position,looking_at,up,focal_dist);
    
	// ----------------------------------------------------------------------
	// Create a world 
	//
	World*  w = new World;
  
	w->set_ambient(Vec3f(1,1,1));
	w->set_background(Vec3f(.1,.3,0.6));

	Surface* s1  = new Surface(w);
	s1->color = Vec3f(.1,0.7,.0);
	s1->k_ambient = 0.1;
	s1->k_diffuse = 0.9;

	Surface* s2  = new Surface(w);
	s2->color = Vec3f(1,1,1);
	s2->k_highlight = 0.3;
	s2->phong_exponent = 42;
	s2->k_reflected = 0.1;
	s2->k_transmitted = 0.9;
	s2->refraction_index = 1.5;

	Surface* s3  = new Surface(w);
	s3->color = Vec3f(.4,0.3,.2);
	s3->k_ambient = 0.3;
	s3->k_diffuse = 0.7;

 	Object3D* inf_plane = new Plane(Vec3f(0,0,0), Vec3f(0,1,0), s1);
 	w->add_object(inf_plane);

 	Object3D* sphere = new Sphere(Vec3f(0,0.5,0), s2, 0.3);
 	w->add_object(sphere);

	Object3D* tri = new Triangle(Vec3f(.2,.1,.9), Vec3f(-.2,.1,.9), 
															 Vec3f(-.2,.1,-.1), s3);
	w->add_object(tri);

  //LightSource* ls = new PointLightSource(w, Vec3f(0,1,0), Vec3f(1,1,1));
  Vec3f corners[4];
  corners[3] = Vec3f( 0.1, 1.0,  0.1);
  corners[2] = Vec3f(-0.1, 1.0,  0.1);
  corners[1] = Vec3f( 0.1, 1.0, -0.1);
  corners[0] = Vec3f(-0.1, 1.0, -0.1);
  LightSource* ls = new AreaLightSource(w, corners, 12, Vec3f(1,1,1));
  
  w->add_light(ls);

  printf("Building photon map...");
  timer.start();
  ls->emit_photons();
  printf("Done!\n");
  printf("Photon map took %f seconds\n", timer.get_secs());
  printf("Global photon map contains %d elements\n", w->get_global_photon_map()->getPhotonCount());
  printf("Caustic photon map contains %d elements\n", w->get_caustic_photon_map()->getPhotonCount());

	
	// ---------------------------------------------------------------------- 
	// Set up GL/glut for interactive viewing.
	// 

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);
	glutInitWindowSize(sizex,sizey);
	glutCreateWindow(argv[0]);
	glutShowWindow();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);

	glOrtho(0,1,0,1,-1,1);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &tex_no);
	glBindTexture(GL_TEXTURE_2D, tex_no);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
									GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
									GL_LINEAR/*_MIPMAP_LINEAR*/);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//	glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);

	// ----------------------------------------------------------------------
	// Create canvas and rendering engine
	//
	canvas = new Canvas(sizex,sizey, tex_no);
	engine = new RenderEngine(w, canvas, &camera);

	// ----------------------------------------------------------------------
	// Start timer and go ...
	//
	cout << "rendering ... " << endl;
	timer.start();
	glutMainLoop();
	arrividerci();
}
