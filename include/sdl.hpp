/********!
 * @file  sdl.hpp
 * 
 * @author
 * 	Evan Clegern <evanclegern.work@gmail.com>
 * 
 * @date
 * 	4 March 2023
 * 
 * @brief
 * 	Provides all of the LibSDL2 includes and a wrapper class for
 *	setting up, controlling, and destroying a window and its surface.
 *	Also has mouse and keyboard input handling! Provides includes in:
 *		Anoptamin::Base
 * 
 * @note
 *	None of the classes implemented here are thread-safe. All should
 *	be managed from the main thread.
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


#ifndef anoptamin_SDL
#define anoptamin_SDL

#include "base.hpp"

#include <SDL2/SDL_clipboard.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_audio.h>
#include <SDL2/SDL_power.h>
#include <SDL2/SDL_timer.h>


namespace Anoptamin { namespace Base {

//! Identifies the type of window when construction a new c_SDLWindow.
enum e_SDLWindow_Type : uint8_t {
	TYPE_GENERIC,
	TYPE_NO_TASKBAR,
	TYPE_UTILITY,
	TYPE_TOOLTIP,
	TYPE_POPUP
};

//! Wrapper for any general SDL window. Implements basic window controls, surface control, and basic event access.
//! Also provides simple functions for window control (i.e. force focus, minimize, maximize, or title updates)
class c_SDLWindow {
	bool m_open = 0, m_hidden = 0;
	
	SDL_Window* mp_window;
	
	uint16_t m_windowHgt, m_windowWdt;
	std::string m_windowTitle;
	
	SDL_Surface* mp_baseSurf;
	
	SDL_Event m_windowEvents;
	
	c_Function_Hook m_hookKeyboard, m_hookMouseBtn, m_hookMouseMove, m_hookMouseScrl;
	
	//! Updates surface, then frees surface and closes window. Does not deinitialize the pointers.
	void cleanup();
public:
	//! Initializes and opens the window with an undefined or centered position.
	c_SDLWindow(uint16_t width, uint16_t height, std::string title, bool centerOnOpen, e_SDLWindow_Type openType = TYPE_GENERIC,
		bool allowResize = true, bool initOpenGL = false, bool openFullscreen = false);
	//! Initializes and opens the window at a specific position.
	c_SDLWindow(uint16_t width, uint16_t height, std::string title, int32_t posx, int32_t posy, bool centerOnOpen, e_SDLWindow_Type openType = TYPE_GENERIC,
		bool allowResize = true, bool initOpenGL = false, bool openFullscreen = false);
	//! Simple deconstructor -- just calls closeWindow()
	~c_SDLWindow();
	//! Calls the cleanup protocol, then nulls out the pointers and finishes window exit.
	void closeWindow();
	//! Query if the window is even open/valid.
	const bool isOpen() const noexcept;
	//! Deques as many events as possible and handles them if they're window related or if they're related to input hooks.
	std::vector<SDL_Event> fullEventPoll();
	/*
	Scancode List:
	
	SDL_SCANCODE_A = 4,
    SDL_SCANCODE_B = 5,
    SDL_SCANCODE_C = 6,
    SDL_SCANCODE_D = 7,
    SDL_SCANCODE_E = 8,
    SDL_SCANCODE_F = 9,
    SDL_SCANCODE_G = 10,
    SDL_SCANCODE_H = 11,
    SDL_SCANCODE_I = 12,
    SDL_SCANCODE_J = 13,
    SDL_SCANCODE_K = 14,
    SDL_SCANCODE_L = 15,
    SDL_SCANCODE_M = 16,
    SDL_SCANCODE_N = 17,
    SDL_SCANCODE_O = 18,
    SDL_SCANCODE_P = 19,
    SDL_SCANCODE_Q = 20,
    SDL_SCANCODE_R = 21,
    SDL_SCANCODE_S = 22,
    SDL_SCANCODE_T = 23,
    SDL_SCANCODE_U = 24,
    SDL_SCANCODE_V = 25,
    SDL_SCANCODE_W = 26,
    SDL_SCANCODE_X = 27,
    SDL_SCANCODE_Y = 28,
    SDL_SCANCODE_Z = 29,

    SDL_SCANCODE_1 = 30,
    SDL_SCANCODE_2 = 31,
    SDL_SCANCODE_3 = 32,
    SDL_SCANCODE_4 = 33,
    SDL_SCANCODE_5 = 34,
    SDL_SCANCODE_6 = 35,
    SDL_SCANCODE_7 = 36,
    SDL_SCANCODE_8 = 37,
    SDL_SCANCODE_9 = 38,
    SDL_SCANCODE_0 = 39,

    SDL_SCANCODE_RETURN = 40,
    SDL_SCANCODE_ESCAPE = 41,
    SDL_SCANCODE_BACKSPACE = 42,
    SDL_SCANCODE_TAB = 43,
    SDL_SCANCODE_SPACE = 44,

    SDL_SCANCODE_MINUS = 45,
    SDL_SCANCODE_EQUALS = 46,
    SDL_SCANCODE_LEFTBRACKET = 47,
    SDL_SCANCODE_RIGHTBRACKET = 48,
    SDL_SCANCODE_BACKSLASH = 49, 
    
    SDL_SCANCODE_NONUSHASH = 50, // unused!
    SDL_SCANCODE_SEMICOLON = 51,
    SDL_SCANCODE_APOSTROPHE = 52,
    SDL_SCANCODE_GRAVE = 53, // Tilde
    
    SDL_SCANCODE_PERIOD = 55,
    SDL_SCANCODE_SLASH = 56,

    SDL_SCANCODE_CAPSLOCK = 57,

    SDL_SCANCODE_F1 = 58,
    SDL_SCANCODE_F2 = 59,
    SDL_SCANCODE_F3 = 60,
    SDL_SCANCODE_F4 = 61,
    SDL_SCANCODE_F5 = 62,
    SDL_SCANCODE_F6 = 63,
    SDL_SCANCODE_F7 = 64,
    SDL_SCANCODE_F8 = 65,
    SDL_SCANCODE_F9 = 66,
    SDL_SCANCODE_F10 = 67,
    SDL_SCANCODE_F11 = 68,
    SDL_SCANCODE_F12 = 69,

    SDL_SCANCODE_PRINTSCREEN = 70,
    SDL_SCANCODE_SCROLLLOCK = 71,
    SDL_SCANCODE_PAUSE = 72,
    SDL_SCANCODE_INSERT = 73,
    
    SDL_SCANCODE_HOME = 74,
    SDL_SCANCODE_PAGEUP = 75,
    SDL_SCANCODE_DELETE = 76,
    SDL_SCANCODE_END = 77,
    SDL_SCANCODE_PAGEDOWN = 78,
    SDL_SCANCODE_RIGHT = 79,
    SDL_SCANCODE_LEFT = 80,
    SDL_SCANCODE_DOWN = 81,
    SDL_SCANCODE_UP = 82,

    SDL_SCANCODE_NUMLOCKCLEAR = 83,
    SDL_SCANCODE_KP_DIVIDE = 84,
    SDL_SCANCODE_KP_MULTIPLY = 85,
    SDL_SCANCODE_KP_MINUS = 86,
    SDL_SCANCODE_KP_PLUS = 87,
    SDL_SCANCODE_KP_ENTER = 88,
    SDL_SCANCODE_KP_1 = 89,
    SDL_SCANCODE_KP_2 = 90,
    SDL_SCANCODE_KP_3 = 91,
    SDL_SCANCODE_KP_4 = 92,
    SDL_SCANCODE_KP_5 = 93,
    SDL_SCANCODE_KP_6 = 94,
    SDL_SCANCODE_KP_7 = 95,
    SDL_SCANCODE_KP_8 = 96,
    SDL_SCANCODE_KP_9 = 97,
    SDL_SCANCODE_KP_0 = 98,
    SDL_SCANCODE_KP_PERIOD = 99,
	
	SDL_SCANCODE_LCTRL = 224,
    SDL_SCANCODE_LSHIFT = 225,
    SDL_SCANCODE_LALT = 226, 
    SDL_SCANCODE_LGUI = 227, // left windows sign or apple command
    SDL_SCANCODE_RCTRL = 228,
    SDL_SCANCODE_RSHIFT = 229,
    SDL_SCANCODE_RALT = 230, 
    SDL_SCANCODE_RGUI = 231, // right windows sign, apple command, or other gui interactor
	*/
	
	//! Gets the most recent key presses from the last event poll.
	LIBANOP_FUNC_HOT std::vector<SDL_Scancode> getLastKeys();
	//! Tests if a given key is pressed in last poll.
	LIBANOP_FUNC_HOT bool keyPressed(SDL_Scancode what);
	//! Hooks a function for its Keyboard Event hook.
	//! The hookable functions are expected to process a vector of SDL_Event objects (union member SDL_KeyboardEvent).
	uint16_t addHook_KeyboardEvent(const c_Hookable_Func& function);
	//! Hooks a function for its Mouse Button Event hook.
	//! The hookable functions are expected to process a vector of SDL_Event objects (union member SDL_MouseButtonEvent).
	uint16_t addHook_MouseButtonEvent(const c_Hookable_Func& function);
	//! Hooks a function for its Mouse Motion Event hook.
	//! The hookable functions are expected to process a vector of SDL_Event objects (union member SDL_MouseMotionEvent).
	uint16_t addHook_MouseMotionEvent(const c_Hookable_Func& function);
	//! Hooks a function for its Mouse Scroll Event hook.
	//! The hookable functions are expected to process a vector of SDL_Event objects (union member SDL_MouseScrollEvent).
	uint16_t addHook_MouseScrollEvent(const c_Hookable_Func& function);
	//! Gets the current height.
	const uint16_t getWindowHeight() const noexcept;
	//! Gets the current width.
	const uint16_t getWindowWidth() const noexcept;
	//! Hides the window.
	void hideWindow();
	//! Shows the window.
	void showWindow();
	//! Gets visibility.
	const bool getWindowVisiblity() const noexcept;
	//! Sets the window title.
	LIBANOP_FUNC_INPUTS_NONNULL void setTitle(const char* title);
	//! Sets the window title.
	void setTitle(std::string title);
	//! Gets the window title.
	const std::string getTitle() const noexcept;
	//! Gets the current flags and returns if we're minimized
	const bool windowMinimized() const noexcept;
	//! Gets the current flags and returns if we're maximized
	const bool windowMaximized() const noexcept;
	//! Gets the current flags and returns if we're fullscreen
	const bool windowFullscreen() const noexcept;
	//! Gets the current flags and returns if we've got mouse focus
	const bool windowHasMouse() const noexcept;
	//! Gets the current flags and returns if we've got general focus
	const bool windowHasFocus() const noexcept;
	//! Gets the current flags and returns if we have grabbed keyboard & mouse
	const bool windowFullFocus() const noexcept;
	//! Updates the internal dimensions info.
	void checkDimensions();
	//! Makes the window maximized
	void maximizeWindow();
	//! Makes the window minimized
	void minimizeWindow();
	//! Brings the window to the top for input focus.
	void focusWindow();
	//! Restores window from maximizing/minimizing
	void restoreFromMinMax();
	//! Refresh the draw surface
	void refreshWindowSurface();
	//! Grab the mouse
	void grabMouseFocus();
	//! Grab the keyboard
	void grabKeyboardFocus();
	//! Release input grab
	void releaseInputFocus();
	//! Returns the SDL_Window* for other actions is necessary
	SDL_Window* getRawSDLWindow();
	//! Returns the surface for drawing
	SDL_Surface* getRawSDLSurface();
	//! Makes the window flash once to get the user's attention
	void flashWindowOnce();
	//! Makes the window flash until the user takes focus on the window
	void flashWindowToFocus();
};



}} // End Anoptamin::Low

#endif
