/********!
 * @file  01_Hooked_Closing.cpp
 * 
 * @author
 * 	Evan Clegern <evanclegern.work@gmail.com>
 * 
 * @date
 * 	14 March 2023
 * 
 * @brief
 * 	This example file demonstrates how to use Hooked Functions with a
 *	c_SDLWindow object in order to make it close upon receiving an
 *	Escape key press, and how to utilize asserts and checks.
 *
 * @note
 *	Assuming your LibSDL2 implementation is stable, then this code
 *	should not abort irregularly if other keys are pressed, other
 *	input methods are used, if the window is closed with the 'X'
 *	button, or if you press the ESCAPE key. Using external signals
 *	is not handled.
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

#include "include/base.hpp"
#include "include/sdl.hpp"

// Pointer where we store our window object.
// Since we're explicitly closing the window from a hooked function, we need a pointer to the window.
// It is fine, however, to use a plain window object instead to avoid using 'new' and 'delete'.
Anoptamin::Base::c_SDLWindow* BobWindow;

//! This will be hooked to the Window's keyboard handler, so it will be triggered only if there's keyboard input.
//! This will only receive SDL_Event objects of type SDL_KeyboardEvent in the inputVector.
Anoptamin::Base::c_HookReturn exitWindowOnEsc(size_t inputVectorSize, uint16_t inputTypeSize, const void* inputVector) {
	const SDL_Event* EventList = static_cast<const SDL_Event*>(inputVector);
	// Ensure we weren't handed a NULL ptr.
	check_ptr( EventList != NULL );
	// This is the return data which all hooked functions, which requires runtime, validity, and output data.
	// However, since we're hooking into the window's event handlers, it doesn't expect data outputs.
	Anoptamin::Base::c_HookReturn TopTMP;
	std::clock_t StartTicks = std::clock();
	TopTMP.Valid = 1;
	// This is just intended to help visualize that we're running the function whenever the window sees keyboard input!
	Anoptamin_LogDebug("Running Hooked Function!");
	// Go through all of the valid Keyboard Events passed to us.
	for (size_t i = 0; i < inputVectorSize; i++) {
		const SDL_Event X = EventList[i];
		// Since SDL_Event is a union between, like, a dozen different events, we specify 'Keyboard'.
		// Then, we access its key symbol information, and test the scancode for if it's the 'ESC' key
		if (X.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
			// Close the window directly, since we have the power to do so in the main function.
			// Also, make a manical laugh in the log file about it.
			Anoptamin_LogDebug("MWAAHAHAHAHAHAHAH!!!!");
			BobWindow->closeWindow(); break;
		}
	}
	// Cleanup and return to the hook itself.
	std::clock_t EndTicks = std::clock();
	TopTMP.ElapsedTicks = EndTicks - StartTicks;
	return TopTMP;
}

// This sets that we do NOT expect no input, and that our hooked function is the one above.
Anoptamin::Base::c_Hookable_Func exitWindowOnEsc_F = {0, exitWindowOnEsc};

int main() {
	// Setup logging
	Anoptamin::Log::SetupFiles();
	std::cout << "Initializing Test Code.\n";
	
	// Make sure LIBSDL2 is working
	assert_libsdl( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == 0 );
	
	// Create the new window, with dimensions of 605 Wide, 300 Long, and a title of "Test Window for the Doom Test."
	// Other flags and info make it resizeable and have an OpenGL Context ready to be assigned.
	BobWindow = new Anoptamin::Base::c_SDLWindow(605, 300,
		"Test Window for The Doom Test", false, Anoptamin::Base::TYPE_GENERIC, true, true);
	Anoptamin_LogCommon("Window Created.");
	
	// Hook the function we setup earlier to the Window's keyboard hook.
	BobWindow->addHook_KeyboardEvent(exitWindowOnEsc_F);
	
	// Start a loop for handling user inputs and general window activity.
	bool isclosed = 0;
	for (uint16_t i = 0; i < 5000; i++) {
		// This gets all of the SDL_Event objects that have occurred since the last poll, and runs the hooks if any data is attached.
		std::vector<SDL_Event> Events = BobWindow->fullEventPoll();
		// Wait one millisecond
		SDL_Delay(1);
		if (!BobWindow->isOpen()) {
			isclosed = 1;
			break;
		}
	}
	// Close the window, if the user hasn't already.
	if (!isclosed) BobWindow->closeWindow(); else {
		Anoptamin_LogCommon("Window Closed at User Bequest.");
	}
	// Delete the window object itself.
	delete BobWindow;
	Anoptamin_LogCommon("Window Closed.");
	
	// Clean up the SDL2 instance(s).
	SDL_Quit();
	
	// Flushes and closes the log, and removes our directory in the temporary directory.
	Anoptamin::Log::CleanupFiles();
	
	return 0;
}
