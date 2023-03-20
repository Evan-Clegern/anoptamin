/********!
 * @file  geometry.hpp
 * 
 * @author
 * 	Evan Clegern <evanclegern.work@gmail.com>
 * 
 * @date
 * 	16 March 2023
 * 
 * @brief
 * 	Provides handling for basic 2D geometries (rectangles, triangles)
 *	and then 3D shapes constructed from them, as well as utilities
 *	for quickly operating on them, or on points.
 *	Provides includes in:
 *		Anoptamin::Geometry
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

#ifndef anoptamin_geom
#define anoptamin_geom

#include "base.hpp"

namespace Anoptamin { namespace Geometry {
	static const long double PI =         3.14159265359;
	static const long double EULER =      2.71828182846;
	static const long double ANGStepRad = 0.00019175345;
	static const long double ANGStepDeg = 0.01098666341;
	
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL bool arePointsEqual_F(const Base::c_Point3D_Floating* A,
		const Base::c_Point3D_Floating* B) noexcept;
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL bool arePointsEqual_I(const Base::c_Point3D_Integer* A,
		const Base::c_Point3D_Integer* B) noexcept;
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL double getPointDist_F(const Base::c_Point3D_Floating* A,
		const Base::c_Point3D_Floating* B) noexcept;
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL double getPointDist_I(const Base::c_Point3D_Integer* A,
		const Base::c_Point3D_Integer* B) noexcept;
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL Base::c_Point3D_Floating getPointDiff_F(const Base::c_Point3D_Floating* A,
		const Base::c_Point3D_Floating* B) noexcept;
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL Base::c_Point3D_Integer getPointDiff_I(const Base::c_Point3D_Integer* A,
		const Base::c_Point3D_Integer* B) noexcept;
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL std::string pointToStr_F(const Base::c_Point3D_Floating* A) noexcept;
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL std::string pointToStr_I(const Base::c_Point3D_Integer* A) noexcept;
	
	//! Class which holds basic angle data in an efficient manner (as integer based fractions of 2PI)
	//! This still means that an angle has a precision of 0.010987 degrees per step, in either direction.
	struct c_Angle {
		//! Pitch Yaw and Roll respectively; each subsequent value being equal to (X * 2 Pi / 32767)
		int16_t Angle_AroundX = 0, Angle_AroundZ = 0, Angle_AroundY = 0;
		
		//! Return the angle as a value of (Angle_AroundX * (2 PI / 32767))
		double getPitch_Rad() const noexcept;
		//! Return the angle as a value of (Angle_AroundX * (360 / 32767))
		double getPitch_Deg() const noexcept;
		//! Return the angle as a value of (Angle_AroundZ * (2 PI / 32767))
		double getYaw_Rad() const noexcept;
		//! Return the angle as a value of (Angle_AroundZ * (360 / 32767))
		double getYaw_Deg() const noexcept;
		//! Return the angle as a value of (Angle_AroundY * (2 PI / 32767))
		double getRoll_Rad() const noexcept;
		//! Return the angle as a value of (Angle_AroundY * (360 / 32767))
		double getRoll_Deg() const noexcept;
		
		//! Sets the 'X' angle to a value which is a direct multiple of Pi: X = 32767(VAL) / (2 PI)
		void setPitch_Rad(double Radians) noexcept;
		//! Sets the 'X' angle to a value which is expressed as degrees: X = 32767(VAL) / 360
		void setPitch_Deg(double Degrees) noexcept;
		//! Sets the 'Z' angle to a value which is a direct multiple of Pi: Z = 32767(VAL) / (2 PI)
		void setYaw_Rad(double Radians) noexcept;
		//! Sets the 'Z' angle to a value which is expressed as degrees: Z = 32767(VAL) / 360
		void setYaw_Deg(double Degrees) noexcept;
		//! Sets the 'Y' angle to a value which is a direct multiple of Pi: Y = 32767(VAL) / (2 PI)
		void setRoll_Rad(double Radians) noexcept;
		//! Sets the 'Y' angle to a value which is expressed as degrees: Y = 32767(VAL) / 360
		void setRoll_Deg(double Degrees) noexcept;
		//! Returns a String representation.
		std::string toString(bool degrees = 1) const noexcept;
	};
	//! Class which represents a single 3D vector. Can be tied to a point.
	struct c_Vector3D {
		double ValX, ValY, ValZ, Magnitude;
		
		c_Vector3D(double X, double Y, double Z);
		//! Zero vector.
		c_Vector3D();
		c_Vector3D(const c_Vector3D& b);
		
		//! Calculates the vector's magnitude, given the three components.
		void calculateMagnitude() noexcept;
		//! Adjusts all values so that the sum of their squares all add up to one.
		void normalize() noexcept;
		//! Gets the angle at which the vector is pointed from the base point.
		c_Angle getAngles() const;
		//! Returns a String representation.
		std::string toString() const noexcept;
		
		c_Vector3D operator*(double scalar) const noexcept;
		c_Vector3D operator*(const c_Vector3D& vector2) const noexcept;
		c_Vector3D operator+(const c_Vector3D& vector2) const noexcept;
		c_Vector3D operator-(const c_Vector3D& vector2) const noexcept;
	};
	
namespace PtTransforms {
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL Base::c_Point3D_Floating translateBy_F(const Base::c_Point3D_Floating* main,
		const c_Vector3D* level) noexcept;
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL Base::c_Point3D_Integer translateBy_I(const Base::c_Point3D_Integer* main,
		const c_Vector3D* level) noexcept;
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL Base::c_Point3D_Floating scaleBy_F(const Base::c_Point3D_Floating* main,
		const c_Vector3D* level) noexcept;
	LIBANOP_FUNC_IMPORT LIBANOP_FUNC_HOT LIBANOP_FUNC_INPUTS_NONNULL Base::c_Point3D_Integer scaleBy_I(const Base::c_Point3D_Integer* main,
		const c_Vector3D* level) noexcept;
	LIBANOP_FUNC_HEADERPT LIBANOP_FUNC_HOT std::vector<std::vector<long double>> getRotationMatrix(const c_Angle& by);
	LIBANOP_FUNC_HEADERPT LIBANOP_FUNC_HOT Base::c_Point3D_Floating rotateByMatrix(const std::vector<std::vector<long double>> &vector, Base::c_Point3D_Floating main,
		const Base::c_Point3D_Floating& about);
}
	//! Class which represents a line drawn between two points.
	struct c_Edge {
		double Length;
		c_Angle EdgeAngle;
		const Base::c_Point3D_Floating *PointA, *PointB;
		
		c_Edge();
		LIBANOP_FUNC_INPUTS_NONNULL c_Edge(const Base::c_Point3D_Floating* from, const Base::c_Point3D_Floating* to);
		c_Edge(const c_Edge& b);
		
		//! Calculates the 'length' value and its angle.
		void calculateData();
		//! Calculate a vector to represent the edge from PointA to PointB.
		c_Vector3D calculateAsVector() const;
		//! Returns a String representation.
		std::string toString() const;
	};
	//! Class whichs contains the three points needed to compose a triangle.
	struct c_Face_Simple {
		Base::c_Point3D_Floating A, B, C;
	};
	//! Class which stores the simple point face plus information about it.
	struct c_Face_Triangle {
		double Area;
		Base::c_Point3D_Floating Center;
		c_Edge EdgeA, EdgeB, EdgeC;
		c_Face_Simple Points;
		
		c_Face_Triangle();
		//! Constructor which takes three points and creates the edges automatically.
		c_Face_Triangle(Base::c_Point3D_Floating A, Base::c_Point3D_Floating B, Base::c_Point3D_Floating C);
		c_Face_Triangle(const c_Face_Triangle& b);
		
		//! Computes the face's area and its center; updates state of edges as well.
		void calculateData();
		//! Returns a String representation.
		std::string toString() const;
	};
	//! Class which stores a simple bounded volume.
	struct c_Volume {
		std::vector<c_Face_Triangle> Faces;
		
		Base::c_Point3D_Floating Center;
		double SurfaceArea;
		
		//! Compute the volume's center and its Surface Area
		void calculateData();
		//! Simple string representation (lists stats and face count, but not main points)
		std::string toString() const;
		//! Gets all of the unique points which compose the volume
		std::vector<Base::c_Point3D_Floating> getAllPoints() const noexcept;
		
		//! Move the object by the amount specified in the vector.
		void translateSelf(c_Vector3D translateBy);
		//! Scale the object's points by the amount specified in the vector.
		void scaleSelf(c_Vector3D scaleBy);
		//! Scale the object's points by the amount specified.
		void scaleSelf(float scalar);
		//! Rotate the object by the various angles specified, about the position specified.
		void rotateSelf_About(c_Angle rotateBy, Base::c_Point3D_Integer about);
		//! Rotate the object by the various angles specified
		void rotateSelf(c_Angle rotateBy);
	};
	
	//! Generates a rectangular volume between the specified points
	LIBANOP_FUNC_HEADERPT LIBANOP_FUNC_HOT c_Volume generateRectangle(Base::c_Point3D_Floating lowestBound, Base::c_Point3D_Floating highestBound);
	
	// references for the rendering info:
	//https://open.gl/drawing
	//https://stackoverflow.com/questions/8766788/opengl-polygon-rendering-mode-and-texture-mapping
	//https://eng.libretexts.org/Bookshelves/Computer_Science/Applied_Programming/Book%3A_Introduction_to_Computer_Graphics_(Eck)/03%3A_OpenGL_1.1-_Geometry/3.04%3A_Polygonal_Meshes_and_glDrawArrays

}}; //End Anoptamin::Geometry

#endif
