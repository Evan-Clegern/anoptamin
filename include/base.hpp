/********!
 * @file  base.hpp
 * 
 * @author
 * 	Evan Clegern <evanclegern.work@gmail.com>
 * 
 * @date
 * 	1 March 2023
 * 
 * @brief
 * 	Provides base C++STL includes, minor SDL2 includes, utility macros,
 *	program hooks, and general assertion support, as well as the base
 *	logging facility for the game itself. Provides includes in:
 *		Anoptamin::Base
 *		Anoptamin::Log
 *
 * @note
 *	Since the BASE functionality is intended to be established before
 *	the use of any concurrency, the only thread-safe functions are
 *	the general logging functions. Everything else is either a once-called
 *	and/or an abort-the-program-called sort of deal.
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


#ifndef anoptamin_base
#define anoptamin_base

// SDL provides some similar low-level utilities to those provided in Boost.



#if (defined(__WIN32__) || defined(__WINRT__) || defined(__CYGWIN__) || defined(__OS2__) || defined(_MSC_VER))
	#define LIBANOP_WINDOWS 1
#else
	#define LIBANOP_WINDOWS 0
#endif

#if defined(__GNUC__)
	#if (__GNUC__ >= 4)
		#define LIBANOP_GNU 1
	#else
		#define LIBANOP_GNU 0
	#endif
#else
	#define LIBANOP_GNU 0
#endif

#ifndef LIBANOP_FUNC_IMPORT
	#if LIBANOP_WINDOWS
		#define LIBANOP_FUNC_IMPORT extern __declspec(dllimport)
	#else
		#define LIBANOP_FUNC_IMPORT extern
	#endif
#endif

#ifndef LIBANOP_FUNC_EXPORT
	#if LIBANOP_WINDOWS
		#define LIBANOP_FUNC_EXPORT __declspec(dllexport)
	#elif LIBANOP_GNU
		#define LIBANOP_FUNC_EXPORT __attribute__((used, visibility("default")))
	#else
		#define LIBANOP_FUNC_EXPORT /* exported */
	#endif
#endif

#ifndef LIBANOP_FUNC_COLD
	#if LIBANOP_GNU
		#define LIBANOP_FUNC_COLD __attribute__((cold))
	#else
		#define LIBANOP_FUNC_COLD /* not used often */
	#endif
#endif

#ifndef LIBANOP_FUNC_HOT
	#if LIBANOP_GNU
		#define LIBANOP_FUNC_HOT __attribute__((hot))
	#else
		#define LIBANOP_FUNC_HOT /* used often */
	#endif
#endif

#ifndef LIBANOP_FUNC_DEPRECATED
	#if LIBANOP_WINDOWS
		#define LIBANOP_FUNC_DEPRECATED __declspec(deprecated)
	#elif LIBANOP_GNU
		#define LIBANOP_FUNC_DEPRECATED __attribute__((deprecated))
	#else
		#define LIBANOP_FUNC_DEPRECATED /* deprecated */
	#endif
#endif

#ifndef LIBANOP_FUNC_NO_EXIT
	#if LIBANOP_WINDOWS
		#define LIBANOP_FUNC_NO_EXIT __declspec(noreturn)
	#elif LIBANOP_GNU
		#define LIBANOP_FUNC_NO_EXIT __attribute__((noreturn))
	#else
		#define LIBANOP_FUNC_NO_EXIT /* does not return */
	#endif
#endif

#ifndef LIBANOP_FUNC_FIXED_RETURN
	#if LIBANOP_GNU
		#define LIBANOP_FUNC_FIXED_RETURN __attribute__((const))
	#else
		#define LIBANOP_FUNC_FIXED_RETURN /* fixed return value */
	#endif
#endif

//! Doesn't modify ANYTHING in the program state except for non-constant pointers provided to it.
#ifndef LIBANOP_FUNC_FIX_STATE
	#if LIBANOP_WINDOWS
		#define LIBANOP_FUNC_FIX_STATE __declspec(noalias)
	#elif LIBANOP_GNU
		#define LIBANOP_FUNC_FIX_STATE __attribute__((pure))
	#else
		#define LIBANOP_FUNC_FIX_STATE /* no state changes */
	#endif
#endif

#ifndef LIBANOP_FUNC_INPUTS_NONNULL
	#if LIBANOP_GNU
		#define LIBANOP_FUNC_INPUTS_NONNULL __attribute__((nonnull))
	#else
		#define LIBANOP_FUNC_INPUTS_NONNULL /* do not provide with null pointers */
	#endif
#endif

