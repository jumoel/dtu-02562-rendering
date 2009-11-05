#ifndef __DRAW_H__

#include "TriMesh.h"
#include "Material.h"
#include "Texmap.h"
#include "Object.h"

namespace BMesh
{

	/** Draw the object. 
	The arguments are "object": The BMesh object being drawn.
	"smooth" determines whether the object is drawn with vertex
	normals or face normals. "use_texture" controls whether texture coordinates 
	are assigned and a texture is bound. "use_material" controls whether the 
	object should set its material parameters.
	NOTE: You must still enable GL_LIGHTING if you want the object to be
  drawn lit. */
	void gl_draw_object(Object& object,
											bool smooth = false,
											bool use_texture = false,
											bool use_material = false);

	/** Initialize textures. This function must be called before the 
			object is drawn - at least if it has any textures. */
	void gl_init_textures(Object& obj);

	/** Draw mesh with per face normals. 
			The first argument is the mesh, the second argument 
			determines whether texture coords are assigned for each vertex.
			The final argument determines whether colours coordinates are
			assigned for each vertex. Both texture and colour coords are assigned
			only if present and the respective arguments are true. */
	void gl_draw_mesh(TriMesh& mesh, bool use_texture, bool use_material);


	/** Draw mesh with per vertex normals. 
			The first argument is the mesh, the second argument 
			determines whether texture coords are assigned for each vertex.
			The final argument determines whether colours coordinates are
			assigned for each vertex. Both texture and colour coords are assigned
			only if present and the respective arguments are true. */
	void gl_draw_mesh_smooth(TriMesh& mesh, bool use_texture, bool use_material);

	/** Set OpenGL material according to the Material passed as arg. */
	void gl_apply_material( Material& material);

	/** Initialize textures for a single texmap. This function is rarely 
			called directly. See gl_init_textures(Object&). */
	void gl_init_textures( Texmap& texmap);




}
#endif
