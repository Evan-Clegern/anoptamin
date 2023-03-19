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
	
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL LIBANOP_FUNC_FIX_STATE bool arePointsEqual_F(const Base::c_Point3D_Floating* A,
	const Base::c_Point3D_Floating* B) noexcept {
		return (A->x == B->x) and (A->y == B->y) and (A->z == B->z);
	}
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL LIBANOP_FUNC_FIX_STATE bool arePointsEqual_I(const Base::c_Point3D_Integer* A,
	const Base::c_Point3D_Integer* B) noexcept {
		return (A->x == B->x) and (A->y == B->y) and (A->z == B->z);
	}
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL LIBANOP_FUNC_FIX_STATE double getPointDist_F(const Base::c_Point3D_Floating* A,
	const Base::c_Point3D_Floating* B) noexcept {
		return std::sqrt( std::pow(A->x - B->x, 2) + std::pow(A->y - B->y, 2) + std::pow(A->z - B->z, 2) );
	}
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL LIBANOP_FUNC_FIX_STATE double getPointDist_I(const Base::c_Point3D_Integer* A,
	const Base::c_Point3D_Integer* B) noexcept {
		return std::sqrt( std::pow(A->x - B->x, 2) + std::pow(A->y - B->y, 2) + std::pow(A->z - B->z, 2) );
	}
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL LIBANOP_FUNC_FIX_STATE Base::c_Point3D_Floating getPointDiff_F(const Base::c_Point3D_Floating* A,
	const Base::c_Point3D_Floating* B) noexcept {
		Base::c_Point3D_Floating N(A->x - B->x, A->y - B->y, A->z - B->z);
		return N;
	}
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL LIBANOP_FUNC_FIX_STATE Base::c_Point3D_Integer getPointDiff_I(const Base::c_Point3D_Integer* A,
	const Base::c_Point3D_Integer* B) noexcept {
		Base::c_Point3D_Integer N(A->x - B->x, A->y - B->y, A->z - B->z);
		return N;
	}
	
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL LIBANOP_FUNC_FIX_STATE std::string pointToStr_F(const Base::c_Point3D_Floating* A) noexcept {
		std::string tmp = "(";
		tmp += std::to_string(A->x) + ", ";
		tmp += std::to_string(A->y) + ", ";
		tmp += std::to_string(A->z) + ")";
		return tmp;
	}
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL LIBANOP_FUNC_FIX_STATE std::string pointToStr_I(const Base::c_Point3D_Integer* A) noexcept {
		std::string tmp = "(";
		tmp += std::to_string(A->x) + ", ";
		tmp += std::to_string(A->y) + ", ";
		tmp += std::to_string(A->z) + ")";
		return tmp;
	}
	
	double c_Angle::getPitch_Rad() const noexcept {
		return this->Angle_AroundX * ANGStepRad;
	}
	
	double c_Angle::getPitch_Deg() const noexcept {
		return this->Angle_AroundX * ANGStepDeg;
	}
	
	double c_Angle::getYaw_Rad() const noexcept {
		return this->Angle_AroundZ * ANGStepRad;
	}
	
	double c_Angle::getYaw_Deg() const noexcept {
		return this->Angle_AroundZ * ANGStepDeg;
	}
	
	double c_Angle::getRoll_Rad() const noexcept {
		return this->Angle_AroundZ * ANGStepRad;
	}
	
	double c_Angle::getRoll_Deg() const noexcept {
		return this->Angle_AroundY * ANGStepDeg;
	}
	
	
	void c_Angle::setPitch_Rad(double Radians) noexcept {
		// Normalize
		while (Radians >= (2 * PI)) Radians -= (2 * PI);
		if (Radians == 0) {
			this->Angle_AroundX = 0;
		} else {
			this->Angle_AroundX = int16_t(Radians / ANGStepRad);
		}
	}
	
	void c_Angle::setPitch_Deg(double Degrees) noexcept {
		// Normalize
		while (Degrees >= 360) Degrees -= 360;
		if (Degrees == 0) {
			this->Angle_AroundX = 0;
		} else {
			this->Angle_AroundX = int16_t(Degrees / ANGStepDeg);
		}
	}
	
	void c_Angle::setYaw_Rad(double Radians) noexcept {
		// Normalize
		while (Radians >= (2 * PI)) Radians -= (2 * PI);
		if (Radians == 0) {
			this->Angle_AroundZ = 0;
		} else {
			this->Angle_AroundZ = int16_t(Radians / ANGStepRad);
		}
	}
	
	void c_Angle::setYaw_Deg(double Degrees) noexcept {
		// Normalize
		while (Degrees >= 360) Degrees -= 360;
		if (Degrees == 0) {
			this->Angle_AroundZ = 0;
		} else {
			this->Angle_AroundZ = int16_t(Degrees / ANGStepDeg);
		}
	}
	
	void c_Angle::setRoll_Rad(double Radians) noexcept {
		// Normalize
		while (Radians >= (2 * PI)) Radians -= (2 * PI);
		if (Radians == 0) {
			this->Angle_AroundY = 0;
		} else {
			this->Angle_AroundY = int16_t(Radians / ANGStepRad);
		}
	}
	
	void c_Angle::setRoll_Deg(double Degrees) noexcept {
		// Normalize
		while (Degrees >= 360) Degrees -= 360;
		if (Degrees == 0) {
			this->Angle_AroundY = 0;
		} else {
			this->Angle_AroundY = int16_t(Degrees / ANGStepDeg);
		}
	}
	std::string c_Angle::toString(bool degrees) const noexcept {
		std::string tmp = "(";
		if (degrees) {
			tmp += std::to_string(this->getPitch_Deg()) + "°, ";
			tmp += std::to_string(this->getYaw_Deg()) + "°, ";
			tmp += std::to_string(this->getRoll_Deg()) + "°)";
		} else {
			tmp += std::to_string(this->getPitch_Rad()) + "R, ";
			tmp += std::to_string(this->getYaw_Rad()) + "R, ";
			tmp += std::to_string(this->getRoll_Rad()) + "R)";
		}
		return tmp;
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

	std::string c_Vector3D::toString() const noexcept {
		std::string tmpx = "(";
		tmpx += std::to_string(this->ValX) + ", ";
		tmpx += std::to_string(this->ValY) + ", ";
		tmpx += std::to_string(this->ValZ) + " : ";
		tmpx += std::to_string(this->Magnitude) + "u)";
		return tmpx;
	}
	
	//Stop c_Vector3D methods
		
	//! Calculates the 'length' value and its angle.
	c_Edge::c_Edge() {
		PointA = NULL; PointB = NULL;
	}
	LIBANOP_FUNC_INPUTS_NONNULL c_Edge::c_Edge(const Base::c_Point3D_Floating* from, const Base::c_Point3D_Floating* to) {
		PointA = from; PointB = to;
		calculateData();
	}
	c_Edge::c_Edge(const c_Edge& b) {
		check_ptr(b.PointA != NULL);
		check_ptr(b.PointB != NULL);
		check_ptr(b.PointA != b.PointB);
		PointA = b.PointA;
		PointB = b.PointB;
	}
	void c_Edge::calculateData() {
		check_ptr(this->PointA != NULL);
		check_ptr(this->PointB != NULL);
		check_ptr(this->PointA != this->PointB);
		this->Length = getPointDist_F(this->PointA, this->PointB);
		c_Angle TMPANG;
		Base::c_Point3D_Floating DIFF = getPointDiff_F(this->PointA, this->PointB);
		// hypotenuse == this->Length
		TMPANG.setPitch_Rad( std::acos(DIFF.x / this->Length) );
		TMPANG.setYaw_Rad( std::acos(DIFF.z / this->Length) );
		TMPANG.setRoll_Rad( std::acos(DIFF.y / this->Length) );
		this->EdgeAngle = TMPANG;
	}
	//! Calculate a vector to represent the edge from PointA to PointB.
	c_Vector3D c_Edge::calculateAsVector() const {
		check_ptr(this->PointA != NULL);
		check_ptr(this->PointB != NULL);
		check_ptr(this->PointA != this->PointB);
		
		Base::c_Point3D_Floating DIFF = getPointDiff_F(this->PointA, this->PointB);
		
		c_Vector3D nyehehe(DIFF.x, DIFF.y, DIFF.z);
		return nyehehe;
	}
	std::string c_Edge::toString() const {
		check_ptr(this->PointA != NULL);
		check_ptr(this->PointB != NULL);
		check_ptr(this->PointA != this->PointB);
		//→
		std::string tmp = "{";
		tmp += pointToStr_F(this->PointA) + " → " + pointToStr_F(this->PointB) + ", ";
		tmp += std::to_string(this->Length) + "u}";
		return tmp;
	}
	
	
	// get area and center
	c_Face_Triangle::c_Face_Triangle() {
		Points.A.x = 0;
		Points.A.y = 0;
		Points.A.z = 0;
		
		Points.B.x = 0;
		Points.B.y = 0;
		Points.B.z = 0;
		
		Points.C.x = 0;
		Points.C.y = 0;
		Points.C.z = 0;
	}
	c_Face_Triangle::c_Face_Triangle(Base::c_Point3D_Floating A, Base::c_Point3D_Floating B, Base::c_Point3D_Floating C) {
		Points.A = A;
		Points.B = B;
		Points.C = C;
		
		c_Edge NA(&Points.A, &Points.B);
		c_Edge NB(&Points.B, &Points.C);
		c_Edge NC(&Points.C, &Points.A);
		EdgeA = NA;
		EdgeB = NB;
		EdgeC = NC;
		
		calculateData();
	}
	void c_Face_Triangle::calculateData() {
		this->EdgeA.calculateData();
		this->EdgeB.calculateData();
		this->EdgeC.calculateData();
		
		// Centers
		double tmpx = (this->Points.A.x + this->Points.B.x + this->Points.C.x) / 3;
		double tmpy = (this->Points.A.y + this->Points.B.y + this->Points.C.y) / 3;
		double tmpz = (this->Points.A.z + this->Points.B.z + this->Points.C.z) / 3;
		this->Center = Base::c_Point3D_Floating(tmpx, tmpy, tmpz);
		// Distances
		double gooberAB = this->EdgeA.Length;
		double gooberBC = this->EdgeB.Length;
		double gooberCA = this->EdgeC.Length;
		long double perim = 0.5 * (gooberAB + gooberBC + gooberCA);
		this->Area = std::sqrt( perim * (perim - gooberAB) * (perim - gooberBC) * (perim - gooberCA) );
	}
	//! Returns a String representation.
	std::string c_Face_Triangle::toString() const {
		std::string tmp = "Tri: " + pointToStr_F(&(this->Points.A)) + "; " + pointToStr_F(&(this->Points.B)) + "; " + pointToStr_F(&(this->Points.C));
		tmp += "\nArea: " + std::to_string(this->Area) + "u², Center: " + pointToStr_F(&(this->Center));
		return tmp;
	}
	
	
}}; //End Anoptamin::Geometry
