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
	c_RenderObject::c_RenderObject(bool isStatic) {
		glGenVertexArrays(1, &GL_VAO);
		glBindVertexArray(GL_VAO);
		
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogError("Render Object Error when generating vertex array!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* Y = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(Y));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			GLenum glewError = glewInit();
			const uint8_t* Z = glewGetErrorString( glewError );
			X = (reinterpret_cast<const char*>(Z));
			Anoptamin_LogTrace("GLEW Error State: " + X);
			// For simplicity in logging
			bool couldGenerateVertArray = false;
			check_video(couldGenerateVertArray);
		}
		
		glGenBuffers(1, &GL_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, GL_VBO);
		glGenBuffers(1, &GL_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_IBO);
		Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogError("Render Object Error when binding buffers for VAO!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* Y = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(Y));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			GLenum glewError = glewInit();
			const uint8_t* Z = glewGetErrorString( glewError );
			X = (reinterpret_cast<const char*>(Z));
			Anoptamin_LogTrace("GLEW Error State: " + X);
			// For simplicity in logging
			bool couldAssignBuffers = false;
			check_video(couldAssignBuffers);
		}
		this->GL_STATIC = isStatic;
		glBindVertexArray(0);
	}
	//! Initializes the Rendering Object and loads data from an existing volume.
	c_RenderObject::c_RenderObject(const Geometry::c_Volume& loadFrom, bool isStatic) {
		glGenVertexArrays(1, &GL_VAO);
		glBindVertexArray(GL_VAO);
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogError("Render Object Error when generating vertex array!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* Y = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(Y));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			GLenum glewError = glewInit();
			const uint8_t* Z = glewGetErrorString( glewError );
			X = (reinterpret_cast<const char*>(Z));
			Anoptamin_LogTrace("GLEW Error State: " + X);
			// For simplicity in logging
			bool couldGenerateVertArray = false;
			check_video(couldGenerateVertArray);
		}
		glGenBuffers(1, &GL_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, GL_VBO);
		glGenBuffers(1, &GL_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_IBO);
		Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogError("Render Object Error when binding buffers for VAO!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* Y = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(Y));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			GLenum glewError = glewInit();
			const uint8_t* Z = glewGetErrorString( glewError );
			X = (reinterpret_cast<const char*>(Z));
			Anoptamin_LogTrace("GLEW Error State: " + X);
			// For simplicity in logging
			bool couldAssignBuffers = false;
			check_video(couldAssignBuffers);
		}
		this->GL_STATIC = isStatic;
		// TODO: load data from the volume.
		// Also, do we need to do extra culling? If so, do we need the current viewport angle and position?
		// And if that, then would we also have to then translate everything into the 'real area'?
		// That may need to be handled before calling the c_RenderObject...
	}
	
	//! Destroys the Rendering Object and frees the buffers.
	c_RenderObject::~c_RenderObject() {
		glBindVertexArray(this->GL_VAO);
		glDeleteBuffers(1, &(this->GL_VBO));
		glDeleteBuffers(1, &(this->GL_IBO));
		glDeleteVertexArrays(1, &(this->GL_VAO));
		glBindVertexArray(0);
	}
	
	
	//! Loads the GL-ready flattened vertexes into the render object's VBO
	void c_RenderObject::loadVBO_Prepared(uint32_t PointCount, const std::vector<double>& FlattenedVertexes) {
		check_codelogic(this->GL_VAO != 0);
		check_codelogic(this->GL_VBO != 0);
		check_codelogic(this->GL_IBO != 0);
		glBindVertexArray(this->GL_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->GL_VBO);
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogError("Render Object Error when binding vertex array!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* Y = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(Y));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			GLenum glewError = glewInit();
			const uint8_t* Z = glewGetErrorString( glewError );
			X = (reinterpret_cast<const char*>(Z));
			Anoptamin_LogTrace("GLEW Error State: " + X);
			// For simplicity in logging
			bool couldGenerateVertArray = false;
			check_video(couldGenerateVertArray);
		}
		check_codelogic( (FlattenedVertexes.size() % PointCount == 0) );
		if (this->GL_STATIC) {
			glBufferData( GL_ARRAY_BUFFER, PointCount * sizeof(double), FlattenedVertexes.data(), GL_STATIC_DRAW );
		} else {
			glBufferData( GL_ARRAY_BUFFER, PointCount * sizeof(double), FlattenedVertexes.data(), GL_DYNAMIC_DRAW );
		}
		Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogError("Render Object Error when loading data into vertex array!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* Y = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(Y));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			GLenum glewError = glewInit();
			const uint8_t* Z = glewGetErrorString( glewError );
			X = (reinterpret_cast<const char*>(Z));
			Anoptamin_LogTrace("GLEW Error State: " + X);
			// For simplicity in logging
			bool couldGenerateVertArray = false;
			check_video(couldGenerateVertArray);
		}
		
		glBindVertexArray(0);
	}
	//! Loads the GL-ready flattened vertex indexes into the render object's IBO
	void c_RenderObject::loadIBO_Prepared(uint32_t PointCount, const std::vector<uint32_t>& FlattenedIndexes) {
		check_codelogic(this->GL_VAO != 0);
		check_codelogic(this->GL_VBO != 0);
		check_codelogic(this->GL_IBO != 0);
		glBindVertexArray(this->GL_VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->GL_IBO);
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogError("Render Object Error when binding index array!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* Y = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(Y));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			GLenum glewError = glewInit();
			const uint8_t* Z = glewGetErrorString( glewError );
			X = (reinterpret_cast<const char*>(Z));
			Anoptamin_LogTrace("GLEW Error State: " + X);
			// For simplicity in logging
			bool couldGenerateVertArray = false;
			check_video(couldGenerateVertArray);
		}
		check_codelogic( (FlattenedIndexes.size() % PointCount == 0) );
		if (this->GL_STATIC) {
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, PointCount * sizeof(uint32_t), FlattenedIndexes.data(), GL_STATIC_DRAW );
		} else {
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, PointCount * sizeof(uint32_t), FlattenedIndexes.data(), GL_DYNAMIC_DRAW );
		}
		Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogError("Render Object Error when loading data into index array!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* Y = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(Y));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			GLenum glewError = glewInit();
			const uint8_t* Z = glewGetErrorString( glewError );
			X = (reinterpret_cast<const char*>(Z));
			Anoptamin_LogTrace("GLEW Error State: " + X);
			// For simplicity in logging
			bool couldGenerateVertArray = false;
			check_video(couldGenerateVertArray);
		}
		
		
		glBindVertexArray(0);
	}
}};
