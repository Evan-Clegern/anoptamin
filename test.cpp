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
}
