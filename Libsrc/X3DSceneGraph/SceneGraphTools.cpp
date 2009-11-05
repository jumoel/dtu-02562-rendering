#include "X3DSceneGraph/SceneGraphTools.h" 

const int BIG=1000000;

using namespace std;
using namespace CGLA;

namespace X3DSceneGraph {

	void calculateAABB(IndexedFaceSet *faceset, CGLA::Vec3f* min, CGLA::Vec3f * max) {
		max->set(-BIG,-BIG,-BIG);
		min->set(BIG,BIG,BIG);

		vector<int>::iterator i=faceset->coordIndex.begin();
		CGLA::Vec3f vec;
		while(i!=faceset->coordIndex.end()) {
			if (*i>-1) {
				vec = faceset->coord->point[*i];
				// Maximum
				if ((vec)[0]>(*max)[0])
					(*max)[0]=(vec)[0];
				if ((vec)[1]>(*max)[1])
					(*max)[1]=(vec)[1];
				if ((vec)[2]>(*max)[2])
					(*max)[2]=(vec)[2];
				// Minimum
				if ((vec)[0]<(*min)[0])
					(*min)[0]=(vec)[0];
				if ((vec)[1]<(*min)[1])
					(*min)[1]=(vec)[1];
				if ((vec)[2]<(*min)[2])
					(*min)[2]=(vec)[2];
			}
			i++;
		}
		return;
	}
	
	// This function finds all IndexedFaceSet whitin a group and find the min and max
	void calculateAABB(Group *group, Vec3f* min, Vec3f * max) {
		max->set(-BIG,-BIG,-BIG);
		min->set(BIG,BIG,BIG);

		vector<Group*> stack;
		Group* curgroup;
		stack.push_back(group);
		IndexedFaceSet *faceset=0;
		Vec3f submax;
		Vec3f submin;

		while (!stack.empty()) {
			curgroup=stack.back();
			stack.pop_back();
			for(vector<Drawable*>::iterator i=curgroup->children.begin();i!=curgroup->children.end();++i) {
				if (Group* gr=dynamic_cast<Group*>(*i)) 
					stack.push_back(gr);
		
				if (Shape* sh=dynamic_cast<Shape*>(*i))  {
					faceset=dynamic_cast<IndexedFaceSet*>(sh->geometry);
				}
				if (faceset!=0) {
					calculateAABB(faceset,&submin,&submax);
					// Maximum
					if ((submax)[0]>(*max)[0])
						(*max)[0]=(submax)[0];
					if ((submax)[1]>(*max)[1])
						(*max)[1]=(submax)[1];
					if ((submax)[2]>(*max)[2])
						(*max)[2]=(submax)[2];
					// Minimum
					if ((submin)[0]<(*min)[0])
						(*min)[0]=(submin)[0];
					if ((submin)[1]<(*min)[1])
						(*min)[1]=(submin)[1];
					if ((submin)[2]<(*min)[2])
						(*min)[2]=(submin)[2];
					faceset=0;
				}
			}
		}
	}

	// This function could be made either as a recursive or stack type algorithm
	// I choose to make it as a stack oriented algorithm
	Drawable* findObject(string name, Group* group) {
		vector<Group*> stack;
		Group* curgroup;
		Drawable *foundobj=0;
		stack.push_back(group);
		
		// Brede først algorithm
		while (!stack.empty()) {
			curgroup=stack.back();
			stack.pop_back();
			if (curgroup->name==name) {
				foundobj=curgroup;
				break;
			}	else {
				for(vector<Drawable*>::iterator i=curgroup->children.begin();i!=curgroup->children.end();++i) {
					if ((*i)->name==name) {
						foundobj=(*i);
						break;
					}
					if (Group* gr=dynamic_cast<Group*>(*i)) 
						stack.push_back(gr);
					
					if (Shape* sh=dynamic_cast<Shape*>(*i))  {
						if (sh->geometry->name==name) {
							foundobj=sh->geometry;
							break;
						}
					}
				}
			}
		}
		return foundobj;
	}
	
	void traverse(Group *group, traverse_callback callback) {
		vector<Group*> stack;
		Group* curgroup;
		stack.push_back(group);
		// Brede først algorithm
		while (!stack.empty()) {
			curgroup=stack.back();
			stack.pop_back();
			if (!callback(curgroup))
				return;
			for(vector<Drawable*>::iterator i=curgroup->children.begin();i!=curgroup->children.end();++i) {
				if (Group* gr=dynamic_cast<Group*>(*i)) 
					stack.push_back(gr);
				else 
					if (!callback(*i))
					return;
			}
		}
	}
}

