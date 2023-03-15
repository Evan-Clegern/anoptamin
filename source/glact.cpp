/********!
 * @file  glact.cpp
 * 
 * @author
 * 	Evan Clegern <evanclegern.work@gmail.com>
 * 
 * @date
 * 	14 March 2023
 * 
 * @brief
 * 	Backend for "include/glact.hpp"
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

#include "../include/glact.hpp"

namespace Anoptamin {
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_COLD void initializeSDLGraphics() {
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		assert_libsdl( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0 );
		
		Anoptamin_LogDebug("Initialized LibSDL2 with expected GL version.");
	}
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_COLD void cleanupSDLGraphics() {
		SDL_Quit();
		
		Anoptamin_LogCommon("Deinitialized OpenGL and LibSDL2.");
		Anoptamin::Log::CleanupFiles();
	}
namespace Graphics {
	LIBANOP_FUNC_EXPORT c_Window_Renderer::c_Window_Renderer(SDL_Window* workFrom) {
		std::string nx = std::to_string( SDL_GetWindowID(workFrom) );
		Anoptamin_LogDebug("Creating OpenGL Context for Window #" + nx);
		ExternWindow = workFrom;
		BridgeContext = SDL_GL_CreateContext( workFrom );
		assert_libsdl(BridgeContext != NULL);
		
		if (SDL_GL_SetSwapInterval(1) < 0) {
			Anoptamin_LogInfo("Window Renderer unable to utilize VSYNC.");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
		}
		
		glClear( GL_COLOR_BUFFER_BIT );
		Anoptamin_LogDebug("Created OpenGL Context for Window #" + nx);
	}
	LIBANOP_FUNC_EXPORT c_Window_Renderer::~c_Window_Renderer() {
		SDL_GL_SwapWindow(this->ExternWindow);
		SDL_GL_DeleteContext( this->BridgeContext );
		SDL_UpdateWindowSurface(this->ExternWindow);
	}
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_HOT bool c_Window_Renderer::updateRenderer() {
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogWarn("Window Renderer detected OpenGL Error!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* Y = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(Y));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			GLenum glewError = glewInit();
			const uint8_t* Z = glewGetErrorString( glewError );
			X = (reinterpret_cast<const char*>(Z));
			Anoptamin_LogTrace("GLEW Error State: " + X); return false;
		}
		SDL_GL_SwapWindow(this->ExternWindow);
		Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogWarn("Window Renderer detected OpenGL Error!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* Y = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(Y));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			GLenum glewError = glewInit();
			const uint8_t* Z = glewGetErrorString( glewError );
			X = (reinterpret_cast<const char*>(Z));
			Anoptamin_LogTrace("GLEW Error State: " + X); return false;
		}
		return true;
	}
	
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_COLD bool initializeGL() {
		Anoptamin_LogDebug("Initializing GLEW.");
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK) {
			Anoptamin_LogError("GLEW Failed to Load!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			GLenum Error = glGetError();
			const uint8_t* Y = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(Y));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			const uint8_t* Z = glewGetErrorString( glewError );
			X = (reinterpret_cast<const char*>(Z));
			Anoptamin_LogTrace("GLEW Error State: " + X);
			return false;
		}
		const uint8_t* Y = glewGetString(GLEW_VERSION);
		std::string nval = (reinterpret_cast<const char*>(Y));
		const uint8_t* Z = glGetString(GL_VERSION);
		std::string xval = (reinterpret_cast<const char*>(Z));
		Anoptamin_LogDebug("GLEW Initialized; Using Version " + nval);
		Anoptamin_LogDebug("Initializing OpenGL, Version " + xval);
		
		GLenum Error = GL_NO_ERROR;
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogError("GL Failed to load identity for projection!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* V = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(V));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			return false;
		}
		Anoptamin_LogDebug("Loaded OpenGL with PROJECTION Matrix Mode.");
		
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogError("GL Failed to load identity for model viewing!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* V = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(V));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			return false;
		}
		Anoptamin_LogDebug("Loaded OpenGL with MODELVIEW Matrix Mode.");
		glClear( GL_COLOR_BUFFER_BIT );
		glClearColor( 0.1, 0.2, 0.4, 1.0 );
		glClear( GL_COLOR_BUFFER_BIT );
		Anoptamin_LogDebug("Initialized OpenGL.");
		
		Anoptamin_LogCommon("Graphical System Initialized.");
		return true;
	}
	
	
	c_Render_Engine::c_Render_Engine(c_Window_Renderer& baseRenderer) {
		mp_renderCtrl = &baseRenderer;
		m_progID = glCreateProgram();
		GLenum Error = GL_NO_ERROR;
		Error = glGetError();
		if (Error != GL_NO_ERROR || m_progID == 0) {
			Anoptamin_LogError("Failed to initialize OpenGL interface program!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* V = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(V));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
		} else {
			Anoptamin_LogCommon("OpenGL Interface Program Created, ID #" + std::to_string(m_progID));
			
			glGenBuffers(1, &m_VBO);
			glBindBuffer( GL_ARRAY_BUFFER, m_VBO );
			
			glGenBuffers(1, &m_IBO);
			glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );
			
			Error = glGetError();
			if (Error != GL_NO_ERROR) {
				Anoptamin_LogError("Failed to initialize OpenGL Buffers for Rendering Engine!");
				std::string X = SDL_GetError();
				Anoptamin_LogTrace("SDL2 Error State: " + X);
				const uint8_t* V = gluErrorString( Error );
				X = (reinterpret_cast<const char*>(V));
				Anoptamin_LogTrace("OpenGL Error State: " + X);
			}
			Anoptamin_LogDebug("OpenGL VBO and IBO buffers bound.");
			m_valid = true;
		}
	}
	bool c_Render_Engine::registerShader_Vertex(std::string source) {
		check_codelogic( this->m_valid );
		uint32_t nshader = glCreateShader( GL_VERTEX_SHADER );
		const char* tmpptr[] = {source.c_str()};
		glShaderSource( nshader, 1, tmpptr, NULL );
		glCompileShader( nshader );
		int32_t compiled = GL_FALSE;
		glGetShaderiv( nshader, GL_COMPILE_STATUS, &compiled );
		if ( compiled != GL_TRUE ) {
			Anoptamin_LogWarn("Failed to compile vertex shader for program #" + std::to_string(this->m_progID));
			int errloglen = 0, maxloglen = 0;
			glGetShaderiv( nshader, GL_INFO_LOG_LENGTH, &maxloglen );
			char* infolog = new char[maxloglen + 1];
			glGetShaderInfoLog( nshader, maxloglen, &errloglen, infolog );
			Anoptamin_LogTrace("OpenGL Shader Log: " + std::string(infolog));
			delete [] infolog;
			GLenum Error = glGetError();
			const uint8_t* V = gluErrorString( Error );
			std::string X = (reinterpret_cast<const char*>(V));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			return false;
		}
		glAttachShader( this->m_progID, nshader );
		m_vertexShaders.push_back(nshader);
		Anoptamin_LogDebug("Successfully compiled vertex shader for program #" + std::to_string(this->m_progID));
		return true;
	}
	bool c_Render_Engine::registerShader_Fragment(std::string source) {
		check_codelogic( this->m_valid );
		uint32_t nshader = glCreateShader( GL_FRAGMENT_SHADER );
		const char* tmpptr[] = {source.c_str()};
		glShaderSource( nshader, 1, tmpptr, NULL );
		glCompileShader( nshader );
		int32_t compiled = GL_FALSE;
		glGetShaderiv( nshader, GL_COMPILE_STATUS, &compiled );
		if ( compiled != GL_TRUE ) {
			Anoptamin_LogWarn("Failed to compile fragment shader for program #" + std::to_string(this->m_progID));
			int errloglen = 0, maxloglen = 0;
			glGetShaderiv( nshader, GL_INFO_LOG_LENGTH, &maxloglen );
			char* infolog = new char[maxloglen + 1];
			glGetShaderInfoLog( nshader, maxloglen, &errloglen, infolog );
			Anoptamin_LogTrace("OpenGL Shader Log: " + std::string(infolog));
			delete [] infolog;
			GLenum Error = glGetError();
			const uint8_t* V = gluErrorString( Error );
			std::string X = (reinterpret_cast<const char*>(V));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			return false;
		}
		glAttachShader( this->m_progID, nshader );
		m_fragShaders.push_back(nshader);
		Anoptamin_LogDebug("Successfully compiled fragment shader for program #" + std::to_string(this->m_progID));
		return true;
	}
	void c_Render_Engine::compileWithShaders() {
		check_codelogic( this->m_valid );
		check_video(glIsProgram(this->m_progID));
		glLinkProgram( this->m_progID );
		m_compiled = true;
	}
	bool c_Render_Engine::renderEngineGood() noexcept {
		if (!m_compiled) {
			Anoptamin_LogInfo("Called a check for the renderEngine before it was compiled.");
			this->compileWithShaders();
		}
		if (!this->m_valid) return false;
		if (!glIsProgram(this->m_progID)) return false;
		int32_t test = GL_TRUE;
		glGetProgramiv( this->m_progID, GL_LINK_STATUS, &test );
		if (test != GL_TRUE) {
			Anoptamin_LogError("Failed to link OpenGL render program #" + std::to_string(this->m_progID));
			int errloglen=0, maxloglen=0;
			glGetProgramiv( this->m_progID, GL_INFO_LOG_LENGTH, &maxloglen );
			char* infolog = new char[maxloglen + 1];
			glGetProgramInfoLog( this->m_progID, maxloglen, &errloglen, infolog );
			
			std::string X = ((infolog));
			Anoptamin_LogTrace("OpenGL Program Log: " + X);
			delete [] infolog;
			
			
			GLenum Error = glGetError();
			const uint8_t* V = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(V));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			
			
			return false;
		}
		return true;
	}
	void c_Render_Engine::shutdownEngine() {
		Anoptamin_LogDebug("Shutting down OpenGL render program #" + std::to_string(this->m_progID));
		this->m_valid = 0;
		for (auto i : this->m_fragShaders) {
			glDetachShader( this->m_progID, i );
		}
		this->m_fragShaders.clear();
		for (auto i : this->m_vertexShaders) {
			glDetachShader( this->m_progID, i );
		}
		this->m_vertexShaders.clear();
		this->m_compiled = 0;
		glDeleteProgram( this->m_progID );
		
		this->mp_renderCtrl->updateRenderer();
		Anoptamin_LogCommon("Shut down OpenGL Interface Program.");
	}
	
	void c_Render_Engine::bindRenderer() const {
		check_codelogic(this->m_valid);
		check_video(this->m_compiled);
		glUseProgram( this->m_progID );
	}
	void c_Render_Engine::unbindRenderer() const {
		check_codelogic(this->m_valid);
		check_video(this->m_compiled);
		glUseProgram( 0 );
	}
	int c_Render_Engine::getAttributeLocation(std::string what) const {
		check_codelogic(this->m_valid);
		check_video(this->m_compiled);
		int ReturnLoc = 0;
		ReturnLoc = glGetAttribLocation(this->m_progID, what.c_str());
		check_video(ReturnLoc != -1);
		return ReturnLoc;
	}
	
	
	//! Loads some data into the VBO buffer. If 'vbostatic' is true, then it will not allow the data buffer to be modified!
	LIBANOP_FUNC_HOT void c_Render_Engine::loadDataVBO(size_t vbosize, float* vbodata, bool vbostatic) {
		check_codelogic(this->m_valid);
		check_video(this->m_compiled);
		
		glBindBuffer(1, this->m_VBO);
		if (vbostatic) {
			glBufferData( GL_ARRAY_BUFFER, vbosize, vbodata, GL_STATIC_DRAW );
		} else {
			glBufferData( GL_ARRAY_BUFFER, vbosize, vbodata, GL_DYNAMIC_DRAW );
		}
	}
	//! Loads some data into the IBO buffer. If 'ibostatic' is true, then it will not allow the data buffer to be modified!
	LIBANOP_FUNC_HOT void c_Render_Engine::loadDataIBO(size_t ibosize, uint32_t* ibodata, bool ibostatic) {
		check_codelogic(this->m_valid);
		check_video(this->m_compiled);
		
		glBindBuffer(1, this->m_IBO);
		if (ibostatic) {
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, ibosize, ibodata, GL_STATIC_DRAW );
		} else {
			glBufferData( GL_ELEMENT_ARRAY_BUFFER, ibosize, ibodata, GL_DYNAMIC_DRAW );
		}
	}
	void c_Render_Engine::bindAndDraw(int32_t attribLocation, int8_t vertexSize, int32_t pointsRender) {
		check_codelogic(this->m_valid);
		check_video(this->m_compiled);
		
		glClear( GL_COLOR_BUFFER_BIT );
		glEnableVertexAttribArray(attribLocation);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
		glVertexAttribPointer( attribLocation, vertexSize, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), NULL );
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_IBO);
		glDrawElements( GL_TRIANGLE_FAN, pointsRender, GL_UNSIGNED_INT, NULL );
		glDisableVertexAttribArray(attribLocation);
		
		this->mp_renderCtrl->updateRenderer();
	}
}} //End Anoptamin::Graphics
