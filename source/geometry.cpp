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
		return Base::round(std::sqrt( std::pow(A->x - B->x, 2) + std::pow(A->y - B->y, 2) + std::pow(A->z - B->z, 2) ));
	}
	LIBANOP_FUNC_EXPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL double getPointDist_I(const Base::c_Point3D_Integer* A,
	const Base::c_Point3D_Integer* B) noexcept {
		return Base::round(std::sqrt( std::pow(A->x - B->x, 2) + std::pow(A->y - B->y, 2) + std::pow(A->z - B->z, 2) ));
	}
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL Base::c_Point3D_Floating getPointDiff_F(const Base::c_Point3D_Floating* A,
	const Base::c_Point3D_Floating* B) noexcept {
		Base::c_Point3D_Floating N(Base::round(A->x - B->x, 3), Base::round(A->y - B->y, 3), Base::round(A->z - B->z, 3));
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
		return Base::round(this->Angle_AroundX * ANGStepRad);
	}
	
	double c_Angle::getPitch_Deg() const noexcept {
		return Base::round(this->Angle_AroundX * ANGStepDeg);
	}
	
	double c_Angle::getYaw_Rad() const noexcept {
		return Base::round(this->Angle_AroundZ * ANGStepRad);
	}
	
	double c_Angle::getYaw_Deg() const noexcept {
		return Base::round(this->Angle_AroundZ * ANGStepDeg);
	}
	
	double c_Angle::getRoll_Rad() const noexcept {
		return Base::round(this->Angle_AroundY * ANGStepRad);
	}
	
	double c_Angle::getRoll_Deg() const noexcept {
		return Base::round(this->Angle_AroundY * ANGStepDeg);
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
		ValX = Base::round(X,3); ValY = Base::round(Y,3); ValZ = Base::round(Z,3);
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
		this->Magnitude = Base::round(std::sqrt( (this->ValX * this->ValX) + (this->ValY * this->ValY) + (this->ValZ * this->ValZ) ));
	}
	// the square of ValX, ValY and ValZ must add up to 1
	void c_Vector3D::normalize() noexcept {
		this->calculateMagnitude();
		this->ValX = Base::round(this->ValX / this->Magnitude, 3);
		this->ValY = Base::round(this->ValY / this->Magnitude, 3);
		this->ValZ = Base::round(this->ValZ / this->Magnitude, 3);
	}
	//! Gets the angle at which the vector is pointed from the base point.
	
	// They're all ARCTAN because the vector's magnitude is the hypotenuse of any given right triangle.
	// Radians are the default value in CMATH
	c_Angle c_Vector3D::getAngles() const {
		c_Angle TMP;
		// About the 'x' axis (Y / Z)
		TMP.setPitch_Rad( Base::round(std::atan( this->ValY	/ this->ValZ )) );
		// About the 'z' axis (X / Y)
		TMP.setYaw_Rad( Base::round(std::atan( this->ValX / this->ValY )) );
		// About the 'y' axis (X / Z)
		TMP.setRoll_Rad( Base::round(std::atan( this->ValX / this->ValZ )) );
		
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
		TMP.ValX = Base::round(scalar * TMP.ValX, 3);
		TMP.ValY = Base::round(scalar * TMP.ValY, 3);
		TMP.ValZ = Base::round(scalar * TMP.ValZ, 3);
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
	
	double c_Vector3D::dotProduct(const c_Vector3D& b) const noexcept {
		return Base::round(b.ValX * this->ValX) + Base::round(b.ValY * this->ValY) + Base::round(b.ValZ * this->ValZ);
	}
	
	c_Vector3D c_Vector3D::crossProduct(const c_Vector3D& b) const noexcept {
		return c_Vector3D(
			Base::round((this->ValY * b.ValZ) - (this->ValZ * b.ValY), 3),
			Base::round((this->ValX * b.ValZ) - (this->ValZ * b.ValX), 3),
			Base::round((this->ValX * b.ValY) - (this->ValY * b.ValX), 3)
		);
	}
	//Stop c_Vector3D methods
	
	
	//uint16_t SizeRow, SizeCol;
	//std::vector< std::vector<long double> > MainData;
	
	//! Construct it with a single continuous value.
	c_Matrix::c_Matrix(uint16_t rows, uint16_t cols, long double fillWith) {
		SizeRow = rows;
		SizeCol = cols;
		MainData.clear();
		for (uint16_t i = 0; i < rows; i++) {
			std::vector<long double> tmp;
			for (uint16_t j = 0; j < rows; j++) {
				tmp.push_back(fillWith);
			}
			MainData.push_back(tmp);
		}
	}
	//! Construct it with random values between 0 and 1.
	c_Matrix::c_Matrix(uint16_t rows, uint16_t cols) {
		SizeRow = rows;
		SizeCol = cols;
		MainData.clear();
		std::uniform_real_distribution<long double> distr(0.0, 1.0);
		for (uint16_t i = 0; i < rows; i++) {
			std::vector<long double> tmp;
			for (uint16_t j = 0; j < rows; j++) {
				tmp.push_back(distr(Base::RANDengine));
			}
			MainData.push_back(tmp);
		}
	}
	//! Construct it with an initialization vector (will check size!)
	c_Matrix::c_Matrix(uint16_t rows, uint16_t cols, std::initializer_list<std::initializer_list<long double>> data) {
		SizeRow = rows;
		SizeCol = cols;
		MainData.clear();
		
		check_param(data.size() == rows);
		for (std::initializer_list<long double> EachRow : data) {
			check_param(EachRow.size() == cols);
			
			std::vector<long double> newvec = EachRow;
			MainData.push_back(newvec);
		}
	}
	//! Construct it with a filled set of vectors (will check initial sizes, but not all vectors)
	c_Matrix::c_Matrix(uint16_t rows, uint16_t cols, std::vector<std::vector<long double>> data) {
		SizeRow = rows;
		SizeCol = cols;
		MainData.clear();
		
		check_param(data.size() == rows);
		check_param(data.at(0).size() == cols);
		
		MainData = data;
	}
	//! Copy an existing matrix.
	c_Matrix::c_Matrix(const c_Matrix& b) {
		SizeRow = b.SizeRow;
		SizeCol = b.SizeCol;
		MainData.clear();
		
		check_param(b.MainData.size() == SizeRow);
		for (std::vector<long double> i : b.MainData) {
			check_param(i.size() == SizeCol);
			MainData.push_back(i);
		}
	}
	
	//! Access a value at given position
	long double& c_Matrix::get(uint16_t row, uint16_t col) {
		check_param(row < this->SizeRow);
		check_param(col < this->SizeCol);
		return this->MainData.at(row).at(col);
	}
	
	long double c_Matrix::at(uint16_t row, uint16_t col) const {
		check_param(row < this->SizeRow);
		check_param(col < this->SizeCol);
		return this->MainData.at(row).at(col);
	}
	
	//! Calculate the dot product between two matrices
	c_Matrix c_Matrix::dotProduct(const c_Matrix& b) const {
		uint16_t OutsizeRows, OutsizeCols, Sharedsize;
		bool MatchesSelfCols = 0;
		if (b.SizeRow == this->SizeCol) {
			Sharedsize = this->SizeCol;
			OutsizeRows = this->SizeRow;
			OutsizeCols = b.SizeCol;
			MatchesSelfCols = 1;
		} else if (b.SizeCol == this->SizeRow) {
			Sharedsize = this->SizeRow;
			OutsizeCols = this->SizeCol;
			OutsizeRows = b.SizeRow;
		} else {
			throw std::invalid_argument("Cross product impossible with provided matrix; no matching dimensions");
		}
		std::vector<std::vector<long double>> TMP;
		for (uint16_t Row = 0; Row < OutsizeRows; Row++) {
			std::vector<long double> Current;
			for (uint16_t Col = 0; Col < OutsizeCols; Col++) {
				long double Working = 0;
				for (uint16_t i = 0; i < Sharedsize; i++) {
					if (MatchesSelfCols) {
						Working += this->MainData.at(Row).at(i) * b.MainData.at(i).at(Col);
					} else {
						Working += this->MainData.at(i).at(Col) * b.MainData.at(Row).at(i);
					}
				}
				Current.push_back(Working);
			}
			TMP.push_back(Current);
		}
		return c_Matrix(OutsizeRows, OutsizeCols, TMP);
	}
	
	std::string c_Matrix::toString() const {
		std::string OUT = std::to_string(this->SizeRow) + "x" + std::to_string(this->SizeCol) + " matrix:\n";
		for (uint16_t row = 0; row < this->SizeRow; row++) {
			std::string TMP = "[ ";
			for (uint16_t col = 0; col < this->SizeCol; col++) {
				TMP += std::to_string( this->at(row, col) );
				if (col != (this->SizeCol - 1)) {
					TMP += ", ";
				} else {
					TMP += " ]\n";
				}
			}
			OUT += TMP;
		}
		return OUT;
	}
	// stop c_Matrix methods
	
namespace PtTransforms {
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL Base::c_Point3D_Floating translateBy_F(const Base::c_Point3D_Floating* main,
	const c_Vector3D* level) noexcept {
		Base::c_Point3D_Floating NEWPT(*main);
		NEWPT.x = Base::round(NEWPT.x + level->ValX, 3);
		NEWPT.y = Base::round(level->ValY + NEWPT.y, 3);
		NEWPT.z = Base::round(level->ValZ + NEWPT.z, 3);
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
		NEWPT.x = Base::round(level->ValX * NEWPT.x, 3);
		NEWPT.y = Base::round(level->ValY * NEWPT.y, 3);
		NEWPT.z = Base::round(level->ValZ * NEWPT.z, 3);
		return NEWPT;
	}
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL Base::c_Point3D_Integer scaleBy_I(const Base::c_Point3D_Integer* main,
	const c_Vector3D* level) noexcept {
		Base::c_Point3D_Integer NEWPT(*main);
		NEWPT.x = (int)(level->ValX * NEWPT.x);
		NEWPT.y = (int)(level->ValY * NEWPT.y);
		NEWPT.z = (int)(level->ValZ * NEWPT.z);
		return NEWPT;
	}
	
	LIBANOP_FUNC_CODEPT LIBANOP_FUNC_HOT std::array<c_Matrix, 3> getRotationMatrices(const c_Angle& by) {
		// 'A' vector: 1x3
		// 'B' vector: 3x3
		// Output: 1x3 (new point)


		const long double SinAlph = Base::round(std::sin(by.getYaw_Rad()));
		const long double CosAlph = Base::round(std::cos(by.getYaw_Rad()));
		
		const long double SinBeta = Base::round(std::sin(by.getPitch_Rad()));
		const long double CosBeta = Base::round(std::cos(by.getPitch_Rad()));
		
		const long double SinGamm = Base::round(std::sin(by.getRoll_Rad()));
		const long double CosGamm = Base::round(std::cos(by.getRoll_Rad()));
		// Manually create the matrix (using proper axes)
		// 'α, β, γ, about axes z, y, x'...
		// except we have Pitch about x, and not about y, so it is adjusted accordingly
		// for Wikipedia info: ALPHA is YAW  BETA is PITCH  GAMMA is ROLL
		
		c_Matrix FromYaw(3, 3, {
			{CosAlph, -1 * SinAlph, 0},
			{SinAlph, CosAlph, 0},
			{0, 0, 1}
		});
		c_Matrix FromPitch(3, 3, {
			{CosBeta, 0, SinBeta},
			{0, 1, 0},
			{-1 * SinBeta, 0, CosBeta}
		});
		c_Matrix FromRoll(3, 3, {
			{1, 0, 0},
			{0, CosGamm, -1 * SinGamm},
			{0, SinGamm, CosGamm}
		});
		
		std::array<c_Matrix, 3> OUT = {FromYaw, FromPitch, FromRoll};
		return OUT;
	}
	/*
    1 Translate the object to world origin
        Object's origin would align with world's, making r = 0
    2 Rotate with one (or more) aforementioned rotation matrices
    3 Translate object back again to its previous (original) location.
	*/
	LIBANOP_FUNC_CODEPT LIBANOP_FUNC_HOT Base::c_Point3D_Floating rotateByMatrices(const std::array<c_Matrix, 3> &matrix, Base::c_Point3D_Floating main,
	const Base::c_Point3D_Floating& about) {
		Base::c_Point3D_Floating origin(0.0, 0.0, 0.0);
		Base::c_Point3D_Floating offset = getPointDiff_F(&about, &origin);
		Base::c_Point3D_Floating direct = getPointDiff_F(&main, &offset);
		c_Matrix AsMatr(1, 3, { {direct.x, direct.y, direct.z} });
		c_Matrix YawRot = AsMatr.dotProduct(matrix[0]);
		c_Matrix PitRot = YawRot.dotProduct(matrix[1]);
		c_Matrix RolRot = PitRot.dotProduct(matrix[2]);
		return Base::c_Point3D_Floating(Base::round(RolRot.at(0,0) + offset.x, 3), Base::round(RolRot.at(0,1) + offset.y, 3), Base::round(RolRot.at(0,2) + offset.z, 3));
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
		TMPANG.setPitch_Rad( Base::round(std::acos(DIFF.x / this->Length)) );
		TMPANG.setYaw_Rad( Base::round(std::acos(DIFF.z / this->Length)) );
		TMPANG.setRoll_Rad( Base::round(std::acos(DIFF.y / this->Length)) );
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
		double tmpx = Base::round((this->Points.A.x + this->Points.B.x + this->Points.C.x) / 3, 3);
		double tmpy = Base::round((this->Points.A.y + this->Points.B.y + this->Points.C.y) / 3, 3);
		double tmpz = Base::round((this->Points.A.z + this->Points.B.z + this->Points.C.z) / 3, 3);
		this->Center = Base::c_Point3D_Floating(tmpx, tmpy, tmpz);
		// Distances
		double gooberAB = this->EdgeA.Length;
		double gooberBC = this->EdgeB.Length;
		double gooberCA = this->EdgeC.Length;
		long double perim = Base::round(0.5 * (gooberAB + gooberBC + gooberCA));
		this->Area = Base::round(std::sqrt( perim * (perim - gooberAB) * (perim - gooberBC) * (perim - gooberCA) ));
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
		this->SurfaceArea = Base::round(this->SurfaceArea);
		Base::c_Point3D_Floating NTMP;
		NTMP.x = Base::round(TMP.x / this->Faces.size(), 3);
		NTMP.y = Base::round(TMP.y / this->Faces.size(), 3);
		NTMP.z = Base::round(TMP.z / this->Faces.size(), 3);
		this->Center = NTMP;
	}
	
	// codeonly, test if the point is in vector
	bool isPtInVec(Base::c_Point3D_Floating* point, std::vector<Base::c_Point3D_Floating>& vector) {
		for (auto i : vector) {
			if (i.x == point->x) {
				bool N = (i.y == point->y) and (i.z == point->z);
				if (N) return true; else continue;
			}
		}
		return false;
	}
	// codeonly, test if the point is in vector
	bool isPtInVec(Base::c_Point3D_Floating point, std::vector<Base::c_Point3D_Floating>& vector) {
		for (auto i : vector) {
			if (i.x == point.x) {
				bool N = (i.y == point.y) and (i.z == point.z);
				if (N) return true; else continue;
			}
		}
		return false;
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
		for (c_Face_Triangle& i : this->Faces) {
			auto na = PtTransforms::translateBy_F(&i.Points.A, &nvec);
			i.Points.A = na;
			na = PtTransforms::translateBy_F(&i.Points.B, &nvec);
			i.Points.B = na;
			na = PtTransforms::translateBy_F(&i.Points.C, &nvec);
			i.Points.C = na;
		}
		this->calculateData();
	}
	
	// code-only for scaling in respect to another point
	// distances must be scaled properly!!!!!!!
	Base::c_Point3D_Floating scaleWith(Base::c_Point3D_Floating main, Base::c_Point3D_Floating from, double xSc, double ySc, double zSc) {
		// treat 'from' as the arbitrary origin
		double diff_x = from.x - main.x, diff_y = from.y - main.y, diff_z = from.z - main.z;
		
		long double scale_x = diff_x * xSc, scale_y = diff_y * ySc, scale_z = diff_z * zSc;
		
		return Base::c_Point3D_Floating(Base::round(from.x + scale_x, 3), Base::round(from.y + scale_y, 3), Base::round(from.z + scale_z, 3));
	}
	
	// we have to increase the distance of each point from the center
	//! Scale the object's points by the amount specified in the vector.
	void c_Volume::scaleSelf(c_Vector3D scaleBy) {
		for (c_Face_Triangle& i : this->Faces) {
			i.Points.A = scaleWith(i.Points.A, this->Center, scaleBy.ValX, scaleBy.ValY, scaleBy.ValZ);
			i.Points.B = scaleWith(i.Points.B, this->Center, scaleBy.ValX, scaleBy.ValY, scaleBy.ValZ);
			i.Points.C = scaleWith(i.Points.C, this->Center, scaleBy.ValX, scaleBy.ValY, scaleBy.ValZ);
		}
		this->calculateData();
	}
	void c_Volume::scaleSelf(float scaleBy) {
		for (c_Face_Triangle& i : this->Faces) {
			i.Points.A = scaleWith(i.Points.A, this->Center, scaleBy, scaleBy, scaleBy);
			i.Points.B = scaleWith(i.Points.B, this->Center, scaleBy, scaleBy, scaleBy);
			i.Points.C = scaleWith(i.Points.C, this->Center, scaleBy, scaleBy, scaleBy);
		}
		this->calculateData();
	}
	// rotation time baby
	//! Rotate the object by the various angles specified
	void c_Volume::rotateSelf(c_Angle rotateBy) {
		auto rotvec = PtTransforms::getRotationMatrices(rotateBy);
		const auto this_ctr = this->Center;
		for (c_Face_Triangle& i : this->Faces) {
			i.Points.A = PtTransforms::rotateByMatrices(rotvec, i.Points.A, this_ctr);
			i.Points.B = PtTransforms::rotateByMatrices(rotvec, i.Points.B, this_ctr);
			i.Points.C = PtTransforms::rotateByMatrices(rotvec, i.Points.C, this_ctr);
		}
		this->calculateData();
	}
	//! Rotate the object by the various angles specified, about the position specified.
	void c_Volume::rotateSelf_About(c_Angle rotateBy, Base::c_Point3D_Integer about) {
		auto rotvec = PtTransforms::getRotationMatrices(rotateBy);
		for (c_Face_Triangle& i : this->Faces) {
			i.Points.A = PtTransforms::rotateByMatrices(rotvec, i.Points.A, about);
			i.Points.B = PtTransforms::rotateByMatrices(rotvec, i.Points.B, about);
			i.Points.C = PtTransforms::rotateByMatrices(rotvec, i.Points.C, about);
		}
		this->calculateData();
	}
	
	std::vector<Base::c_Point3D_Floating> c_Volume::getAllPoints() const noexcept {
		std::vector<Base::c_Point3D_Floating> TMP;
		for (c_Face_Triangle i : this->Faces) {
			if (!isPtInVec(i.Points.A, TMP)) {
				TMP.push_back(i.Points.A);
			}
			if (!isPtInVec(i.Points.B, TMP)) {
				TMP.push_back(i.Points.B);
			}
			if (!isPtInVec(i.Points.C, TMP)) {
				TMP.push_back(i.Points.C);
			}
		}
		return TMP;
	}
	
	// End c_Volume methods
	
	//! Generates a rectangular volume between the specified points
	LIBANOP_FUNC_CODEPT LIBANOP_FUNC_HOT c_Volume generateRectangle(Base::c_Point3D_Floating lowestBound, Base::c_Point3D_Floating highestBound) {
		// gets the dimensions
		long double OffsetX = highestBound.x - lowestBound.x;
		long double OffsetY = highestBound.y - lowestBound.y;
		long double OffsetZ = highestBound.z - lowestBound.z;
		
		// Points which compose the rectangle
		Base::c_Point3D_Floating PtA = lowestBound;
		Base::c_Point3D_Floating PtB = lowestBound;
		PtB.x += OffsetX;
		Base::c_Point3D_Floating PtC = lowestBound;
		PtC.y += OffsetY;
		Base::c_Point3D_Floating PtD = lowestBound;
		PtD.x += OffsetX;
		PtD.y += OffsetY;
		Base::c_Point3D_Floating PtE = lowestBound;
		PtE.z += OffsetZ;
		Base::c_Point3D_Floating PtF = lowestBound;
		PtF.x += OffsetX;
		PtF.z += OffsetZ;
		Base::c_Point3D_Floating PtG = lowestBound;
		PtG.y += OffsetY;
		PtG.z += OffsetZ;
		Base::c_Point3D_Floating PtH = lowestBound;
		PtH.x += OffsetX;
		PtH.y += OffsetY;
		PtH.z += OffsetZ;
		
		
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
		X.calculateData();
		return X;
	}
	
}}; //End Anoptamin::Geometry
