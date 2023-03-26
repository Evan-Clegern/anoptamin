/********!
 * @file  glrender.cpp
 * 
 * @author
 * 	Evan Clegern <evanclegern.work@gmail.com>
 * 
 * @date
 * 	19 March 2023
 * 
 * @brief
 * 	Provides backend code for "include/glrender.hpp"
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

#include "../include/glrender.hpp"

namespace Anoptamin { namespace Graphics {
	
	//! Initializes the Rendering Object.
	c_RenderObject::c_RenderObject() {
		glGenVertexArrays(1, &GL_VAO);
		glBindVertexArray(GL_VAO);
		glGenBuffers(1, &GL_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, GL_VBO);
		glGenBuffers(1, &GL_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_IBO);
	}
	//! Initializes the Rendering Object and loads data from an existing volume.
	c_RenderObject::c_RenderObject(const Geometry::c_Volume& loadFrom) {
		glGenVertexArrays(1, &GL_VAO);
		glBindVertexArray(GL_VAO);
		glGenBuffers(1, &GL_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, GL_VBO);
		glGenBuffers(1, &GL_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_IBO);
		// TODO: load data from the volume.
		// Also, do we need to do extra culling? If so, do we need the current viewport angle and position?
		// And if that, then would we also have to then translate everything into the 'real area'?
		// That may need to be handled before calling the c_RenderObject...
	}
	
	//! Destroys the Rendering Object and frees the buffers.
	c_RenderObject::~c_RenderObject() {
		glDeleteBuffers(1, &(this->GL_VBO));
		glDeleteBuffers(1, &(this->GL_IBO));
		glDeleteVertexArrays(1, &(this->GL_VAO));
	}
		
}};
