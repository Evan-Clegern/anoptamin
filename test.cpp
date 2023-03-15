#include "include/base.hpp"
#include "include/sdl.hpp"
#include "include/glact.hpp"

#include <chrono>

std::atomic<bool> eWOE_Flag = false;

Anoptamin::Base::c_SDLWindow* BobWindow;

Anoptamin::Base::c_HookReturn exitWindowOnEsc(size_t inputVectorSize, uint16_t inputTypeSize, const void* inputVector) {
	const SDL_Event* EventList = static_cast<const SDL_Event*>(inputVector);
	check_ptr( EventList != NULL );

	Anoptamin::Base::c_HookReturn TopTMP;
	std::clock_t StartTicks = std::clock();
	TopTMP.Valid = 1;

	Anoptamin_LogDebug("Running Hooked Function (Inputs: " + std::to_string(inputVectorSize));


	for (size_t i = 0; i < inputVectorSize; i++) {
		const SDL_Event X = EventList[i];
		if (X.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
			Anoptamin_LogDebug("MWAAHAHAHAHAHAHAH!!!!");
			BobWindow->closeWindow(); break;
		} else if (X.key.keysym.scancode == SDL_SCANCODE_GRAVE) {
			// Prevents the 1-ms polling delay from messing with this.
			if (eWOE_Flag.load()) {
				eWOE_Flag.store(false); break;
			}
			if (BobWindow->windowFullscreen()) {
				BobWindow->exitFullscreen(); eWOE_Flag.store(true); break;
			} else {
				BobWindow->goFullscreen(); eWOE_Flag.store(true); break;
			}
		}
	}
	std::clock_t EndTicks = std::clock();
	TopTMP.ElapsedTicks = EndTicks - StartTicks;
	return TopTMP;
}

Anoptamin::Base::c_Hookable_Func exitWindowOnEsc_F = {0, exitWindowOnEsc};

int main() {
	Anoptamin::Log::SetupFiles();
	
	Anoptamin::initializeSDLGraphics();
	
	
	BobWindow = new Anoptamin::Base::c_SDLWindow(605, 300,
		"Test Window for The Doom Test", false, Anoptamin::Base::TYPE_GENERIC, true, true, false);
	Anoptamin_LogCommon("Window Created.");
	
	BobWindow->addHook_KeyboardEvent(exitWindowOnEsc_F);
	
	Anoptamin::Graphics::c_Window_Renderer autorender( BobWindow->getRawSDLWindow() );
	assert_runtime( Anoptamin::Graphics::initializeGL() );
	
	Anoptamin::Graphics::c_Render_Engine mainrenderer(autorender);
	mainrenderer.registerShader_Vertex( "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }" );
	mainrenderer.registerShader_Fragment("#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }");
	mainrenderer.compileWithShaders();
	assert_runtime( mainrenderer.renderEngineGood() );
	
	bool isclosed = 0;
	
	uint64_t sum_avg = 0;
	
	float vertexes[] = {
		-0.5, -0.5,
		0.5, -0.5,
		0.5, 0.5,
		-0.5, 0.5
	};
	uint32_t indexes[] = {
		0, 1, 2, 3
	};
	
	mainrenderer.loadDataVBO(sizeof(float) * 2 * 4, vertexes, true);
	mainrenderer.loadDataIBO(sizeof(uint32_t) * 4, indexes, true);
	int attrib2d = mainrenderer.getAttributeLocation("LVertexPos2D");
	
	uint64_t msst = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
	for (uint16_t i = 0; i < 1500; i++) {
		// This essentially gives us a 1 ms delay
		uint64_t mst_top = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
		std::vector<SDL_Event> Events = BobWindow->fullEventPoll();
		uint64_t mst_btm = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
		
		sum_avg += (mst_btm - mst_top);
		
		if (!BobWindow->isOpen()) {
			isclosed = 1;
			break;
		}
		mainrenderer.bindRenderer();
		// Draw the rectangle
		mainrenderer.bindAndDraw(attrib2d, 2, 4); // 2D points; 4 of them in total.
		
		mainrenderer.unbindRenderer();
	}
	uint64_t msed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
	std::cout << "The average event polling time was: " << (sum_avg / 1500.0) << " us, and the total time elapsed was: " << (msed - msst) << "ms.\n";
	// Change colors!
	if (!isclosed) {
		glClearColor(1.0, 0.0, 0.0, 0.8);
		glClear( GL_COLOR_BUFFER_BIT );
		for (uint16_t i = 0; i < 1500; i++) {
			std::vector<SDL_Event> Events = BobWindow->fullEventPoll();
			autorender.updateRenderer();
			if (!BobWindow->isOpen()) {
				isclosed = 1;
				break;
			}
		}
		mainrenderer.bindRenderer();
		mainrenderer.bindAndDraw(attrib2d, 2, 4); // 2D points; 4 of them in total.
		mainrenderer.unbindRenderer();
	}
	
	mainrenderer.shutdownEngine();

	if (!isclosed) BobWindow->closeWindow(); else {
		Anoptamin_LogCommon("Window Closed at User Bequest.");
	}
	// Delete the window
	delete BobWindow;
	Anoptamin_LogCommon("Window Closed.");
	
	// Finish up.
	
	Anoptamin::cleanupSDLGraphics();
	
	return 0;
}
