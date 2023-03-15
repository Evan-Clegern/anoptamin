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
#include <GL/glew.h>     // Graphics Layer Extension Wrangler. Should handle OpenGL3 includes.
#include <GL/freeglut.h> // Free-and-open-source Graphics Layer Utility Tools (Cross-Platform)
#include <GL/glu.h>      // Graphics Layer Utilities (piping)

// SDL2 portion
// Don't include the full "sdl.hpp" because we just need to handle single contexts
#include <SDL2/SDL_surface.h>

namespace Anoptamin {
	//! Handles the setup of the SDL Subsystems for video.
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_COLD void initializeSDLGraphics();
	
	//! Handles the cleanup of both the SDL Subsystems and the graphical sysstems.
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_COLD void cleanupSDLGraphics();
namespace Graphics {
	//! Handles the linkage of SDL2 and OpenGL/GLEW.
	struct c_Window_Renderer {
		SDL_Window* ExternWindow;
		SDL_GLContext BridgeContext;
		
		c_Window_Renderer(SDL_Window* workFrom);
		~c_Window_Renderer();
		bool updateRenderer();
	};
	
	//! Initializes OpenGL, GLEW, GLUT and the sort. Can only be called AFTER a c_Window_Renderer is created.
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_COLD bool initializeGL();
	
	//! Handles the basic OpenGL and GLEW rendering system.
	class c_Render_Engine {
		c_Window_Renderer* mp_renderCtrl;
		
		uint32_t m_progID = 0;
		uint32_t m_VBOs = 0, m_IBOs = 0;
		std::vector<uint32_t> m_vertexShaders;
		std::vector<uint32_t> m_fragShaders;
		std::vector<uint32_t> m_otherShaders;
		bool m_valid = false;
	public:
		c_Render_Engine(c_Window_Renderer& baseRenderer);
		
		bool registerShader_Vertex(std::string source);
		bool registerShader_Fragment(std::string source);
	};
}} //End Anoptamin::Graphics

#endif
