/********!
 * @file  sdl.cpp
 * 
 * @author
 * 	Evan Clegern <evanclegern.work@gmail.com>
 * 
 * @date
 * 	4 March 2023
 * 
 * @brief
 * 	Backend code for 'include/sdl.hpp'
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


#include "../include/sdl.hpp"

namespace Anoptamin { namespace Base {

LIBANOP_FUNC_CODEPT void c_SDLWindow::cleanup() {
	Anoptamin_LogDebug("Cleaning up window ID #" + std::to_string( SDL_GetWindowID(this->mp_window) ));
	SDL_UpdateWindowSurface( this->mp_window );
	
	SDL_FreeSurface( this->mp_baseSurf );
	
	SDL_DestroyWindow( this->mp_window );
	
	
	m_open = 0;
}

LIBANOP_FUNC_CODEPT c_SDLWindow::c_SDLWindow(uint16_t width, uint16_t height, std::string title, bool centerOnOpen,
	e_SDLWindow_Type openType, bool allowResize, bool initOpenGL, bool openFullscreen) {
	Anoptamin_LogDebug("Initializing new window.");
	m_windowWdt = width;
	m_windowHgt = height;
	m_windowTitle = title;
	
	assert_safety( SDL_WasInit( SDL_INIT_VIDEO ) == SDL_INIT_VIDEO );
	
	uint32_t flagsOpen = 0;
	if (initOpenGL) flagsOpen |= SDL_WINDOW_OPENGL;
	if (allowResize) flagsOpen |= SDL_WINDOW_RESIZABLE;
	if (openFullscreen) flagsOpen |= SDL_WINDOW_FULLSCREEN;
	
	switch (openType) {
		case TYPE_NO_TASKBAR:
			flagsOpen |= SDL_WINDOW_SKIP_TASKBAR; break;
		case TYPE_POPUP:
			flagsOpen |= SDL_WINDOW_POPUP_MENU; break;
		case TYPE_TOOLTIP:
			flagsOpen |= SDL_WINDOW_TOOLTIP; break;
		case TYPE_UTILITY:
			flagsOpen |= SDL_WINDOW_UTILITY; break;
		default:
			break;
	};
	
	if (centerOnOpen) mp_window = SDL_CreateWindow(title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		flagsOpen);
	else mp_window = SDL_CreateWindow(title.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		flagsOpen);
	
	std::string windowID = std::to_string( SDL_GetWindowID(this->mp_window) );
	assert_libsdl( mp_window != NULL );
	Anoptamin_LogDebug("Created a new window with ID #" + windowID );
	mp_baseSurf = SDL_GetWindowSurface( mp_window );
	assert_libsdl( mp_baseSurf != NULL );
	
	m_hookKeyboard.Name = ("Keyboard Hook for Window #" + windowID);
	m_hookKeyboard.CatchHookedErrors = 1;
	m_hookMouseBtn.Name = ("Mouse Button Hook for Window #" + windowID);
	m_hookMouseBtn.CatchHookedErrors = 1;
	m_hookMouseScrl.Name = ("Mouse Scroll Hook for Window #" + windowID);
	m_hookMouseScrl.CatchHookedErrors = 1;
	m_hookMouseMove.Name = ("Mouse Movement Hook for Window #" + windowID);
	m_hookMouseMove.CatchHookedErrors = 1;
	
	m_open = 1;
}

LIBANOP_FUNC_CODEPT c_SDLWindow::c_SDLWindow(uint16_t width, uint16_t height, std::string title, int32_t posx, int32_t posy, bool centerOnOpen,
	e_SDLWindow_Type openType, bool allowResize, bool initOpenGL, bool openFullscreen) {
	Anoptamin_LogDebug("Initializing new window.");
	m_windowWdt = width;
	m_windowHgt = height;
	m_windowTitle = title;
	
	assert_safety( SDL_WasInit( SDL_INIT_VIDEO ) == SDL_INIT_VIDEO );
	
	uint32_t flagsOpen = 0;
	if (initOpenGL) flagsOpen |= SDL_WINDOW_OPENGL;
	if (allowResize) flagsOpen |= SDL_WINDOW_RESIZABLE;
	if (openFullscreen) flagsOpen |= SDL_WINDOW_FULLSCREEN;
	
	switch (openType) {
		case TYPE_NO_TASKBAR:
			flagsOpen |= SDL_WINDOW_SKIP_TASKBAR; break;
		case TYPE_POPUP:
			flagsOpen |= SDL_WINDOW_POPUP_MENU; break;
		case TYPE_TOOLTIP:
			flagsOpen |= SDL_WINDOW_TOOLTIP; break;
		case TYPE_UTILITY:
			flagsOpen |= SDL_WINDOW_UTILITY; break;
		default:
			break;
	};
	
	if (centerOnOpen) mp_window = SDL_CreateWindow(title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		flagsOpen);
	else mp_window = SDL_CreateWindow(title.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		flagsOpen);
		
		
	std::string windowID = std::to_string( SDL_GetWindowID(this->mp_window) );
	assert_libsdl( mp_window != NULL );
	Anoptamin_LogDebug("Created a new window with ID #" + windowID );
	mp_baseSurf = SDL_GetWindowSurface( mp_window );
	assert_libsdl( mp_baseSurf != NULL );
	
	m_hookKeyboard.Name = ("Keyboard Hook for Window #" + windowID);
	m_hookKeyboard.CatchHookedErrors = 1;
	m_hookMouseBtn.Name = ("Mouse Button Hook for Window #" + windowID);
	m_hookMouseBtn.CatchHookedErrors = 1;
	m_hookMouseScrl.Name = ("Mouse Scroll Hook for Window #" + windowID);
	m_hookMouseScrl.CatchHookedErrors = 1;
	m_hookMouseMove.Name = ("Mouse Movement Hook for Window #" + windowID);
	m_hookMouseMove.CatchHookedErrors = 1;
	
	SDL_SetWindowPosition(mp_window, posx, posy);
	
	m_open = 1;
}

LIBANOP_FUNC_CODEPT c_SDLWindow::~c_SDLWindow() {
	
	if (this->m_open) {
		this->cleanup();
		this->mp_window = NULL;  // the SDL_FreeSurface and sort performs the freeing of these
		this->mp_baseSurf = NULL;
	}
	
}

LIBANOP_FUNC_CODEPT void c_SDLWindow::closeWindow() {
	
	if (this->m_open) {
		this->cleanup();
		this->mp_window = NULL;  // the SDL_FreeSurface and sort performs the freeing of these
		this->mp_baseSurf = NULL;
	}
	
}


LIBANOP_FUNC_CODEPT std::vector<SDL_Event> c_SDLWindow::fullEventPoll() {
	
	std::vector<SDL_Event> Out, KeyEvents, MouseBtnEvents, MouseScrlEvents, MouseMoveEvents;
	int32_t X;
	if (this->m_open) {
		do {
			X = SDL_PollEvent( &(this->m_windowEvents) );
			switch (this->m_windowEvents.type) {
				case SDL_QUIT:
					this->closeWindow();
					break;
				case SDL_WINDOWEVENT_CLOSE:
					this->closeWindow();
					this->m_windowEvents.type = SDL_QUIT;
					break;
				case SDL_WINDOWEVENT_SHOWN:
					this->m_hidden = 0;
					break;
				case SDL_WINDOWEVENT_HIDDEN:
					this->m_hidden = 1;
					break;
				case SDL_WINDOWEVENT_RESIZED:
					this->checkDimensions();
					break;
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					this->checkDimensions();
					break;
				case SDL_MOUSEMOTION:
					MouseMoveEvents.push_back(this->m_windowEvents);
					break;
				case SDL_MOUSEWHEEL:
					MouseScrlEvents.push_back(this->m_windowEvents);
					break;
				case SDL_MOUSEBUTTONUP:
					MouseBtnEvents.push_back(this->m_windowEvents);
					break;
				case SDL_MOUSEBUTTONDOWN:
					MouseBtnEvents.push_back(this->m_windowEvents);
					break;
				case SDL_KEYDOWN:
					KeyEvents.push_back(this->m_windowEvents);
					break;
				case SDL_KEYUP:
					KeyEvents.push_back(this->m_windowEvents);
					break;
				default:
					break;
			};
			Out.push_back(this->m_windowEvents);
		} while (X != 0);
	}
	
	if (MouseMoveEvents.size() != 0) {
		this->m_hookMouseMove.Invoke<SDL_Event>(MouseMoveEvents);
	}
	if (MouseScrlEvents.size() != 0) {
		this->m_hookMouseScrl.Invoke<SDL_Event>(MouseScrlEvents);
	}
	if (MouseBtnEvents.size() != 0) {
		this->m_hookMouseBtn.Invoke<SDL_Event>(MouseBtnEvents);
	}
	if (KeyEvents.size() != 0) {
		this->m_hookKeyboard.Invoke<SDL_Event>(KeyEvents);
	}
	return Out;
}

//! Hides the window.
LIBANOP_FUNC_CODEPT void c_SDLWindow::hideWindow() {
	if (this->m_hidden) return;
	
	assert_safety(this->m_open);
	SDL_HideWindow(this->mp_window);
	this->m_hidden = 1;
	
}
//! Shows the window
LIBANOP_FUNC_CODEPT void c_SDLWindow::showWindow() {
	if (!this->m_hidden) return;
	
	assert_safety(this->m_open);
	SDL_ShowWindow(this->mp_window);
	this->m_hidden = 0;
	
}
//! Gets visibility
LIBANOP_FUNC_CODEPT LIBANOP_FUNC_FIX_STATE const bool c_SDLWindow::getWindowVisiblity() const noexcept {
	return this->m_hidden;
}
//! Gets the current height.
LIBANOP_FUNC_CODEPT LIBANOP_FUNC_FIX_STATE const uint16_t c_SDLWindow::getWindowHeight() const noexcept {
	return this->m_windowHgt;
}
//! Gets the current width.
LIBANOP_FUNC_CODEPT LIBANOP_FUNC_FIX_STATE const uint16_t c_SDLWindow::getWindowWidth() const noexcept {
	return this->m_windowWdt;
}
LIBANOP_FUNC_CODEPT LIBANOP_FUNC_INPUTS_NONNULL void c_SDLWindow::setTitle(const char* title) {
	
	assert_safety(this->m_open);
	SDL_SetWindowTitle(this->mp_window, title);
	this->m_windowTitle = title;
	
}
LIBANOP_FUNC_CODEPT void c_SDLWindow::setTitle(std::string title) {
	
	assert_safety(this->m_open);
	SDL_SetWindowTitle(this->mp_window, title.c_str());
	this->m_windowTitle = title;
	
}
LIBANOP_FUNC_CODEPT LIBANOP_FUNC_FIX_STATE const std::string c_SDLWindow::getTitle() const noexcept {
	return this->m_windowTitle;
}

//! Gets the current flags and returns if we're minimized
LIBANOP_FUNC_CODEPT LIBANOP_FUNC_FIX_STATE const bool c_SDLWindow::windowMinimized() const noexcept {
	return (SDL_GetWindowFlags(this->mp_window) & SDL_WINDOW_MINIMIZED);
}
//! Gets the current flags and returns if we're maximized
LIBANOP_FUNC_CODEPT LIBANOP_FUNC_FIX_STATE const bool c_SDLWindow::windowMaximized() const noexcept {
	return (SDL_GetWindowFlags(this->mp_window) & SDL_WINDOW_MAXIMIZED);
}
//! Gets the current flags and returns if we're fullscreen
LIBANOP_FUNC_CODEPT LIBANOP_FUNC_FIX_STATE const bool c_SDLWindow::windowFullscreen() const noexcept {
	return (SDL_GetWindowFlags(this->mp_window) & SDL_WINDOW_FULLSCREEN);
}
//! Gets the current flags and returns if we've got mouse focus
LIBANOP_FUNC_CODEPT LIBANOP_FUNC_FIX_STATE const bool c_SDLWindow::windowHasMouse() const noexcept {
	return (SDL_GetWindowFlags(this->mp_window) & SDL_WINDOW_MOUSE_FOCUS);
}
//! Gets the current flags and returns if we've got general focus
LIBANOP_FUNC_CODEPT LIBANOP_FUNC_FIX_STATE const bool c_SDLWindow::windowHasFocus() const noexcept {
	return (SDL_GetWindowFlags(this->mp_window) & SDL_WINDOW_INPUT_FOCUS);
}
//! Gets the current flags and returns if we have grabbed keyboard & mouse
LIBANOP_FUNC_CODEPT LIBANOP_FUNC_FIX_STATE const bool c_SDLWindow::windowFullFocus() const noexcept {
	return ((SDL_GetWindowFlags(this->mp_window) & SDL_WINDOW_MOUSE_GRABBED) > 0) and ((SDL_GetWindowFlags(this->mp_window) & SDL_WINDOW_KEYBOARD_GRABBED) > 0);
}
LIBANOP_FUNC_CODEPT void c_SDLWindow::checkDimensions() {
	assert_safety( this->m_open );
	
	int tmpw, tmph;
	SDL_GetWindowSize( this->mp_window, &tmpw, &tmph );
	
	this->m_windowHgt = uint16_t(tmph); // I mean, when is a window going to be 65,000 pixels wide???
	this->m_windowWdt = uint16_t(tmpw);
	
}
//! Makes the window maximized
LIBANOP_FUNC_CODEPT void c_SDLWindow::maximizeWindow() {
	assert_safety( this->m_open );
	
	SDL_MaximizeWindow( this->mp_window );
	
}
//! Brings the window to the top for input focus.
LIBANOP_FUNC_CODEPT void c_SDLWindow::focusWindow() {
	assert_safety( this->m_open );
	
	SDL_RaiseWindow( this->mp_window );
	
}
//! Restores window from maximizing/minimizing
LIBANOP_FUNC_CODEPT void c_SDLWindow::restoreFromMinMax() {
	assert_safety( this->m_open );
	
	SDL_RestoreWindow( this->mp_window );
	
}
LIBANOP_FUNC_CODEPT void c_SDLWindow::refreshWindowSurface() {
	assert_safety( this->m_open );
	
	SDL_UpdateWindowSurface( this->mp_window );
	
}
//! Grab the mouse
LIBANOP_FUNC_CODEPT void c_SDLWindow::grabMouseFocus() {
	assert_safety( this->m_open );
	
	SDL_SetWindowMouseGrab( this->mp_window, SDL_TRUE );
	
}
//! Grab the keyboard
LIBANOP_FUNC_CODEPT void c_SDLWindow::grabKeyboardFocus() {
	assert_safety( this->m_open );
	
	SDL_SetWindowKeyboardGrab( this->mp_window, SDL_TRUE );
	
}
//! Release input grab
LIBANOP_FUNC_CODEPT void c_SDLWindow::releaseInputFocus() {
	assert_safety( this->m_open );
	
	SDL_SetWindowMouseGrab( this->mp_window, SDL_FALSE );
	SDL_SetWindowKeyboardGrab( this->mp_window, SDL_FALSE );
	
}

LIBANOP_FUNC_CODEPT SDL_Window* c_SDLWindow::getRawSDLWindow() {
	return this->mp_window;
}
LIBANOP_FUNC_CODEPT SDL_Surface* c_SDLWindow::getRawSDLSurface() {
	return this->mp_baseSurf;
}

//! Makes the window flash
LIBANOP_FUNC_CODEPT void c_SDLWindow::flashWindowOnce() {
	assert_safety( this->m_open );
	
	int FlashStatus = SDL_FlashWindow(this->mp_window, SDL_FLASH_BRIEFLY);
	assert_libsdl( FlashStatus == 0 );
	
}
LIBANOP_FUNC_CODEPT void c_SDLWindow::flashWindowToFocus() {
	assert_safety( this->m_open );
	
	int FlashStatus = SDL_FlashWindow(this->mp_window, SDL_FLASH_UNTIL_FOCUSED);
	assert_libsdl( FlashStatus == 0 );
	
}

//! Gets the most recent key presses from the last eventPollSelf() call.
LIBANOP_FUNC_CODEPT LIBANOP_FUNC_HOT std::vector<SDL_Scancode> c_SDLWindow::getLastKeys() {
	
	const uint8_t* Keystates = SDL_GetKeyboardState( NULL );
	assert_libsdl( Keystates != NULL );
	
	std::vector<SDL_Scancode> output;
	
	// Use the standard keyboard layout + basic numpad
	SDL_Scancode ix = SDL_SCANCODE_A;
	int* ip = (int*)(&ix); // this is disgusting, yes, but SDL defines the scancodes as a typedef enum and you can't iterate thru it normally
	for (; ix <= SDL_SCANCODE_KP_PERIOD; (*ip)++) {
		if (Keystates[ix]) {
			output.push_back(ix);
		}
	}
	// Get the Left/Right control, shift, alt, etc. keys
	ix = SDL_SCANCODE_LCTRL;
	for (; ix <= SDL_SCANCODE_RGUI; (*ip)++) {
		if (Keystates[ix]) {
			output.push_back(ix);
		}
	}
	
	return output;
}
//! Tests if a given key is pressed in last poll.
LIBANOP_FUNC_CODEPT LIBANOP_FUNC_HOT bool c_SDLWindow::keyPressed(SDL_Scancode what) {
	
	const uint8_t* Keystates = SDL_GetKeyboardState( NULL );
	assert_libsdl( Keystates != NULL );
	
	return (Keystates[what] != 0);
}


//! Hooks a function for its Keyboard Event hook.
//! The hookable functions are expected to process a vector of SDL_KeyboardEvent objects.
LIBANOP_FUNC_CODEPT uint16_t c_SDLWindow::addHook_KeyboardEvent(const c_Hookable_Func& function) {
	return this->m_hookKeyboard.HookFunction(function);
}
//! Hooks a function for its Mouse Button Event hook.
//! The hookable functions are expected to process a vector of SDL_MouseButtonEvent objects.
LIBANOP_FUNC_CODEPT uint16_t c_SDLWindow::addHook_MouseButtonEvent(const c_Hookable_Func& function) {
	return this->m_hookMouseBtn.HookFunction(function);
}
//! Hooks a function for its Mouse Motion Event hook.
//! The hookable functions are expected to process a vector of SDL_MouseMotionEvent objects.
LIBANOP_FUNC_CODEPT uint16_t c_SDLWindow::addHook_MouseMotionEvent(const c_Hookable_Func& function) {
	return this->m_hookMouseMove.HookFunction(function);
}
//! Hooks a function for its Mouse Scroll Event hook.
//! The hookable functions are expected to process a vector of SDL_MouseWheelEvent objects.
LIBANOP_FUNC_CODEPT uint16_t c_SDLWindow::addHook_MouseScrollEvent(const c_Hookable_Func& function) {
	return this->m_hookMouseScrl.HookFunction(function);
}

LIBANOP_FUNC_CODEPT const bool c_SDLWindow::isOpen() const noexcept {
	return this->m_open;
}

LIBANOP_FUNC_CODEPT void c_SDLWindow::goFullscreen() {
	assert_safety( this->m_open );
	check_video( SDL_SetWindowFullscreen(this->mp_window, SDL_WINDOW_FULLSCREEN) == 0 );
}
//! Makes the window leave fullscreen mode.
LIBANOP_FUNC_CODEPT void c_SDLWindow::exitFullscreen() {
	assert_safety( this->m_open );
	check_video( SDL_SetWindowFullscreen(this->mp_window, 0) == 0 );  // This call sets the fullscreen state to 0 (windowed)
}

}} // End Anoptamin::Low
