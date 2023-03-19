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
	
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_NOINLINE LIBANOP_FUNC_FIX_STATE bool arePointsEqual_F(const Base::c_Point3D_Floating* A,
	const Base::c_Point3D_Floating* B) noexcept {
		return (A->x == B->x) and (A->y == B->y) and (A->z == B->z);
	}
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_NOINLINE LIBANOP_FUNC_FIX_STATE bool arePointsEqual_I(const Base::c_Point3D_Integer* A,
	const Base::c_Point3D_Integer* B) noexcept {
		return (A->x == B->x) and (A->y == B->y) and (A->z == B->z);
	}
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_NOINLINE LIBANOP_FUNC_FIX_STATE double getPointDist_F(const Base::c_Point3D_Floating* A,
	const Base::c_Point3D_Floating* B) noexcept {
		return std::sqrt( std::pow(A->x - B->x, 2) + std::pow(A->y - B->y, 2) + std::pow(A->z - B->z, 2) );
	}
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_NOINLINE LIBANOP_FUNC_FIX_STATE double getPointDist_I(const Base::c_Point3D_Integer* A,
	const Base::c_Point3D_Integer* B) noexcept {
		return std::sqrt( std::pow(A->x - B->x, 2) + std::pow(A->y - B->y, 2) + std::pow(A->z - B->z, 2) );
	}
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_NOINLINE LIBANOP_FUNC_FIX_STATE Base::c_Point3D_Floating getPointDiff_F(const Base::c_Point3D_Floating* A,
	const Base::c_Point3D_Floating* B) noexcept {
		Base::c_Point3D_Floating N(A->x - B->x, A->y - B->y, A->z - B->z);
		return N;
	}
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_NOINLINE LIBANOP_FUNC_FIX_STATE Base::c_Point3D_Integer getPointDiff_I(const Base::c_Point3D_Integer* A,
	const Base::c_Point3D_Integer* B) noexcept {
		Base::c_Point3D_Integer N(A->x - B->x, A->y - B->y, A->z - B->z);
		return N;
	}
		
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
	
	//Stop c_Vector3D methods
		
	//! Calculates the 'length' value and its angle.
	void c_Edge::calculateData() {
		check_runtime(this->isValid());
		this->Length = getPointDist_F(this->PointA, this->PointB);
		c_Angle TMPANG;
		Base::c_Point3D_Floating DIFF = getPointDiff_F(this->PointA, this->PointB);
		// hypotenuse == this->Length
		TMPANG.setPitch_Rad( std::acos(DIFF.x / this->Length) );
		TMPANG.setYaw_Rad( std::acos(DIFF.z / this->Length) );
		TMPANG.setRoll_Rad( std::acos(DIFF.y / this->Length) );
		this->EdgeAngle = TMPANG;
	}
	//! Ensures that the faces actually fuse at the points specified.
	bool c_Edge::isValid() const noexcept {
		// Get the point pointers ready for comparison
		const Base::c_Point3D_Floating* faceApt1 = this->FaceA->Points.A;
		const Base::c_Point3D_Floating* faceApt2 = this->FaceA->Points.B;
		const Base::c_Point3D_Floating* faceApt3 = this->FaceA->Points.C;
		
		const Base::c_Point3D_Floating* faceBpt1 = this->FaceB->Points.A;
		const Base::c_Point3D_Floating* faceBpt2 = this->FaceB->Points.B;
		const Base::c_Point3D_Floating* faceBpt3 = this->FaceB->Points.C;
		
		const Base::c_Point3D_Floating* edgePtA = this->PointA;
		const Base::c_Point3D_Floating* edgePtB = this->PointB;
		
		if (arePointsEqual_F(faceApt1, edgePtA) || arePointsEqual_F(faceApt2, edgePtA) || arePointsEqual_F(faceApt3, edgePtA) ) {
			return (arePointsEqual_F(faceBpt1, edgePtB) || arePointsEqual_F(faceBpt2, edgePtB) || arePointsEqual_F(faceBpt3, edgePtB));
		} else if (arePointsEqual_F(faceApt1, edgePtB) || arePointsEqual_F(faceApt2, edgePtB) || arePointsEqual_F(faceApt3, edgePtB) ) {
			return (arePointsEqual_F(faceBpt1, edgePtA) || arePointsEqual_F(faceBpt2, edgePtA) || arePointsEqual_F(faceBpt3, edgePtA));
		} else return false;
	}
	
	// Stop c_Edge methods
	
	// get area and center
	void c_Face_Triangle::calculateData() {
		// Centers
		double tmpx = (this->Points.A->x + this->Points.B->x + this->Points.C->x) / 3;
		double tmpy = (this->Points.A->y + this->Points.B->y + this->Points.C->y) / 3;
		double tmpz = (this->Points.A->z + this->Points.B->z + this->Points.C->z) / 3;
		this->Center = Base::c_Point3D_Floating(tmpx, tmpy, tmpz);
		// Distances
		double gooberAB = getPointDist_F(this->Points.A, this->Points.B);
		double gooberBC = getPointDist_F(this->Points.B, this->Points.C);
		double gooberCA = getPointDist_F(this->Points.C, this->Points.A);
		long double perim = 0.5 * (gooberAB + gooberBC + gooberCA);
		this->Area = std::sqrt( perim * (perim - gooberAB) * (perim - gooberBC) * (perim - gooberCA) );
	}
	
	// Stop c_Face_Triangle methods
	
	
}}; //End Anoptamin::Geometry