#ifndef LIBANOP_FUNC_NOINLINE
	#if LIBANOP_GNU
		#define LIBANOP_FUNC_NOINLINE __attribute__((noinline))
	#elif LIBANOP_WINDOWS
		#define LIBANOP_FUNC_NOINLINE __declspec(noinline)
	#else
		#define LIBANOP_FUNC_NOINLINE /* mr compiler, pleas no inline ): */
	#endif
#endif

#ifndef LIBANOP_FUNC_HEADERPT
	#define LIBANOP_FUNC_HEADERPT LIBANOP_FUNC_IMPORT LIBANOP_FUNC_NOINLINE
#endif
#ifndef LIBANOP_FUNC_CODEPT
	#define LIBANOP_FUNC_CODEPT LIBANOP_FUNC_EXPORT LIBANOP_FUNC_NOINLINE
#endif


// Standard Library I/O
#include <filesystem>
#include <iostream>
#include <fstream>

// Standard Library Theads
#include <thread>
#include <atomic>
#include <mutex>

// Standard Library Storage Primitives
#include <vector>
#include <string>
#include <array>

// Standard Library Utilities
#include <stdexcept>
#include <cstdlib>
#include <cerrno>
#include <random>
#include <cmath>
#include <ctime>

// Simple DirectMedia Core
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>

// SDL Shared Object support
#include <SDL2/SDL_loadso.h>

// GLIBC backtrace. Only include from the GNU C library.
#include <execinfo.h>

// Utilities (Stacktraces, assertions, macro stringifies, and logging)

#ifndef anoptamin_utilities
	#define anoptamin_utilities 1

	#define anoptamin_stringify(n) #n

namespace Anoptamin { namespace Base {
	static std::filesystem::path anoptamin_TMPpath;
	static std::filesystem::path anoptamin_LOGpath;
	static std::filesystem::path anoptamin_BASEpath;
	static std::ofstream anoptamin_logf;
	static std::clock_t anoptamin_stclock;
	static bool anoptamin_logopen = 0;

	//! Performs a semi-demangled stacktrace, and prints to stderr.
	void LIBANOP_FUNC_COLD LIBANOP_FUNC_IMPORT dbg_stacktrace();
	//! Prints out information regarding a failed assertion, and handles closing the program.
	void LIBANOP_FUNC_COLD LIBANOP_FUNC_INPUTS_NONNULL LIBANOP_FUNC_IMPORT LIBANOP_FUNC_NO_EXIT dbg_assertfunc(const char* type, const char* func, uint32_t line, const char* file, const char* expr);
	//! Prints out information regarding a failed check, but doesn't abort the program or scream bloody murder.
	void LIBANOP_FUNC_COLD LIBANOP_FUNC_INPUTS_NONNULL LIBANOP_FUNC_IMPORT dbg_checkfunc(const char* type, const char* func, uint32_t line, const char* file, const char* expr);
	
