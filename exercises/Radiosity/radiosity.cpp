// disable warning C4786: symbol greater than 255 character - okay to ignore
#pragma warning(disable: 4786)

#include <GL/glut.h>
#include "Graphics/TrackBall.h"
#include "Loader.h"
#include "Hemicube.h"
#include "Mesher.h"

#include "ProgRef.h"

using namespace std;
using namespace CGLA;
using namespace GFX;
using namespace SG;


// Radiosity data structures
// ---
vector<MyPolygon*> polygons;  // Polygons = finite elements used in radiosity
                              // computations
vector<MyVertex*> vertices;   // vertices of polygons above

vector<MyPolygon*> newpolygons;
vector<MyVertex*> newvertices;

Hemicube *hemicube;           // Hemicube pointer.



// Parameters loaded from resource file
// ---
float patch_subdiv_size;      // How much do we subdivide polygons to get patch
                              // sizes
float light_subdiv_size;      // How much do we subdivide light sources
int hemicube_size;            // Side length of hemicube face. 
bool use_hemicube;            // Do we use hemicube?
std::string file_name;        // File name



// Other constants and variables
// ---
const int screen_size = 700;  // Const screen size - MAKE SURE THAT 
                              // screen_size < 1/2 hemicube_size !!!
TrackBall *ball;              // Trackball used for scene navigation
int old_state=GLUT_UP;        // GLUT variable
int option = 0;               // Menu option

void displayMyPolygons() {
  for(unsigned int i=0; i < newpolygons.size(); i++) {
    if (4==newpolygons[i]->vertices)
    {
      if(option == 2)
	glBegin(GL_LINE_LOOP);
      else
	glBegin(GL_QUADS);
    }
    else if (3==newpolygons[i]->vertices)
    {
      if(option == 2)
	glBegin(GL_LINE_LOOP);
      else
	glBegin(GL_TRIANGLES);
    }
    else 
      assert(false); // illegal number of vertices
		
		
    glColor3f(newpolygons[i]->color[0],
	      newpolygons[i]->color[1],
	      newpolygons[i]->color[2]);
		
    for (int j=0;j<newpolygons[i]->vertices;j++)
    {
      Vec3f position = newvertices[newpolygons[i]->vertex[j]]->position;
      glVertex3f(position[0], position[1], position[2]);
    }
    glEnd();
  }
}

void displayMyVertices() {
  for(unsigned int i=0; i < newpolygons.size(); i++) {
    if(4 == newpolygons[i]->vertices)
      glBegin(GL_QUADS);
    else if(3 == newpolygons[i]->vertices)
      glBegin(GL_TRIANGLES);
    else 
      assert(false); // illegal number of vertices
			      		
    for (int j=0; j < newpolygons[i]->vertices; j++)
    {
      glColor3f(newvertices[newpolygons[i]->vertex[j]]->color[0],
		newvertices[newpolygons[i]->vertex[j]]->color[1],
		newvertices[newpolygons[i]->vertex[j]]->color[2]);

      Vec3f position = newvertices[newpolygons[i]->vertex[j]]->position;
      glVertex3f(position[0], position[1], position[2]);
    }
    glEnd();
  }
}


// GLUT callback functions
// --------------------------------------------------

void display() {
  glViewport(0,0,screen_size,screen_size);	
  ball->do_spin();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0,0.0,0.0);
  glLoadIdentity();
  ball->set_gl_modelview();
  if(option == 4 || option == 6)
    displayMyVertices();
  else
    displayMyPolygons();
  glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
  if (old_state==GLUT_UP && state==GLUT_DOWN) {
    if (button==GLUT_LEFT_BUTTON) 
      ball->grab_ball(ROTATE_ACTION,Vec2i(x,y));
    else if (button==GLUT_MIDDLE_BUTTON) 
      ball->grab_ball(ZOOM_ACTION,Vec2i(x,y));
    else if (button==GLUT_RIGHT_BUTTON) 
      ball->grab_ball(PAN_ACTION,Vec2i(x,y));
  }
  if (old_state==GLUT_DOWN && state==GLUT_UP)
    ball->release_ball();
  old_state=state;
}

void motion(int x, int y) {
  if (old_state==GLUT_DOWN)
    ball->roll_ball(Vec2i(x,y));
}

