#include "include/base.hpp"
#include "include/sdl.hpp"
#include "include/glact.hpp"
#include "include/geometry.hpp"

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
	Anoptamin::Base::c_Point3D_Floating ptA(0, 0, 0);
	Anoptamin::Base::c_Point3D_Floating ptB(2, 1.5, 1);
	
	Anoptamin::Geometry::c_Vector3D translatinator(2, 0, -1);
	
	Anoptamin::Geometry::c_Volume box = Anoptamin::Geometry::generateRectangle(ptA, ptB);
	std::cout << "Box info: " << box.toString() << '\n';
	std::vector<Anoptamin::Base::c_Point3D_Floating> pointsOf;
	pointsOf = box.getAllPoints();
	for (auto i : pointsOf) {
		std::cout << Anoptamin::Geometry::pointToStr_F(&i) << '\n';
	}
	
	box.translateSelf(translatinator);
	
	std::cout << "Box info: " << box.toString() << '\n';
	pointsOf = box.getAllPoints();
	for (auto i : pointsOf) {
		std::cout << Anoptamin::Geometry::pointToStr_F(&i) << '\n';
	}
	
	box.scaleSelf(2.0);
	std::cout << "Box info: " << box.toString() << '\n';
	pointsOf = box.getAllPoints();
	for (auto i : pointsOf) {
		std::cout << Anoptamin::Geometry::pointToStr_F(&i) << '\n';
	}
	
	box.scaleSelf(0.5);
	std::cout << "Box info: " << box.toString() << '\n';
	pointsOf = box.getAllPoints();
	for (auto i : pointsOf) {
		std::cout << Anoptamin::Geometry::pointToStr_F(&i) << '\n';
	}
	
	Anoptamin::Geometry::c_Matrix superMatrix1(3, 2, { {1.0, 2.0}, {2.0, 1.0}, {0.5, 0.5} });
	Anoptamin::Geometry::c_Matrix superMatrix2(2, 3, { {3.5, 1.0, 0.5}, {1.5, 1.0, 0.5} });
	
	auto X = superMatrix2.dotProduct(superMatrix1);
	std::cout << X.toString() << '\n';
	X = superMatrix1.dotProduct(superMatrix2);
	std::cout << X.toString() << '\n';
	
	// Just to prevent unneeded delay when testing geometry; move the graphics to an unreachable point for the time being
	return 0;
	
	Anoptamin::Log::SetupFiles();
	
	Anoptamin::initializeSDLGraphics();
	
	
	BobWindow = new Anoptamin::Base::c_SDLWindow(605, 300,
		"Test Window for The Doom Test", false, Anoptamin::Base::TYPE_GENERIC, true, true, false);
	Anoptamin_LogCommon("Window Created.");
	
	BobWindow->addHook_KeyboardEvent(exitWindowOnEsc_F);
	
	Anoptamin::Graphics::c_Window_Renderer autorender( BobWindow->getRawSDLWindow() );
	assert_runtime( Anoptamin::Graphics::initializeGL() );
	
	Anoptamin::Graphics::c_RenderEngine_Low mainrenderer(autorender);
	mainrenderer.registerShader_Vertex( "#version 140\nin vec3 LVertexPos3D1; void main() { gl_Position = vec4( LVertexPos3D1.x, LVertexPos3D1.y, LVertexPos3D1.z, 1 ); }" );
	mainrenderer.registerShader_Fragment("#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }");
	mainrenderer.compileWithShaders();
	assert_runtime( mainrenderer.renderEngineGood() );
	
	bool isclosed = 0;
	
	uint64_t sum_avg = 0;
	
	float vertexes1[] = {
		0.5, 0.5, 1.0,
		0.5, -0.5, 1.0,
		-0.85, -0.35, -1.0,
		-1.0, -0.4, -0.8,
		-0.5, 0.5, -1.0
	};
	uint32_t indexes[] = {
		0, 1, 2, 3, 4
	};
	
	mainrenderer.loadDataVBO(sizeof(float) * 3 * 5, vertexes1, true);
	mainrenderer.loadDataIBO(sizeof(uint32_t) * 5, indexes, true);
	int attrib3d = mainrenderer.getAttributeLocation("LVertexPos3D1");
	
	uint64_t msst = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
	uint16_t i = 0;
	for (; i < 1500; i++) {
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
		mainrenderer.bindAndDraw(attrib3d, 3, 5); // 3D points; 5 of them in total.
		
		mainrenderer.unbindRenderer();
	}
	uint64_t msed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
	std::cout << "The average event polling time was: " << (sum_avg / double(i)) << " us, and the total time elapsed was: " << (msed - msst) << "ms.\n";
	
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
