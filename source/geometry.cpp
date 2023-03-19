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
		if (Radians == 0) {
			this->Angle_AroundX = 0;
		} else {
			this->Angle_AroundX = int16_t(Radians / ANGStepRad);
		}
	}
	//! Sets the 'X' angle to a value which is expressed as degrees: X = 32767(VAL) / 360
	void c_Angle::setPitch_Deg(double Degrees) noexcept {
		// Normalize
		while (Degrees >= 360) Degrees -= 360;
		if (Degrees == 0) {
			this->Angle_AroundX = 0;
		} else {
			this->Angle_AroundX = int16_t(Degrees / ANGStepDeg);
		}
	}
	//! Sets the 'Z' angle to a value which is a direct multiple of Pi: Z = 32767(VAL) / (2 PI)
	void c_Angle::setYaw_Rad(double Radians) noexcept {
		// Normalize
		while (Radians >= (2 * PI)) Radians -= (2 * PI);
		if (Radians == 0) {
			this->Angle_AroundZ = 0;
		} else {
			this->Angle_AroundZ = int16_t(Radians / ANGStepRad);
		}
	}
	//! Sets the 'Z' angle to a value which is expressed as degrees: Z = 32767(VAL) / 360
	void c_Angle::setYaw_Deg(double Degrees) noexcept {
		// Normalize
		while (Degrees >= 360) Degrees -= 360;
		if (Degrees == 0) {
			this->Angle_AroundZ = 0;
		} else {
			this->Angle_AroundZ = int16_t(Degrees / ANGStepDeg);
		}
	}
	//! Sets the 'Y' angle to a value which is a direct multiple of Pi: Y = 32767(VAL) / (2 PI)
	void c_Angle::setRoll_Rad(double Radians) noexcept {
		// Normalize
		while (Radians >= (2 * PI)) Radians -= (2 * PI);
		if (Radians == 0) {
			this->Angle_AroundY = 0;
		} else {
			this->Angle_AroundY = int16_t(Radians / ANGStepRad);
		}
	}
	//! Sets the 'Y' angle to a value which is expressed as degrees: Y = 32767(VAL) / 360
	void c_Angle::setRoll_Deg(double Degrees) noexcept {
		// Normalize
		while (Degrees >= 360) Degrees -= 360;
		if (Degrees == 0) {
			this->Angle_AroundY = 0;
		} else {
			this->Angle_AroundY = int16_t(Degrees / ANGStepDeg);
		}
	}
	
	// Stop c_Angle methods
	
	c_Vector3D::c_Vector3D(double X, double Y, double Z) {
		ValX = X; ValY = Y; ValZ = Z;
		calculateMagnitude();
	}
	c_Vector3D::c_Vector3D() {
		ValX = 0, ValY = 0, ValZ = 0, Magnitude = 0;
	}
	c_Vector3D::c_Vector3D(const c_Vector3D& b) {
		ValX = b.ValX; ValY = b.ValY; ValZ = b.ValZ;
		calculateMagnitude();
	}
	
	void c_Vector3D::calculateMagnitude() noexcept {
		this->Magnitude = std::sqrt( (this->ValX * this->ValX) + (this->ValY * this->ValY) + (this->ValZ * this->ValZ) );
	}
	// the square of ValX, ValY and ValZ must add up to 1
	void c_Vector3D::normalize() noexcept {
		this->calculateMagnitude();
		this->ValX = (this->ValX / this->Magnitude);
		this->ValY = (this->ValY / this->Magnitude);
		this->ValZ = (this->ValZ / this->Magnitude);
	}
	//! Gets the angle at which the vector is pointed from the base point.
	
	// They're all ARCTAN because the vector's magnitude is the hypotenuse of any given right triangle.
	// Radians are the default value in CMATH
	c_Angle c_Vector3D::getAngles() const {
		c_Angle TMP;
		// About the 'x' axis (Y / Z)
		TMP.setPitch_Rad( std::atan( this->ValY	/ this->ValZ ) );
		// About the 'z' axis (X / Y)
		TMP.setYaw_Rad( std::atan( this->ValX / this->ValY ) );
		// About the 'y' axis (X / Z)
		TMP.setRoll_Rad( std::atan( this->ValX / this->ValZ ) );
		
		return TMP;
	}
	
}}; //End Anoptamin::Geometry
