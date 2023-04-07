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
	
	namespace Loading {
		/*
		struct c_Edge {
			double Length;
			c_Angle EdgeAngle;
			const Base::c_Point3D_Floating *PointA, *PointB;
		}
		struct c_Face_Triangle {
			double Area;
			Base::c_Point3D_Floating Center;
			c_Edge EdgeA, EdgeB, EdgeC;
			c_Face_Simple Points;
		}
		struct c_SerializedPoints {
			uint32_t ObjectPoints;
			std::vector<double> ObjectVertexes;
			std::vector<uint16_t> ObjectIndexes;
			
			bool IsVolume;
			union {
				Geometry::c_Volume* AsVolume;
				Geometry::c_Face_Triangle* AsTriangle;
			} Type;
		};
		*/
		LIBANOP_FUNC_CODEPT LIBANOP_FUNC_HOT const c_SerializedPoints serializeFace(const Geometry::c_Face_Triangle& face) {
			c_SerializedPoints TMP;
			TMP.IsVolume = false;
			TMP.Type.AsTriangle = &face;
			TMP.ObjectPoints = 3;
			std::vector<double> SerialPts = {
				face.Points.A.x, face.Points.A.y, face.Points.A.z,
				face.Points.B.x, face.Points.B.y, face.Points.B.z,
				face.Points.C.x, face.Points.C.y, face.Points.C.z
			};
			std::vector<uint16_t> SerialInd {0, 1, 2};
			TMP.ObjectIndexes = SerialInd;
			TMP.ObjectVertexes = SerialPts;
			return TMP;
		}
		LIBANOP_FUNC_CODEPT LIBANOP_FUNC_HOT const c_SerializedPoints serializeVolume(const Geometry::c_Volume& face) {
			c_SerializedPoints TMP;
			TMP.IsVolume = true;
			TMP.Type.AsVolume = &face;
			
			auto AllPoints = face.getAllPoints();
			
			TMP.ObjectPoints = AllPoints.size();
			std::vector<double> SerialPts;
			std::vector<uint16_t> SerialInd;
			
			uint16_t indx = 0;
			for (Base::c_Point3D_Floating i : AllPoints) {
				SerialInd.push_back(indx);
				SerialPts.push_back(i.x);
				SerialPts.push_back(i.y);
				SerialPts.push_back(i.z);
				indx++;
			}
			
			TMP.ObjectIndexes = SerialInd;
			TMP.ObjectVertexes = SerialPts;
			return TMP;
		}
		
		LIBANOP_FUNC_CODEPT LIBANOP_FUNC_HOT const c_SerializedPoints serializeVolume(const Geometry::c_Volume& face, Geometry::c_Angle relativeAngle) {
			c_SerializedPoints TMP;
			TMP.IsVolume = true;
			TMP.Type.AsVolume = &face;
			
			auto AllPoints = face.getAllPoints();
			
			// TODO: find culling method based on the relativeAngle modifier!
			
			TMP.ObjectPoints = AllPoints.size();
			std::vector<double> SerialPts;
			std::vector<uint16_t> SerialInd;
			
			uint16_t indx = 0;
			for (Base::c_Point3D_Floating i : AllPoints) {
				SerialInd.push_back(indx);
				SerialPts.push_back(i.x);
				SerialPts.push_back(i.y);
				SerialPts.push_back(i.z);
				indx++;
			}
			
			TMP.ObjectIndexes = SerialInd;
			TMP.ObjectVertexes = SerialPts;
			return TMP;
		}
	}
	
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
	void c_RenderObject::loadIBO_Prepared(uint32_t PointCount, const std::vector<uint16_t>& FlattenedIndexes) {
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
			bool couldBindIndexArray = false;
			check_video(couldBindIndexArray);
		}
		check_codelogic( (FlattenedIndexes.size() % PointCount == 0) );
		if (this->GL_STATIC) {
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, PointCount * sizeof(uint16_t), FlattenedIndexes.data(), GL_STATIC_DRAW );
		} else {
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, PointCount * sizeof(uint16_t), FlattenedIndexes.data(), GL_DYNAMIC_DRAW );
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
			bool couldLoadIndexArray = false;
			check_video(couldLoadIndexArray);
		}
		
		glBindVertexArray(0);
	}
	void c_RenderObject::loadSerialized(const Loading::c_SerializedPoints& Data) {
		check_codelogic(this->GL_VAO != 0);
		check_codelogic(this->GL_VBO != 0);
		check_codelogic(this->GL_IBO != 0);
		check_loaded(Data.ObjectPoints != 0);
		check_loaded(Data.ObjectIndexes.size() != 0);
		check_loaded(Data.ObjectVertexes.size() != 0);
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
			bool couldBindIndexArray = false;
			check_video(couldBindIndexArray);
		}
		if (this->GL_STATIC) {
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, Data.ObjectPoints * sizeof(uint16_t), Data.ObjectIndexes.data(), GL_STATIC_DRAW );
		} else {
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, Data.ObjectPoints * sizeof(uint16_t), Data.ObjectIndexes.data(), GL_DYNAMIC_DRAW );
		}
		Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogError("Render Object Error when loading index array!");
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
			bool couldLoadIndexArray = false;
			check_video(couldLoadIndexArray);
		}
		glBindBuffer(GL_ARRAY_BUFFER, this->GL_VBO);
		Error = glGetError();
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
			bool couldBindVertexArray = false;
			check_video(couldBindVertexArray);
		}
		if (this->GL_STATIC) {
			glBufferData( GL_ARRAY_BUFFER, Data.ObjectPoints * sizeof(double), Data.ObjectVertexes.data(), GL_STATIC_DRAW );
		} else {
			glBufferData( GL_ARRAY_BUFFER, Data.ObjectPoints * sizeof(double), Data.ObjectVertexes.data(), GL_DYNAMIC_DRAW );
		}
		Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogError("Render Object Error when loading vertex array!");
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
			bool couldLoadVertexArray = false;
			check_video(couldLoadVertexArray);
		}
		
		glBindVertexArray(0);
	}
}};
