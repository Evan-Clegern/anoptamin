#include "include/base.hpp"
#include "include/sdl.hpp"


Anoptamin::Base::c_SDLWindow* BobWindow;

Anoptamin::Base::c_HookReturn exitWindowOnEsc(size_t inputVectorSize, uint16_t inputTypeSize, const void* inputVector) {
	const SDL_Event* EventList = static_cast<const SDL_Event*>(inputVector);
	check_ptr( EventList != NULL );

	Anoptamin::Base::c_HookReturn TopTMP;
	std::clock_t StartTicks = std::clock();
	TopTMP.Valid = 1;

	Anoptamin_LogDebug("Running Hooked Function!");

	for (size_t i = 0; i < inputVectorSize; i++) {
		const SDL_Event X = EventList[i];
		if (X.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
			Anoptamin_LogDebug("MWAAHAHAHAHAHAHAH!!!!");
			BobWindow->closeWindow(); break;
		}
	}
	std::clock_t EndTicks = std::clock();
	TopTMP.ElapsedTicks = EndTicks - StartTicks;
	return TopTMP;
}

Anoptamin::Base::c_Hookable_Func exitWindowOnEsc_F = {0, exitWindowOnEsc};

int main() {
	Anoptamin::Log::SetupFiles();
	std::cout << "Initializing Test Code.\n";
	
	assert_libsdl( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0 );
	
	BobWindow = new Anoptamin::Base::c_SDLWindow(605, 300,
		"Test Window for The Doom Test", false, Anoptamin::Base::TYPE_GENERIC, true, true);
	Anoptamin_LogCommon("Window Created.");
	
	BobWindow->addHook_KeyboardEvent(exitWindowOnEsc_F);
	
	bool isclosed = 0;
	for (uint16_t i = 0; i < 5000; i++) {
		std::vector<SDL_Event> Events = BobWindow->fullEventPoll();
		// Wait one millisecond
		SDL_Delay(1);
		if (!BobWindow->isOpen()) {
			isclosed = 1;
			break;
		}
	}

	if (!isclosed) BobWindow->closeWindow(); else {
		Anoptamin_LogCommon("Window Closed at User Bequest.");
	}
	// Delete the window
	delete BobWindow;
	Anoptamin_LogCommon("Window Closed.");
	
	// Finish up.
	SDL_Quit();
	Anoptamin::Log::CleanupFiles();
	
	return 0;
}
