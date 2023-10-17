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
	Anoptamin::Geometry::c_Vector3D translatinatorR(-2, 0, 1);
	
	Anoptamin::Geometry::c_Volume box = Anoptamin::Geometry::generateRectangle(ptA, ptB);
	std::cout << "Box info: " << box.toString() << '\n';
	std::vector<Anoptamin::Base::c_Point3D_Floating> pointsOf;
	pointsOf = box.getAllPoints();
	for (auto i : pointsOf) {
		std::cout << Anoptamin::Geometry::pointToStr_F(&i) << '\n';
	}
	
	Anoptamin::Geometry::c_Angle rotator;
	rotator.setPitch_Deg(10);
	rotator.setRoll_Deg(-35);
	rotator.setYaw_Deg(0);
	Anoptamin::Geometry::c_Angle rotator2;
	rotator2.setPitch_Deg(-10);
	rotator2.setRoll_Deg(35);
	rotator2.setYaw_Deg(0);
	
	/*
	RESULTS (pitch affects x/z, roll affects y/z, yaw affects x/y)
	It's close to the original, but it's still off...
	
	Box info: Volume SA: 16.335378, Volume Faces: 12; Volume Center: (1.055556, 0.791667, 0.500000)
	(0.000000, 0.000000, 0.000000)
	(2.000000, 0.000000, 0.000000)
	(2.000000, 1.500000, 1.000000)
	(2.000000, 0.000000, 1.000000)
	(2.000000, 1.500000, 0.000000)
	(0.000000, 0.000000, 1.000000)
	(0.000000, 1.500000, 0.000000)
	(0.000000, 1.500000, 1.000000)
	Box info: Volume SA: 16.335378, Volume Faces: 12; Volume Center: (1.055556, 0.791667, 0.500000)
	(0.102835, 0.530585, -0.507519)
	(2.072464, 0.331463, -0.223064)
	(1.898852, 0.995542, 1.443926)
	(1.898852, -0.233298, 0.583722)
	(2.072464, 1.560303, 0.637140)
	(-0.070776, -0.034176, 0.299268)
	(0.102835, 1.759425, 0.352686)
	(-0.070776, 1.194664, 1.159472)
	Box info: Volume SA: 16.335378, Volume Faces: 12; Volume Center: (1.055556, 0.791667, 0.500000)
	(-0.057614, 0.103628, -0.027627)
	(1.931489, -0.094947, 0.035923)
	(2.049922, 1.407820, 1.024691)
	(1.900581, -0.084688, 1.035392)
	(2.080830, 1.397561, 0.025221)
	(-0.088522, 0.113887, 0.971843)
	(0.091728, 1.596137, -0.038328)
	(0.060820, 1.606396, 0.961141)
	*/
	
	box.rotateSelf(rotator);
	std::cout << "Box info: " << box.toString() << '\n';
	pointsOf = box.getAllPoints();
	for (auto i : pointsOf) {
		std::cout << Anoptamin::Geometry::pointToStr_F(&i) << '\n';
	}
	box.rotateSelf(rotator2);
	std::cout << "Box info: " << box.toString() << '\n';
	pointsOf = box.getAllPoints();
	for (auto i : pointsOf) {
		std::cout << Anoptamin::Geometry::pointToStr_F(&i) << '\n';
	}
	
	return 0;
}
