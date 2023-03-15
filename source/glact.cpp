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
		
		if (SDL_GL_SetSwapInterval( 1 ) < 0) {
			Anoptamin_LogInfo("VSYNC Not Permitted?");
			std::string X = SDL_GetError();
			Anoptamin_LogTrace("SDL2 Error State: " + X);
		}
		
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
	}
namespace Graphics {
	
	
}} //End Anoptamin::Graphics
