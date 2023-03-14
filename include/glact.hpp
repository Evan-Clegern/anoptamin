/********!
 * @file  glact.hpp
 * 
 * @author
 * 	Evan Clegern <evanclegern.work@gmail.com>
 * 
 * @date
 * 	14 March 2023
 * 
 * @brief
 * 	Provides the base OpenGL interfaces and SDL2 OpenGL interfaces.
 *	Provides includes in:
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


#ifndef anoptamin_GLact
#define anoptamin_GLact

#include "base.hpp"

// SDL2 portion
// Don't include the full "sdl.hpp" because we just need to handle single contexts
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_surface.h>

// OpenGL: Embedded Systems v2
// It isn't as efficient as GLES3, but more portable.
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>

// Standard OpenGL
#include <GL/gle.h>  // Graphics Layer Extensions
#include <GL/glew.h> // Graphics Layer Extension Wrangler
#include <GL/freeglut.h> // Free-and-open-source Graphics Layer Utility Tools (Cross-Platform)

namespace Anoptamin { namespace Graphics {
	
	
}} //End Anoptamin::Graphics

#endif
