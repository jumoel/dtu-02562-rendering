#include "X3DSceneGraph/SceneGraph.h"
#include "X3DSceneGraph/TGA.h"
#include "X3DSceneGraph/TextureLoader.h"

#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library

using namespace std;
using namespace CGLA;
using namespace Geometry;

namespace X3DSceneGraph
{

	bool materialenable=true;

	BoundingVolume::BoundingVolume() {
		radius = 0;
	}

	Group::Group() {
		parent=0;
	}

	void Group::addChild(Drawable *drawable) {
		children.push_back(drawable);
	}

	void Group::draw() {
		vector<Drawable*>::iterator p=children.begin();
		while(p!=children.end()) {
			(*p)->draw();
			*p++;
		}
	}

	void Group::updateBV() {
		vector<Drawable*>::iterator p=children.begin();
		while(p!=children.end()) {
			(*p)->updateBV();
			if ((*p)->bv.radius>bv.radius)
				bv.radius=(*p)->bv.radius;
			bv.aabb = getBoundingAABB(bv.aabb, (*p)->bv.aabb);		
			*p++;
		}
	}

	void Transform::draw() {
		if (SG_DEBUG)
			cout << "Transform" << endl;
		glPushMatrix();
		// Translate
		glTranslatef(translation[0],translation[1],translation[2]);
		// Rotate
		float a;
		Vec3f vec;
		rotation.get_rot(a, vec);
		glRotatef(a/M_PI*180, vec[0],vec[1],vec[2]);

		// Scale
		//	glScalef(scale[0],scale[1],scale[2]);

		Group::draw();
		glPopMatrix();
	}

	void Transform::updateBV() {
		// Remember translation!!!!!!!!!!!
		vector<Drawable*>::iterator p=children.begin();
		while(p!=children.end()) {
			(*p)->updateBV();
			if ((*p)->bv.radius>bv.radius)
				bv.radius=(*p)->bv.radius;
			Mat4x4f mat =	translation_Mat4x4f(translation)*rotation.get_mat4x4f();
			bv.aabb = getBoundingAABB(bv.aabb, getBoundingAABB((*p)->bv.aabb,mat));
			*p++;
		}
	}


	Material::Material() {
		// Default properties
		diffuseColor[0] = 0.8f;
		diffuseColor[1] = 0.8f;
		diffuseColor[2] = 0.8f;
		ambientIntensity = 0.2f;
		specularColor[0] = 0;
		specularColor[1] = 0;
		specularColor[2] = 0;
		emissiveColor[0] = 0;
		emissiveColor[1] = 0;
		emissiveColor[2] = 0;
		shininess = .2f;
		transparency = 0;
	}

	void Material::apply() {
		GLenum face = GL_FRONT;// GL_FRONT_AND_BACK;
		alpha = 1 - transparency;
		diffuse[0]=diffuseColor[0];
		diffuse[1]=diffuseColor[1];
		diffuse[2]=diffuseColor[2];
		diffuse[3]=alpha;

		ambient[0]=ambientIntensity*diffuse[0];
		ambient[1]=ambientIntensity*diffuse[1];
		ambient[2]=ambientIntensity*diffuse[2];
		ambient[3]=alpha;

		specular[0]=specularColor[0];
		specular[1]=specularColor[1];
		specular[2]=specularColor[2];
		specular[3]=alpha;
		emission[0]=emissiveColor[0];
		emission[1]=emissiveColor[1];
		emission[2]=emissiveColor[2];
		emission[3]=alpha;

		glMaterialfv(face, GL_DIFFUSE, diffuse);
		glMaterialfv(face, GL_AMBIENT, ambient);
		glMaterialfv(face, GL_SPECULAR, specular);
		glMaterialfv(face, GL_SHININESS, &shininess);
		glMaterialfv(face, GL_EMISSION, emission);
		glColor3f(diffuse[0],diffuse[1],diffuse[2]);
	}
	void Material::unApply() {
	}