	//! A 3D coordinate with no decimal positions and only 2^32 possible positions along a single axis.
	struct c_Point3D_Integer {
		int32_t x, y, z;
		c_Point3D_Integer();
		c_Point3D_Integer(int32_t ix, int32_t iy, int32_t iz);
		c_Point3D_Integer(const c_Point3D_Integer& other);
	};
	//! A 3D coordinate with decimal positions.
	struct c_Point3D_Floating {
		double x, y, z;
		c_Point3D_Floating();
		c_Point3D_Floating(double ix, double iy, double iz);
		c_Point3D_Floating(const c_Point3D_Floating& other);
		c_Point3D_Floating(const c_Point3D_Integer& base);
	};
}}

	// Linear search
	template<typename T> bool vectorContains(const std::vector<T>& main, T lookfor) {
		for (size_t i = 0; i < main.size(); i++) {
			if (main.at(i) == lookfor) return true;
		}
		return false;
	}

	// Assertions.
	// Please use these for sanity checks or for things so large that it would constitute aborting the program.
	// Do NOT use these in, like, hooked functions or for "oh no, I can't move the window."
	
	//! Safety assertion. Used for conditions where program stability would be compromised.
	#define assert_safety(condition) if (!(condition)) {Anoptamin::Base::dbg_assertfunc("Safety", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(condition));}
	//! Security assertion. Used for conditions where data or user access would be compromised.
	#define assert_security(condition) if (!(condition)) {Anoptamin::Base::dbg_assertfunc("Security", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(condition));}
	//! File I/O assertion. Used for failures on OS side or for bad permissions when performing file I/O.
	#define assert_fileio(condition) if (!(condition)) {Anoptamin::Base::dbg_assertfunc("File I/O", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(condition));}
	//! SDL2 assertion. Used for failures in LibSDL2.
	#define assert_libsdl(condition) if (!(condition)) {Anoptamin::Base::dbg_assertfunc("LibSDL2", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(condition));}
	//! Runtime assertion. Used for conditions which should never appear except in errorneous conditions.
	#define assert_runtime(condition) if (!(condition)) {Anoptamin::Base::dbg_assertfunc("Runtime", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(condition));}
	
	// Checks.
	// These are almost exactly the same as assertions, but instead the raise exceptions.
	// Unless it's during initialization or is an unrecoverable problem, use checks over asserts.
	// There's also more specific checks than there are asserts.
	
	//! Pointer Safety check. Used for any pointer safety condition (i.e., not null). Throws invalid_argument.
	#define check_ptr(cond) if (!(cond)) {Anoptamin::Base::dbg_checkfunc("Pointer Safety", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(cond)); throw std::invalid_argument("Pointer Safety");};
	//! Parameter check. Used for checking the validity of any non-pointer inputs for a function. Throws invalid_argument.
	#define check_param(cond) if (!(cond)) {Anoptamin::Base::dbg_checkfunc("Parameter", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(cond)); throw std::invalid_argument("Parameter");};
	//! Loaded Data check. Used for checking the validity of loaded data. Throws runtime_error
	#define check_loaded(cond) if (!(cond)) {Anoptamin::Base::dbg_checkfunc("Loaded Data", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(cond)); throw std::runtime_error("Loaded Data");};
	//! Threading check. Used for multithreading problems. Throws runtime_error.
	#define check_thread(cond) if (!(cond)) {Anoptamin::Base::dbg_checkfunc("Threading", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(cond)); throw std::runtime_error("Threading");};
	//! Hook check. Used for both hooked functions and their hooks. Throws runtime_error.
	#define check_hooked(cond) if (!(cond)) {Anoptamin::Base::dbg_checkfunc("Hooking", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(cond)); throw std::runtime_error("Hooking");};
	//! Video check. Used for non-fatal problems in OpenGL or LibSDL2. Throws runtime_error.
	#define check_video(cond) if (!(cond)) {Anoptamin::Base::dbg_checkfunc("Video System", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(cond)); throw std::runtime_error("Video System");};
	//! Search/Sort check. Used for failures in sort or search algorithms. Throws runtime_error.
	#define check_srchsort(cond) if (!(cond)) {Anoptamin::Base::dbg_checkfunc("Search/Sort", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(cond)); throw std::runtime_error("Search/Sort");};
	//! Bounding check. Used for any general out-of-bounds problem. Throws range_error.
	#define check_bounds(cond) if (!(cond)) {Anoptamin::Base::dbg_checkfunc("Bounding", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(cond)); throw std::range_error("Bounding");};
	//! User Activity check. Used for any user inputs or actions. Throws runtime_error.
	#define check_useract(cond) if (!(cond)) {Anoptamin::Base::dbg_checkfunc("User Activity", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(cond)); throw std::runtime_error("User Activity");};
	//! Code Logic check. Used for any other problem that would arise from faulty internal logic. Throws logic_error.
	#define check_codelogic(cond) if (!(cond)) {Anoptamin::Base::dbg_checkfunc("Code Logic", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(cond)); throw std::logic_error("Code Logic");};
	//! Runtime checl. Used for any other problem that is difficult to predict and which is beyond basic program logic. Throws runtime_error.
	#define check_runtime(cond) if (!(cond)) {Anoptamin::Base::dbg_checkfunc("Runtime", __PRETTY_FUNCTION__, __LINE__, __FILE__, anoptamin_stringify(cond)); throw std::runtime_error("Runtime");};
#endif

#ifndef anoptamin_logging
#define anoptamin_logging 1

namespace Anoptamin { namespace Log {
	//! Sets up the session log file and gets the temporary files directory from the current directory. Not thread safe.
	void LIBANOP_FUNC_COLD LIBANOP_FUNC_IMPORT SetupFiles();
	
	//! Closes the logging file and cleans up our temporary directory.
	void LIBANOP_FUNC_COLD LIBANOP_FUNC_IMPORT CleanupFiles();
	
	enum e_LogSeverity : uint8_t {
		LOG_TRACE,  //! Only follows WARN, ERROR or FATAL messages
		LOG_DEBUG,  //! Lowest level log information
		LOG_COMMON, //! Low level 'success'/'standard' log information (i.e., "We just finished this task")
		LOG_INFO,   //! Low level log information
		LOG_WARN,   //! Medium level log information, solvable
		LOG_ERROR,  //! High level log information, barely recoverable
		LOG_FATAL   //! The "uh oh" status. Automatically logs the stacktrace, and other things (i.e., what gets printed on assert failure)
	};
	
