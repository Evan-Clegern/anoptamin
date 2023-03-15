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
 * 	Provides the base OpenGL interfaces and SDL2-OpenGL operations.
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


// Standard OpenGL
#include <GL/glew.h>     // Graphics Layer Extension Wrangler. Should handle OpenGL-ES2, i think? because including GL2.h makes it screeem
#include <GL/freeglut.h> // Free-and-open-source Graphics Layer Utility Tools (Cross-Platform)
#include <GL/glu.h>      // Graphics Layer Utilities (piping)

// SDL2 portion
// Don't include the full "sdl.hpp" because we just need to handle single contexts
#include <SDL2/SDL_surface.h>

namespace Anoptamin { 
	//! Handles the setup of the SDL Subsystems and the initialization of SDL for OpenGL.
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_COLD void initializeSDLGraphics();
namespace Graphics {
	
}} //End Anoptamin::Graphics

#endif
