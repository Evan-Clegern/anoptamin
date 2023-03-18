/********!
 * @file  geometry.cpp
 * 
 * @author
 * 	Evan Clegern <evanclegern.work@gmail.com>
 * 
 * @date
 * 	16 March 2023
 * 
 * @brief
 * 	Backend code for 'include/geometry.hpp'
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


#include "../include/geometry.hpp"


namespace Anoptamin { namespace Geometry {
	
	//! Return the angle as a value of (Angle_AroundX * (2 PI / 32767))
	double c_Angle::getPitch_Rad() const noexcept {
		return this->Angle_AroundX * ANGStepRad;
	}
	//! Return the angle as a value of (Angle_AroundX * (360 / 32767))
	double c_Angle::getPitch_Deg() const noexcept {
		return this->Angle_AroundX * ANGStepDeg;
	}
	//! Return the angle as a value of (Angle_AroundZ * (2 PI / 32767))
	double c_Angle::getYaw_Rad() const noexcept {
		return this->Angle_AroundZ * ANGStepRad;
	}
	//! Return the angle as a value of (Angle_AroundZ * (360 / 32767))
	double c_Angle::getYaw_Deg() const noexcept {
		return this->Angle_AroundZ * ANGStepDeg;
	}
	//! Return the angle as a value of (Angle_AroundY * (2 PI / 32767))
	double c_Angle::getRoll_Rad() const noexcept {
		return this->Angle_AroundZ * ANGStepRad;
	}
	//! Return the angle as a value of (Angle_AroundY * (360 / 32767))
	double c_Angle::getRoll_Deg() const noexcept {
		return this->Angle_AroundY * ANGStepDeg;
	}
	
	//! Sets the 'X' angle to a value which is a direct multiple of Pi: X = 32767(VAL) / (2 PI)
	void c_Angle::setPitch_Rad(double Radians) noexcept {
		// Normalize
		while (Radians >= (2 * PI)) Radians -= (2 * PI);
		this->Angle_AroundX = int16_t(Radians / ANGStepRad);
	}
	//! Sets the 'X' angle to a value which is expressed as degrees: X = 32767(VAL) / 360
	void c_Angle::setPitch_Deg(double Degrees) noexcept {
		// Normalize
		while (Degrees >= 360) Degrees -= 360;
		this->Angle_AroundX = int16_t(Degrees / ANGStepDeg);
	}
	//! Sets the 'Z' angle to a value which is a direct multiple of Pi: Z = 32767(VAL) / (2 PI)
	void c_Angle::setYaw_Rad(double Radians) noexcept {
		// Normalize
		while (Radians >= (2 * PI)) Radians -= (2 * PI);
		this->Angle_AroundZ = int16_t(Radians / ANGStepRad);
	}
	//! Sets the 'Z' angle to a value which is expressed as degrees: Z = 32767(VAL) / 360
	void c_Angle::setYaw_Deg(double Degrees) noexcept {
		// Normalize
		while (Degrees >= 360) Degrees -= 360;
		this->Angle_AroundZ = int16_t(Degrees / ANGStepDeg);
	}
	//! Sets the 'Y' angle to a value which is a direct multiple of Pi: Y = 32767(VAL) / (2 PI)
	void c_Angle::setRoll_Rad(double Radians) noexcept {
		// Normalize
		while (Radians >= (2 * PI)) Radians -= (2 * PI);
		this->Angle_AroundY = int16_t(Radians / ANGStepRad);
	}
	//! Sets the 'Y' angle to a value which is expressed as degrees: Y = 32767(VAL) / 360
	void c_Angle::setRoll_Deg(double Degrees) noexcept {
		// Normalize
		while (Degrees >= 360) Degrees -= 360;
		this->Angle_AroundY = int16_t(Degrees / ANGStepDeg);
	}
	
	// Stop c_Angle methods
	
}}; //End Anoptamin::Geometry