	//! Logs the current stack to the logfile.
	void LIBANOP_FUNC_COLD LIBANOP_FUNC_NOINLINE LIBANOP_FUNC_IMPORT LogTrace();
	std::mutex LogTrace_Mutex;
	
	//! Logs a given message with severity.
	void LIBANOP_FUNC_HOT LIBANOP_FUNC_NOINLINE LIBANOP_FUNC_IMPORT Log(e_LogSeverity SEV, std::string MSG);
	std::mutex Log_Mutex;
}} // End Anoptamin::Log

#define Anoptamin_LogTrace(msg)  Anoptamin::Log::Log(Anoptamin::Log::e_LogSeverity::LOG_TRACE, msg)
#define Anoptamin_LogDebug(msg)  Anoptamin::Log::Log(Anoptamin::Log::e_LogSeverity::LOG_DEBUG, msg)
#define Anoptamin_LogCommon(msg) Anoptamin::Log::Log(Anoptamin::Log::e_LogSeverity::LOG_COMMON, msg)
#define Anoptamin_LogInfo(msg)   Anoptamin::Log::Log(Anoptamin::Log::e_LogSeverity::LOG_INFO, msg)
#define Anoptamin_LogWarn(msg)   Anoptamin::Log::Log(Anoptamin::Log::e_LogSeverity::LOG_WARN, msg)
#define Anoptamin_LogError(msg)  Anoptamin::Log::Log(Anoptamin::Log::e_LogSeverity::LOG_ERROR, msg)
#define Anoptamin_LogFatal(msg)  Anoptamin::Log::Log(Anoptamin::Log::e_LogSeverity::LOG_FATAL, msg)

#endif

#ifndef anoptamin_hooks
#define anoptamin_hooks 1

// Implementation of basic hook-events
namespace Anoptamin { namespace Base {
	//! Holds return data from a Hooked function; the 'MainData' is intended for serializing whatever is needed.
	struct c_HookReturn {
		std::vector<uint8_t> MainData;
		uint32_t ElapsedTicks;
		bool Valid;
	};
	
	//! Holds the pointer and some flags for a hookable function.
	//! All hookable functions must take the parameter vector size (size_t), the vector type size (uint16_t), and the input data (const void*).
	//! All hookable functions must return the 'c_HookReturn' data and update its fields accordingly.
	//! All hookable functions cannot utilize multithreading! They must be designed and optimized for single thread execution.
	struct c_Hookable_Func {
		bool Func_NoInputs = 0;
		c_HookReturn (*Function)(size_t, uint16_t, const void*);
	};
	
	//! Allows for proper functions to be registered under a hook, which then can be invoked to call its child functions.
	//! Uses MUTEXES in order to provide thread safety on its end; cannot be guaranteed for Hookable Functions (beyond stipulated above).
	struct c_Function_Hook {
		std::string Name;
		std::vector<c_Hookable_Func> HookedFuncs;
		std::mutex HookLock, InvokeLock; // Only one thread can invoke the hook at a time.
		bool CatchHookedErrors;
		
		c_Function_Hook(const char* title, bool catchErrs = 0);
		
		c_Function_Hook();
		
		//! Copies over the name and hook config, but none of the hooked functions.
		c_Function_Hook(const c_Function_Hook& b);
		
		//! Adds a new function to the list of hooked functions, and returns the size of the current HookedFuncs vector.
		uint16_t HookFunction(const c_Hookable_Func& function);
		
		//! Invokes the functions which are hooked to this hook, with the provided data vector, and tries to handle errors.
		template<typename T> std::vector<c_HookReturn> Invoke(std::vector<T> Data) {
			this->InvokeLock.lock();
			std::vector<c_HookReturn> returnable;
			
			const void* RawPtr = static_cast<void*>(Data.data());
			assert_safety( RawPtr != NULL );
			const uint16_t SizeData = sizeof(T); const size_t SizeVector = Data.size();
			
			for (uint16_t i = 0; i < HookedFuncs.size(); i++) {
				c_Hookable_Func& X = this->HookedFuncs.at(i);
				c_HookReturn N; N.MainData = {}; N.Valid = 0;
				try {
					if(X.Func_NoInputs) N = X.Function(0, 0, NULL); else N = X.Function(SizeVector, SizeData, RawPtr);
				} catch (std::exception* E) {
					if (this->CatchHookedErrors) {
						std::string X = E->what();
						Anoptamin_LogWarn("Caught exception in Hook '" + this->Name + "', Function #" + std::to_string(i));
						Anoptamin_LogTrace("Error Info: " + X);
						N.Valid = 0;
					} else {
						throw *E;
					}
				}
				returnable.push_back(N);
			}
			this->InvokeLock.unlock();
			return returnable;
		}
	};
}} // End Anoptamin::Base

#endif

#endif
