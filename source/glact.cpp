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
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
		assert_libsdl( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0 );
		
		Anoptamin_LogDebug("Initialized LibSDL2 with expected GL version.");
		
		GLenum Error = GL_NO_ERROR;
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogFatal("GL Failed to load identity for projection!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* Y = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(Y));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			std::exit(-1);
		}
		Anoptamin_LogDebug("Loaded OpenGL2 with PROJECTION Matrix Mode.");
		
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
		Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogFatal("GL Failed to load identity for model viewing!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* Y = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(Y));
			Anoptamin_LogTrace("OpenGL Error State: " + X);
			std::exit(-2);
		}
		glClearColor( 0.2, 0.2, 0.2, 1.0 );
		glClear( GL_COLOR_BUFFER_BIT );
		Anoptamin_LogDebug("Loaded OpenGL2 with MODELVIEW Matrix Mode.");
		Anoptamin_LogDebug("Initialized OpenGL for LibSDL2 interface.");
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
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_HOT bool c_Window_Renderer::updateRenderer() {
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR) {
			Anoptamin_LogWarn("Window Renderer detected OpenGL Error!");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
			const uint8_t* Y = gluErrorString( Error );
			X = (reinterpret_cast<const char*>(Y));
			Anoptamin_LogTrace("OpenGL Error State: " + X); return false;
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
			Anoptamin_LogTrace("OpenGL Error State: " + X); return false;
		}
		return true;
	}
}} //End Anoptamin::Graphics