	void ImageTexture::load() {
		TextureLoader tl;

		glGenTextures(1, &texName);

		glBindTexture(GL_TEXTURE_2D, texName);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		tl.load(url,true);


		/*
			string s;
			s = url.substr(url.size()-4,4);
			//	cout << s << endl;
	
			// tga
			TargaImage p; 

			#ifdef JPEG
			// JPEG
			Colosseum::BitmapImage bimage;
			Colosseum::ImageType type;
			#endif
			if (s==".tga") {
			p.read(url.c_str(),TGA32);
			canvas_width = p.m_iWidth;
			canvas_height = p.m_iHeight;
			} 
			#ifdef JPEG	
			else {
			// Jpeg thing
			type = Colosseum::ReadImage (url.c_str(), bimage, 0, 0) ;

			canvas_width = bimage.getWidth();
			canvas_height = bimage.getHeight();
			}	
			#endif

			int i,j;
			for (i=2;i<=4096 ;i*=2) 
			if (i>=canvas_height) 
			break;
			int power_height = i;
			for (i=2;i<=4096 ;i*=2) 
			if (i>=canvas_width) 
			break;
			int power_width = i;

			unsigned char *image= new unsigned char[power_height*power_width*4*2];		
			if (image==0) {
			cout << "Something wrong! memory allocation failure" << endl;
			exit(0);
			}
		
			for(i=0;i<canvas_height;i++)
			for(j=0;j<canvas_width;j++) {
			if (s==".tga") {
			int c = p.m_pImage[i*p.m_iWidth+j];
			#if __BYTE_ORDER == __LITTLE_ENDIAN
			image[((canvas_height-i)*power_width+j)*4+1]=(c >> 8) & 0xff;
			image[((canvas_height-i)*power_width+j)*4+0]=(c >> 16) & 0xff;
			image[((canvas_height-i)*power_width+j)*4+3]=(c >> 24) & 0xff;
			image[((canvas_height-i)*power_width+j)*4+2]=c & 0xff;
			#else
			image[((canvas_height-i)*power_width+j)*4+0]=(c >> 8) & 0xff;
			image[((canvas_height-i)*power_width+j)*4+1]=(c >> 16) & 0xff;
			image[((canvas_height-i)*power_width+j)*4+2]=(c >> 24) & 0xff;
			image[((canvas_height-i)*power_width+j)*4+3]=c & 0xff;
			#endif

			} 
			#ifdef JPEG			
			else {
			Colosseum::BitmapImage::Pixel p= bimage[i*canvas_width+j];
			image[((canvas_height-i)*power_width+j)*4+0]=p.red;
			image[((canvas_height-i)*power_width+j)*4+1]=p.green;
			image[((canvas_height-i)*power_width+j)*4+2]=p.ue;
			image[((canvas_height-i)*power_width+j)*4+3]=255;
			}
			#endif
			}

			glGenTextures(1, &texName);

			glBindTexture(GL_TEXTURE_2D, texName);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, power_width, 
			power_height, GL_RGBA, GL_UNSIGNED_BYTE, 
			image);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, power_width, 
			power_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 
			image);


			delete []image;*/
		//	bimage.clearImage();
		factorx = (float)tl.load_size_x/(float)tl.size_x;
		factory = (float)tl.load_size_y/(float)tl.size_y;
	}


	Appearance::Appearance() {
		texture=0;
		material=0;
	}

	void Appearance::apply() {
		if (texture!=0) {
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER,0.5);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture->texName);
		}
		if (material!=0)
			material->apply();
	}

	void Appearance::unApply() {
		if (texture!=0) {
			glDisable(GL_ALPHA_TEST);
			glDisable(GL_TEXTURE_2D);
		}
	}

	Shape::Shape() {
		appearance=0;
		geometry=0;
	}

	void Shape::draw() {
		if (geometry!=0) {
			if (appearance!=0)
				geometry->pAppearance = &appearance;
			geometry->draw();
			if (appearance!=0 && materialenable)
				if (appearance->texture!=0) 
					glDisable(GL_TEXTURE_2D);
		}
	}

	void Shape::updateBV() {
		if (geometry!=0) {
			geometry->updateBV();
			bv.radius = geometry->bv.radius;
			bv.aabb.min = geometry->bv.aabb.min;
			bv.aabb.max = geometry->bv.aabb.max;
		}
	}

	Sphere::Sphere() {
		radius=1;
	}

	void Sphere::draw() {
		//	glutSolidSphere(radius, 15,15);
	}

	void Sphere::init() {
	}

	void Sphere::updateBV() {
		bv.radius = radius;
	}

	Scene::Scene() {
	}

	void Scene::draw() {
		Group::draw();
	}

	void Scene::init() {
		updateBV();
	}


	void Scene::updateBV() {
		Group::updateBV();
	}

	void Scene::enableMaterial(bool value) {
		materialenable = value;
	}

	void Drawable::setUserData(void *_user_data) {
		user_data = _user_data;
	}

	void* Drawable::getUserData() {
		return user_data;
	}
}
