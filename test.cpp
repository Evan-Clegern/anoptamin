#include "include/base.hpp"
#include "include/sdl.hpp"
#include "include/glact.hpp"

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
	
	bool isclosed = 0;
	for (uint16_t i = 0; i < 1500; i++) {
		// This essentially gives us a 1 ms delay
		std::vector<SDL_Event> Events = BobWindow->fullEventPoll();
		if (!BobWindow->isOpen()) {
			isclosed = 1;
			break;
		}
		autorender.updateRenderer();
	}
	std::cout << "Exchange Point.\n";
	// Change colors!
	if (!isclosed) {
		glClearColor(1.0, 0.0, 0.0, 0.8);
		for (uint16_t i = 0; i < 1500; i++) {
			std::vector<SDL_Event> Events = BobWindow->fullEventPoll();
			// Wait one millisecond
			if (!BobWindow->isOpen()) {
				isclosed = 1;
				break;
			}
			autorender.updateRenderer();
		}
	}

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