void keyboard(unsigned char key, int x, int y) {
  switch(key) {
    case '\033': exit(0); break;
  }
}

void animate()
{
  glutPostRedisplay();
}

void visible(int vis)
{
  if (vis == GLUT_VISIBLE)
    glutIdleFunc(animate);
  else
    glutIdleFunc(NULL);
}

int main(int argc, char** argv)
{ 
  CMP::ResourceLoader res("Resource.xml");
  cout << "hemicube_size: " 
       << (hemicube_size  = res.getInt("hemicube_size")) << endl 
       << "form_factor_method: " 
       << (use_hemicube=("hemicube"==res.getString("form_factor_method")))
       << endl
       << "patch_subdivision_size: " 
       << (patch_subdiv_size=res.getFloat("patch_subdivision_size")) << endl
       << "light_subdivision_size: " 
       << (light_subdiv_size=res.getFloat("light_subdivision_size")) << endl
       << "file_name: " 
       << (file_name=res.getString("file_name")) << endl;
  
  if(2*hemicube_size > screen_size) 
    cout << "Warning: hemicube * 2 > screen_size " << endl;
  
  // End of resource loading


  // Initialize GLUT 
  // --------------------------------------------------
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitWindowSize(screen_size, screen_size);
  glutInit(&argc, argv);
  glutCreateWindow("Radiosity");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutVisibilityFunc(visible);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
	
  // Initialize OpenGL
  // --------------------------------------------------
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0,1.0,-1.0,1.0,1.5,2500.0);
  glMatrixMode(GL_MODELVIEW);
  glClearColor(0.0,0.0,0.0,0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glDisable(GL_LIGHTING);
  glDisable(GL_DITHER);
  ball = new TrackBall(Vec3f(0,0,0), screen_size, screen_size, 750, 750);
	

  // Load scene
  load_model(file_name, vertices, polygons); 
  
  // Meshing with things ...
  Mesher::mesh(vertices, polygons, newvertices, newpolygons,
	       patch_subdiv_size, light_subdiv_size);

  // Query
  int printFreq = 0;
  float limit = 1;
  cout << endl << "  1. Show initial colours                                (Part 1)" 
       << endl << "  2. Show polygon mesh                                   (Part 2)"
       << endl << "  3. Use approximated analytical form factor calculation (Part 3)"
       << endl << "  4. Case 3 using nodal-averages as vertex radiosities   (Part 4)"
       << endl << "  5. Use hemicube to calculate form factors              (Part 5a)"
       << endl << "  6. Case 4 using nodal-averages as vertex radiosities   (Part 5b)"
       << endl << "  7. Exit";
  while(1)
  {
    cout << endl << "Choose an option: ";
    cin >> option;
    if(option > 0 && option < 7)
      break;
    if(option == 7)
      exit(0); 
    cout << "Please, try again!";
  }

  if(option == 1 || option == 2)
  {
    // code that set some initial colours for us to display
    for(unsigned int i = 0; i < newpolygons.size(); i++)
      newpolygons[i]->color = newpolygons[i]->diffuse;

    // Run
    glutMainLoop();
  }

  cout << endl << "Set limit to sum of unshot radiosity which converges to zero: ";
  cin >> limit;

  cout << endl << "Enter frequency of unshot radiosity printouts while calculating: ";
  cin >> printFreq;

  // Hemicube
  MyPolygon* maxP = 0;

  float radsum;
  int printsum = 0;
  do
  {
    if(option == 3 || option == 4)
      maxP = calcAppFF(newpolygons);
    if(option == 5 || option == 6)
      maxP = calcFF(newpolygons, newvertices);
    if(maxP == 0)
    {
      cout << "no maximal energy patch found ...";
      continue;
    }
    distributeEnergy(newpolygons, maxP);

    radsum = 0;
    for(unsigned int i = 0; i < newpolygons.size(); i++)
      radsum += newpolygons[i]->unshot_rad.length();

    if(printFreq >= 0)
    {
      printsum++;
      if(printsum > printFreq)
      {
	printsum = 0;
	cerr << " radsum " << radsum;
      }
    }
  }
  while(radsum > limit);

  colorReconstruction(newpolygons, newvertices);

  // Run
  glutMainLoop();

  return 0;
}
