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
	
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL bool arePointsEqual_F(const Base::c_Point3D_Floating* A,
	const Base::c_Point3D_Floating* B) noexcept {
		return (A->x == B->x) and (A->y == B->y) and (A->z == B->z);
	}
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL bool arePointsEqual_I(const Base::c_Point3D_Integer* A,
	const Base::c_Point3D_Integer* B) noexcept {
		return (A->x == B->x) and (A->y == B->y) and (A->z == B->z);
	}
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL double getPointDist_F(const Base::c_Point3D_Floating* A,
	const Base::c_Point3D_Floating* B) noexcept {
		return std::sqrt( std::pow(A->x - B->x, 2) + std::pow(A->y - B->y, 2) + std::pow(A->z - B->z, 2) );
	}
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL double getPointDist_I(const Base::c_Point3D_Integer* A,
	const Base::c_Point3D_Integer* B) noexcept {
		return std::sqrt( std::pow(A->x - B->x, 2) + std::pow(A->y - B->y, 2) + std::pow(A->z - B->z, 2) );
	}
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL Base::c_Point3D_Floating getPointDiff_F(const Base::c_Point3D_Floating* A,
	const Base::c_Point3D_Floating* B) noexcept {
		Base::c_Point3D_Floating N(A->x - B->x, A->y - B->y, A->z - B->z);
		return N;
	}
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL Base::c_Point3D_Integer getPointDiff_I(const Base::c_Point3D_Integer* A,
	const Base::c_Point3D_Integer* B) noexcept {
		Base::c_Point3D_Integer N(A->x - B->x, A->y - B->y, A->z - B->z);
		return N;
	}
	
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL std::string pointToStr_F(const Base::c_Point3D_Floating* A) noexcept {
		std::string tmp = "(";
		tmp += std::to_string(A->x) + ", ";
		tmp += std::to_string(A->y) + ", ";
		tmp += std::to_string(A->z) + ")";
		return tmp;
	}
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL std::string pointToStr_I(const Base::c_Point3D_Integer* A) noexcept {
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

	c_Vector3D c_Vector3D::operator*(double scalar) const noexcept {
		c_Vector3D TMP(*this);
		TMP.ValX *= scalar;
		TMP.ValY *= scalar;
		TMP.ValZ *= scalar;
		TMP.calculateMagnitude();
		return TMP;
	}
	c_Vector3D c_Vector3D::operator*(const c_Vector3D& vector2) const noexcept {
		c_Vector3D TMP(*this);
		TMP.ValX *= vector2.ValX;
		TMP.ValY *= vector2.ValY;
		TMP.ValZ *= vector2.ValZ;
		TMP.calculateMagnitude();
		return TMP;
	}
	c_Vector3D c_Vector3D::operator+(const c_Vector3D& vector2) const noexcept {
		c_Vector3D TMP(*this);
		TMP.ValX += vector2.ValX;
		TMP.ValY += vector2.ValY;
		TMP.ValZ += vector2.ValZ;
		TMP.calculateMagnitude();
		return TMP;
	}
	c_Vector3D c_Vector3D::operator-(const c_Vector3D& vector2) const noexcept {
		c_Vector3D TMP(*this);
		TMP.ValX -= vector2.ValX;
		TMP.ValY -= vector2.ValY;
		TMP.ValZ -= vector2.ValZ;
		TMP.calculateMagnitude();
		return TMP;
	}
	//Stop c_Vector3D methods
	
namespace PtTransforms {
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL Base::c_Point3D_Floating translateBy_F(const Base::c_Point3D_Floating* main,
	const c_Vector3D* level) noexcept {
		Base::c_Point3D_Floating NEWPT(*main);
		NEWPT.x += level->ValX;
		NEWPT.y += level->ValY;
		NEWPT.z += level->ValZ;
		return NEWPT;
	}
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL Base::c_Point3D_Integer translateBy_I(const Base::c_Point3D_Integer* main,
	const c_Vector3D* level) noexcept {
		Base::c_Point3D_Integer NEWPT(*main);
		NEWPT.x += int32_t(level->ValX);
		NEWPT.y += int32_t(level->ValY);
		NEWPT.z += int32_t(level->ValZ);
		return NEWPT;
	}
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL Base::c_Point3D_Floating scaleBy_F(const Base::c_Point3D_Floating* main,
	const c_Vector3D* level) noexcept {
		Base::c_Point3D_Floating NEWPT(*main);
		NEWPT.x *= level->ValX;
		NEWPT.y *= level->ValY;
		NEWPT.z *= level->ValZ;
		return NEWPT;
	}
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL Base::c_Point3D_Integer scaleBy_I(const Base::c_Point3D_Integer* main,
	const c_Vector3D* level) noexcept {
		Base::c_Point3D_Integer NEWPT(*main);
		NEWPT.x *= int32_t(level->ValX);
		NEWPT.y *= int32_t(level->ValY);
		NEWPT.z *= int32_t(level->ValZ);
		return NEWPT;
	}
	
	//! Rotates any arbitrary point about a second point using matrices.
	LIBANOP_FUNC_CODEPT LIBANOP_FUNC_HOT std::vector<long double> getRotationVector(const c_Angle& by) {
		// 'A' vector: 1x3
		// 'B' vector: 3x3
		// Output: 1x3 (new point)

		// Manually create the matrix
		// for Wikipedia info: alpha == yaw, beta == pitch, gamma == roll
		long double R0C0 = std::cos(by.getPitch_Rad()) * std::cos(by.getRoll_Rad());
		long double R0C1 = (std::sin(by.getYaw_Rad()) * std::sin(by.getPitch_Rad()) * std::cos(by.getRoll_Rad())) - (std::cos(by.getYaw_Rad()) * std::sin(by.getRoll_Rad()));
		long double R0C2 = (std::cos(by.getYaw_Rad()) * std::sin(by.getPitch_Rad()) * std::cos(by.getRoll_Rad())) + (std::sin(by.getYaw_Rad()) * std::sin(by.getRoll_Rad()));
		
		long double R1C0 = std::cos(by.getPitch_Rad()) * std::sin(by.getRoll_Rad());
		long double R1C1 = (std::sin(by.getYaw_Rad()) * std::sin(by.getPitch_Rad()) * std::cos(by.getRoll_Rad())) + (std::cos(by.getYaw_Rad()) * std::cos(by.getRoll_Rad()));
		long double R1C2 = (std::cos(by.getYaw_Rad()) * std::sin(by.getPitch_Rad()) * std::sin(by.getRoll_Rad())) - (std::sin(by.getYaw_Rad()) * std::cos(by.getRoll_Rad()));
		
		long double R2C0 = -1 * std::sin(by.getPitch_Rad());
		long double R2C1 = std::sin(by.getYaw_Rad()) * std::cos(by.getPitch_Rad());
		long double R2C2 = std::cos(by.getYaw_Rad()) * std::cos(by.getPitch_Rad());
		
		std::vector<long double> N = {R0C0, R0C1, R0C2,  R1C0, R1C1, R1C2,  R2C0, R2C1, R2C2};
		return N;
	}
	LIBANOP_FUNC_CODEPT LIBANOP_FUNC_HOT Base::c_Point3D_Floating rotateByVector(const std::vector<long double> &vector, Base::c_Point3D_Floating main,
	const Base::c_Point3D_Floating& about) {
		Base::c_Point3D_Floating offset = getPointDiff_F(&main, &about);
		double nX = (main.x * vector[0]) + (main.y * vector[3]) + (main.z * vector[6]) + offset.x;
		double nY = (main.x * vector[1]) + (main.y * vector[4]) + (main.z * vector[7]) + offset.y;
		double nZ = (main.x * vector[2]) + (main.y * vector[5]) + (main.z * vector[8]) + offset.z;
		return Base::c_Point3D_Floating(nX, nY, nZ);
	}
} // End Anoptamin::Geometry::Transforms
		
		
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
	c_Face_Triangle::c_Face_Triangle(const c_Face_Triangle& b) {

		Points.A = b.Points.A;
		Points.B = b.Points.B;
		Points.C = b.Points.C;
		
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
		tmp += " - Area: " + std::to_string(this->Area) + "u², Center: " + pointToStr_F(&(this->Center));
		return tmp;
	}
	
	// End c_Face_Triangle methods
	
	void c_Volume::calculateData() {
		this->SurfaceArea = 0;
		// Get the center by finding the average of all of the triangular faces' centers.
		Base::c_Point3D_Floating TMP(0, 0, 0);
		for (c_Face_Triangle i : this->Faces) {
			TMP.x += i.Center.x;
			TMP.y += i.Center.y;
			TMP.z += i.Center.z;
			
			this->SurfaceArea += i.Area;
		}
		Base::c_Point3D_Floating NTMP;
		NTMP.x = (TMP.x / this->Faces.size());
		NTMP.y = (TMP.y / this->Faces.size());
		NTMP.z = (TMP.z / this->Faces.size());
		this->Center = NTMP;
	}
	
	// header-only, test if the point is in vector
	bool isPtInVec(Base::c_Point3D_Floating* point, std::vector<Base::c_Point3D_Floating>& vector) {
		for (auto i : vector) {
			if (i.x == point->x) {
				bool N = (i.y == point->y) and (i.z == point->z);
				if (N) return true; else continue;
			}
		}
		return false;
	}
	// header-only, test if the point is in vector
	bool isPtInVec(Base::c_Point3D_Floating point, std::vector<Base::c_Point3D_Floating>& vector) {
		for (auto i : vector) {
			if (i.x == point.x) {
				bool N = (i.y == point.y) and (i.z == point.z);
				if (N) return true; else continue;
			}
		}
		return false;
	}
	
	//! Updates the pointer list, and removes redundant point pointers
	void c_Volume::updatePointers() {
		std::vector<Base::c_Point3D_Floating> actualPoints; // duplicates of those in the face data. used to trim redundant pointers.
		this->MainPoints.clear();
		for (c_Face_Triangle i : this->Faces) {
			
			if (!isPtInVec(i.Points.A, actualPoints)) {
				actualPoints.push_back(i.Points.A);
				this->MainPoints.push_back(&i.Points.A);
			}
			if (!isPtInVec(i.Points.B, actualPoints)) {
				actualPoints.push_back(i.Points.B);
				this->MainPoints.push_back(&i.Points.B);
			}
			if (!isPtInVec(i.Points.C, actualPoints)) {
				actualPoints.push_back(i.Points.C);
				this->MainPoints.push_back(&i.Points.C);
			}
		}
	}
	std::string c_Volume::toString() const {
		std::string TMP = "Volume SA: " + std::to_string(this->SurfaceArea) + ", Volume Faces: " + std::to_string(this->Faces.size());
		TMP += "; Volume Center: " + pointToStr_F(&(this->Center));
		return TMP;
	}
	
	
	// simplest operation
	//! Move the object by the amount specified in the vector.
	void c_Volume::translateSelf(c_Vector3D translateBy) {
		c_Vector3D nvec = translateBy;
		for (c_Face_Triangle i : this->Faces) {
			auto na = PtTransforms::translateBy_F(&i.Points.A, &nvec);
			i.Points.A = na;
			na = PtTransforms::translateBy_F(&i.Points.B, &nvec);
			i.Points.B = na;
			na = PtTransforms::translateBy_F(&i.Points.C, &nvec);
			i.Points.C = na;
		}
		this->updatePointers();
		this->calculateData();
	}
	
	// we have to increase the distance of each point from the center
	//! Scale the object's points by the amount specified in the vector.
	void c_Volume::scaleSelf(c_Vector3D scaleBy) {
		for (c_Face_Triangle i : this->Faces) {
			// we can try to do the reverse of normalizing a vector
			if (i.Points.A.x > i.Center.x) {
				i.Points.A.x *= scaleBy.ValX;
			} else {
				i.Points.A.x *= -1 * scaleBy.ValX;
			}
			if (i.Points.A.y > i.Center.y) {
				i.Points.A.y *= scaleBy.ValY;
			} else {
				i.Points.A.y *= -1 * scaleBy.ValY;
			}
			if (i.Points.A.z > i.Center.z) {
				i.Points.A.z *= scaleBy.ValZ;
			} else {
				i.Points.A.z *= -1 * scaleBy.ValZ;
			}
			
			if (i.Points.B.x > i.Center.x) {
				i.Points.B.x *= scaleBy.ValX;
			} else {
				i.Points.B.x *= -1 * scaleBy.ValX;
			}
			if (i.Points.B.y > i.Center.y) {
				i.Points.B.y *= scaleBy.ValY;
			} else {
				i.Points.B.y *= -1 * scaleBy.ValY;
			}
			if (i.Points.B.z > i.Center.z) {
				i.Points.B.z *= scaleBy.ValZ;
			} else {
				i.Points.B.z *= -1 * scaleBy.ValZ;
			}
			
			if (i.Points.C.x > i.Center.x) {
				i.Points.C.x *= scaleBy.ValX;
			} else {
				i.Points.C.x *= -1 * scaleBy.ValX;
			}
			if (i.Points.C.y > i.Center.y) {
				i.Points.C.y *= scaleBy.ValY;
			} else {
				i.Points.C.y *= -1 * scaleBy.ValY;
			}
			if (i.Points.C.z > i.Center.z) {
				i.Points.C.z *= scaleBy.ValZ;
			} else {
				i.Points.C.z *= -1 * scaleBy.ValZ;
			}
		}
		this->updatePointers();
		this->calculateData();
	}
	void c_Volume::scaleSelf(float scaleBy) {
		for (c_Face_Triangle i : this->Faces) {
			// we can try to do the reverse of normalizing a vector
			if (i.Points.A.x > i.Center.x) {
				i.Points.A.x *= scaleBy;
			} else {
				i.Points.A.x *= -1 * scaleBy;
			}
			if (i.Points.A.y > i.Center.y) {
				i.Points.A.y *= scaleBy;
			} else {
				i.Points.A.y *= -1 * scaleBy;
			}
			if (i.Points.A.z > i.Center.z) {
				i.Points.A.z *= scaleBy;
			} else {
				i.Points.A.z *= -1 * scaleBy;
			}
			
			if (i.Points.B.x > i.Center.x) {
				i.Points.B.x *= scaleBy;
			} else {
				i.Points.B.x *= -1 * scaleBy;
			}
			if (i.Points.B.y > i.Center.y) {
				i.Points.B.y *= scaleBy;
			} else {
				i.Points.B.y *= -1 * scaleBy;
			}
			if (i.Points.B.z > i.Center.z) {
				i.Points.B.z *= scaleBy;
			} else {
				i.Points.B.z *= -1 * scaleBy;
			}
			
			if (i.Points.C.x > i.Center.x) {
				i.Points.C.x *= scaleBy;
			} else {
				i.Points.C.x *= -1 * scaleBy;
			}
			if (i.Points.C.y > i.Center.y) {
				i.Points.C.y *= scaleBy;
			} else {
				i.Points.C.y *= -1 * scaleBy;
			}
			if (i.Points.C.z > i.Center.z) {
				i.Points.C.z *= scaleBy;
			} else {
				i.Points.C.z *= -1 * scaleBy;
			}
		}
		this->updatePointers();
		this->calculateData();
	}
	// rotation time baby
	//! Rotate the object by the various angles specified
	void c_Volume::rotateSelf(c_Angle rotateBy) {
		auto rotvec = PtTransforms::getRotationVector(rotateBy);
		for (c_Face_Triangle i : this->Faces) {
			i.Points.A = PtTransforms::rotateByVector(rotvec, i.Points.A, this->Center);
			i.Points.B = PtTransforms::rotateByVector(rotvec, i.Points.B, this->Center);
			i.Points.C = PtTransforms::rotateByVector(rotvec, i.Points.C, this->Center);
		}
		this->updatePointers();
		this->calculateData();
	}
	//! Rotate the object by the various angles specified, about the position specified.
	void c_Volume::rotateSelf_About(c_Angle rotateBy, Base::c_Point3D_Integer about) {
		auto rotvec = PtTransforms::getRotationVector(rotateBy);
		for (c_Face_Triangle i : this->Faces) {
			i.Points.A = PtTransforms::rotateByVector(rotvec, i.Points.A, about);
			i.Points.B = PtTransforms::rotateByVector(rotvec, i.Points.B, about);
			i.Points.C = PtTransforms::rotateByVector(rotvec, i.Points.C, about);
		}
		this->updatePointers();
		this->calculateData();
	}
	
	// End c_Volume methods
	
	//! Generates a rectangular volume between the specified points
	LIBANOP_FUNC_CODEPT LIBANOP_FUNC_HOT c_Volume generateRectangle(Base::c_Point3D_Floating lowestBound, Base::c_Point3D_Floating highestBound) {
		// gets the dimensions
		Base::c_Point3D_Floating DIFF = getPointDiff_F(&highestBound, &lowestBound);
		
		// Points which compose the rectangle
		Base::c_Point3D_Floating PtA = lowestBound;
		Base::c_Point3D_Floating PtB = lowestBound;
		PtB.x += DIFF.x;
		Base::c_Point3D_Floating PtC = lowestBound;
		PtC.y += DIFF.y;
		Base::c_Point3D_Floating PtD = lowestBound;
		PtD.x += DIFF.x;
		PtD.y += DIFF.y;
		
		Base::c_Point3D_Floating PtE = highestBound;
		Base::c_Point3D_Floating PtF = highestBound;
		PtF.x -= DIFF.x;
		Base::c_Point3D_Floating PtG = highestBound;
		PtG.y -= DIFF.y;
		Base::c_Point3D_Floating PtH = highestBound;
		PtH.x -= DIFF.x;
		PtH.y -= DIFF.y;
		
		// Faces of the rectangle
		c_Face_Triangle F1A(PtA, PtB, PtH);
		c_Face_Triangle F1B(PtF, PtB, PtH);
		
		c_Face_Triangle F2A(PtB, PtD, PtF);
		c_Face_Triangle F2B(PtE, PtD, PtF);
		
		c_Face_Triangle F3A(PtD, PtE, PtC);
		c_Face_Triangle F3B(PtG, PtE, PtC);
		
		c_Face_Triangle F4A(PtC, PtA, PtH);
		c_Face_Triangle F4B(PtC, PtG, PtH);
		
		c_Face_Triangle F5A(PtH, PtF, PtG);
		c_Face_Triangle F5B(PtE, PtF, PtG);
		
		c_Face_Triangle F6A(PtA, PtB, PtC);
		c_Face_Triangle F6B(PtD, PtB, PtC);
		
		// Do the magicalities
		c_Volume X;
		X.Faces = {F1A, F1B,  F2A, F2B,  F3A, F3B,  F4A, F4B,  F5A, F5B,  F6A, F6B};
		X.updatePointers();
		X.calculateData();
		return X;
	}
	
}}; //End Anoptamin::Geometry
