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
		SDL_UpdateWindowSurface(this->ExternWindow);
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
		glClearColor( 0.2, 0.2, 0.2, 1.0 );
		glClear( GL_COLOR_BUFFER_BIT );
		Anoptamin_LogDebug("Initialized OpenGL.");
		
		Anoptamin_LogCommon("Graphical System Initialized.");
		return true;
	}
	
	
	c_Render_Engine::c_Render_Engine(c_Window_Renderer& baseRenderer) {
		mp_renderCtrl = &baseRenderer;
		m_progID = glCreateProgram();
		
	}
}} //End Anoptamin::Graphics
