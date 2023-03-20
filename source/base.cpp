/********!
 * @file  base.cpp
 * 
 * @author
 * 	Evan Clegern <evanclegern.work@gmail.com>
 * 
 * @date
 * 	2 March 2023
 * 
 * @brief
 * 	Backend code for 'include/base.hpp'
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

#include "../include/base.hpp"

namespace Anoptamin {
	
	namespace Base {
		//! Seeds the random number generator.
		LIBANOP_FUNC_COLD LIBANOP_FUNC_NOINLINE LIBANOP_FUNC_IMPORT void seedEngine() {
			std::time_t now = std::time(NULL);
			uint64_t* rand0 = new uint64_t;
			uint64_t* rand1 = new uint64_t;
			uint64_t* rand2 = new uint64_t;
			uint64_t oval = 0xA5A50FF00FF05A5A;
			oval ^= *rand0;
			oval ^= uint64_t(rand0); //use address as well
			oval ^= *rand1;
			oval ^= uint64_t(rand1);
			oval ^= *rand2;
			oval ^= uint64_t(rand2);
			delete rand0;
			delete rand1;
			delete rand2;
			RANDengine.seed( uint64_t(now) ^ oval );
		}
	
		void LIBANOP_FUNC_COLD LIBANOP_FUNC_CODEPT dbg_stacktrace() {
			uint64_t* pointers[64];
			
			int entries = backtrace((void**)pointers, 64);
			
			char** listOf = backtrace_symbols((void**)pointers, entries);
			
			for (uint8_t i = 0; i < entries; i++) {
				std::string newstr = listOf[i];
				if (newstr.find("anoptamin_dbg_stacktrace") != std::string::npos) {
					std::cerr << " ***Stacktrace Function; ";
					continue;
				} else if (newstr.find("anoptamin_dbg_assertfunc") != std::string::npos) {
					std::cerr << "Assertion Print Function***\n";
					continue;
				}
				std::cerr << "  [" << (entries - i) << "] " << listOf[i] << '\n';
			}
			std::cerr << " ***End Stacktrace (" << entries << " stack frames)***\n\n";
			std::free(listOf);
		}

		//! Prints out information regarding a failed assertion, and handles closing the program. Does not use the logs.
		void LIBANOP_FUNC_COLD LIBANOP_FUNC_INPUTS_NONNULL LIBANOP_FUNC_CODEPT LIBANOP_FUNC_NO_EXIT dbg_assertfunc(const char* type, const char* func, uint32_t line, const char* file, const char* expr) {
			std::string PrintStr = type;
			PrintStr += " Assertion Failed on Line " + std::to_string(line) + ", of file '" + file + "'!\n";
			PrintStr += " Condition '";
			PrintStr += expr;
			PrintStr += "' failed in function:\n ";
			PrintStr += func;
			std::string newerr = "'";
			newerr += SDL_GetError();
			newerr += "'";
			
			std::cerr << PrintStr << '\n';
			std::cerr << "\nSystem Information:\n\tSystem ERRNO: ";
			std::cerr << std::to_string(errno)  <<  "\n\tSDL2 Error State: " << newerr << "\n\nStacktrace:\n";
			dbg_stacktrace();
			std::cerr << '\n';
			
			if (anoptamin_logopen) {
				
				Log::Log(Log::LOG_FATAL, PrintStr);
				Log::Log(Log::LOG_TRACE, "System Errno: " + std::to_string(errno));
				Log::Log(Log::LOG_TRACE, "SDL2 Error State: " + newerr );
				Log::Log(Log::LOG_COMMON, "Aborting Program!");
				anoptamin_logf.close();
			} else {
				std::cerr << "Logging Facility Not Open!\n";
			}
			
			SDL_Quit(); std::abort();
		}
		void LIBANOP_FUNC_COLD LIBANOP_FUNC_INPUTS_NONNULL LIBANOP_FUNC_CODEPT dbg_checkfunc(const char* type, const char* func, uint32_t line, const char* file, const char* expr) {
			std::string PrintStr = type;
			PrintStr += " Check Failed on Line " + std::to_string(line) + ", of file '" + file + "'!\n";
			PrintStr += " Condition '";
			PrintStr += expr;
			PrintStr += "' failed in function:\n ";
			PrintStr += func;
			std::string newerr = "'";
			newerr += SDL_GetError();
			newerr += "'";
			
			std::cerr << PrintStr << '\n';
			std::cerr << "\nSystem Information:\n\tSystem ERRNO: ";
			std::cerr << std::to_string(errno)  <<  "\n\tSDL2 Error State: " << newerr << '\n';
			
			
			if (anoptamin_logopen) {
				Log::Log(Log::LOG_ERROR, PrintStr);
				Log::Log(Log::LOG_TRACE, "System Errno: " + std::to_string(errno));
				Log::Log(Log::LOG_TRACE, "SDL2 Error State: " + newerr );
			}
		}
		/*
		// Implementation of basic hook-events
		namespace Anoptamin { namespace Base {
			//! Holds return data from a Hooked function; the 'MainData' is intended for serializing whatever is needed.
			struct c_HookReturn {
				std::vector<uint8_t> MainData;
				uint32_t ElapsedTicks;
				bool InputPtrsModifed;
			};
			
			//! Holds the pointer and some flags for a hookable function.
			//! All hookable functions must take the parameter vector size (size_t) and the input data (void*).
			//! All hookable functions must return the 'c_HookReturn' data and update its fields accordingly.
			struct c_Hookable_Func {
				bool Func_UsesThreads = 0, Func_NoInputs = 0;
				c_HookReturn (*Function)(size_t, void*);
			};
			
			//! Allows for proper functions to be registered under a hook, which then can be invoked to call its child functions.
			struct c_Function_Hook {
				std::vector<c_Hookable_Func> HookedFuncs;
				std::mutex HookLock, InvokeLock; // Only one thread can invoke the hook at a time.
				
				c_Function_Hook(const char* title, bool catchErrs = 0);
				
				//! Adds a new function to the list of hooked functions, and returns the size of the current HookedFuncs vector.
				uint16_t HookFunction(const c_Hookable_Func& function);
				
				//! Invokes the functions which are hooked to this hook, with the provided data vector, and tries to handle errors.
				template<typename T> std::vector<c_HookReturn> Invoke(std::vector<T> Data) {...};
			};
		}}
		*/
		c_Function_Hook::c_Function_Hook(const char* title, bool catchErrs) {
			Name = title;
			CatchHookedErrors = catchErrs;
		}
		c_Function_Hook::c_Function_Hook() {
			Name = "Undefined";
			CatchHookedErrors = 0;
		}
		//! Copies over the name and hook config, but none of the hooked functions.
		c_Function_Hook::c_Function_Hook(const c_Function_Hook& b) {
			Name = b.Name;
			CatchHookedErrors = b.CatchHookedErrors;
		}
		uint16_t LIBANOP_FUNC_CODEPT c_Function_Hook::HookFunction(const c_Hookable_Func& function) {
			this->HookLock.lock();
			check_ptr( function.Function != NULL );
			check_codelogic( this->HookedFuncs.size() < 600 ); // We're gonna avoid having more than 600 functions called on a hook...
			this->HookedFuncs.push_back(function);
			this->HookLock.unlock();
			return this->HookedFuncs.size();
		}
		
		
		
		c_Point3D_Integer::c_Point3D_Integer() {
			x = 0; y = 0; z = 0;
		}
		c_Point3D_Integer::c_Point3D_Integer(int32_t ix, int32_t iy, int32_t iz) {
			x = ix; y = iy; z = iz;
		}
		c_Point3D_Integer::c_Point3D_Integer(const c_Point3D_Integer& other) {
			x = other.x; y = other.y; z = other.z;
		}
		
		
		c_Point3D_Floating::c_Point3D_Floating() {
			x = 0; y = 0; z = 0;
		}
		c_Point3D_Floating::c_Point3D_Floating(double ix, double iy, double iz) {
			x = ix; y = iy; z = iz;
		}
		c_Point3D_Floating::c_Point3D_Floating(const c_Point3D_Floating& other) {
			x = other.x; y = other.y; z = other.z;
		}
		c_Point3D_Floating::c_Point3D_Floating(const c_Point3D_Integer& base) {
			x = double(base.x); y = double(base.y); z = double(base.z);
		}
	} // End Base namespace
	
	namespace Log {
		//! Sets up the session log file and gets the temporary files directory from the current directory.
		void LIBANOP_FUNC_COLD SetupFiles() {
			// The <filesystem> paths are supposed to be portable if in POSIX syntax
			
			Base::anoptamin_stclock = std::clock();
			
			try {
				Base::anoptamin_TMPpath = std::filesystem::temp_directory_path();
			} catch (...) {
				std::cerr << "OS failed to provide a temporary directory path!\n";
				std::abort();
			};
			try {
				Base::anoptamin_TMPpath /= "anoptamin";
				std::filesystem::create_directory( Base::anoptamin_TMPpath );
			} catch (...) {
				std::cerr << "OS failed to permit Anoptamin's temporary directory!\n";
				std::abort();
			};
			
			try {
				Base::anoptamin_BASEpath = std::filesystem::current_path();
			} catch (...) {
				std::cerr << "OS failed to provide the current path!\n";
				std::abort();
			};
			
			std::filesystem::path TestDir = Base::anoptamin_BASEpath;
			TestDir /= "logs";
			if (!std::filesystem::exists(TestDir)) {
				try {
					std::filesystem::create_directory("logs");
				} catch (...) {
					std::cerr << "OS failed to permit creation of logging directory!\n";
					std::abort();
				};
				TestDir = Base::anoptamin_BASEpath;
				TestDir /= "logs";
			}
			std::string tmpname = "";
			std::time_t now = std::time(NULL);
			char datestr[121]; datestr[120] = 0;
			const std::tm* otime = std::localtime( &now );
			std::strftime(datestr, 120, "%d-%b-%Y__%H-%M", otime);
			tmpname += datestr;
			tmpname += ".log";
			std::strftime(datestr, 120, "%A, %d %B %Y at %H:%M:%S", otime);
			
			TestDir /= tmpname;
			Base::anoptamin_LOGpath = std::filesystem::absolute(TestDir);
			
			Base::anoptamin_logf.open( Base::anoptamin_LOGpath.string(), std::ios::trunc );
			assert_fileio( Base::anoptamin_logf.is_open() &&Base:: anoptamin_logf.good() );
			Base::anoptamin_logopen = 1;
			Base::anoptamin_logf << "ANOPTAMIN Log Created on " << datestr << " (Start +" << Base::anoptamin_stclock << ").\n" << std::flush;
		}
		
		void LIBANOP_FUNC_COLD CleanupFiles() {
			std::filesystem::remove_all( Base::anoptamin_TMPpath );
			Base::anoptamin_logf.close();
			Base::anoptamin_logopen = 0;
		}
		
		
		void LIBANOP_FUNC_COLD LIBANOP_FUNC_NOINLINE LogTrace() {
			LogTrace_Mutex.lock();
			uint64_t* pointers[64];
			int entries = backtrace((void**)pointers, 64);
			char** listOf = backtrace_symbols((void**)pointers, entries);
			
			for (uint8_t i = 0; i < entries; i++) {
				std::string newstr = listOf[i];
				Base::anoptamin_logf << "[ TRACE  ] Frame " << (entries - i) << ": " << listOf[i] << '\n';
			}
			Base::anoptamin_logf << std::flush;
			std::free(listOf);
			LogTrace_Mutex.unlock();
		}
		
		void LIBANOP_FUNC_HOT LIBANOP_FUNC_NOINLINE Log(e_LogSeverity SEV, std::string MSG) {
			assert_runtime( Base::anoptamin_logopen );
			Log_Mutex.lock();
			std::clock_t ntime = std::clock();
			
			uint64_t timediff = ntime - Base::anoptamin_stclock;
			
			switch (SEV) {
				case LOG_TRACE:
					Base::anoptamin_logf << "[ TRACE  ] (+" << timediff << ") " << MSG << '\n' << std::flush;
					break;
				case LOG_DEBUG:
					Base::anoptamin_logf << "[ DEBUG  ] (+" << timediff << ") " << MSG << '\n' << std::flush;
					break;
				case LOG_COMMON:
					Base::anoptamin_logf << "[ COMMON ] (+" << timediff << ") " << MSG << '\n' << std::flush;
					break;
				case LOG_INFO:
					Base::anoptamin_logf << "[  INFO  ] (+" << timediff << ") " << MSG << '\n' << std::flush;
					break;
				case LOG_WARN:
					Base::anoptamin_logf << "[  WARN  ] (+" << timediff << ") " << MSG << '\n' << std::flush;
					break;
				case LOG_ERROR:
					Base::anoptamin_logf << "[ ERROR  ] (+" << timediff << ") " << MSG << '\n' << std::flush;
					break;
				case LOG_FATAL:
					Base::anoptamin_logf << "[ FATAL  ] (+" << timediff << ") " << MSG << '\n' << std::flush;
					LogTrace();
					break;
			};
			Log_Mutex.unlock();
		}
	}
} // End Anoptamin namespace
