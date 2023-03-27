/********!
 * @file  glrender.hpp
 * 
 * @author
 * 	Evan Clegern <evanclegern.work@gmail.com>
 * 
 * @date
 * 	19 March 2023
 * 
 * @brief
 * 	Provides a combination between simple geometry objects and the
 *	lower-level OpenGL implementation. This primarily involves making
 *	renderable primitives and renderable objects. Provides includes in:
 *		Anoptamin::Graphics
 * 
 * @copyright
 * 	Copyright (C) 2023 Evan Clegern
 * 
 * 	This program is free software: you can redistribute it and/or modify
 * 	it under the terms of the GNU General Public License, as published by
 * 	the Free Software Foundation, version 3 of the License.
 * 
 * 	This program is distributed in the hope that it will be useful,
 * 	but WITHOUT ANY WARRANTY; without even the implied warranty of
 * 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * 	GNU General Public License for more details.
 * 
 * 	You should have received a copy of the GNU General Public License
 * 	along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 ********/

#ifndef anoptamin_glrender
#define anoptamin_glrender

#include "../include/geometry.hpp"
#include "../include/glact.hpp"

namespace Anoptamin { namespace Graphics {
	
	//! Wrapper object which is intended to store the points and various buffers needed to draw any given primitive set.
	struct c_RenderObject {
		//! Whether or not we bind the data as static or dynamic
		bool GL_STATIC;
		//! Vertex Buffer Object. Stores vertexes (points) for rendering.
		uint32_t GL_VBO;
		//! Index Buffer Object. Stores the indexes in which OpenGL places the vertexes for drawing lines.
		uint32_t GL_IBO;
		//! Vertex Array Object. Stores vertex attributes, vertex data formatting, and links to other buffer objects.
		uint32_t GL_VAO;
		//! OpenGL-format vertex set.
		std::vector<double> GL_Vertexes;
		//! OpenGL-format index set.
		std::vector<uint32_t> GL_Indexes;
		
		//! Initializes the Rendering Object for future loading, and marks it as a static (one write) or dynamic (multi write) object.
		c_RenderObject(bool isStatic);
		//! Initializes the Rendering Object and loads data from an existing volume, and marks it as a static (one write) or dynamic (multi write) object.
		c_RenderObject(const Geometry::c_Volume& loadFrom, bool isStatic);
		//! Destroys the Rendering Object and frees the buffers.
		~c_RenderObject();
		
		//! Loads the GL-ready flattened vertexes into the render object's VBO
		void loadVBO_Prepared(uint32_t PointCount, const std::vector<double>& FlattenedVertexes);
		//! Loads the GL-ready flattened vertex indexes into the render object's IBO
		void loadIBO_Prepared(uint32_t PointCount, const std::vector<uint32_t>& FlattenedIndexes);
		
	};
	
}}; //End Anoptamin::Graphics

#endif
