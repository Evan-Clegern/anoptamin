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
	static const long double PI =         3.1415926535898;
	static const long double EULER =      2.7182818284590;
	static const long double ANGStepRad = 0.0001917534503;
	static const long double ANGStepDeg = 0.0109866634114;
	//! Class which holds basic angle data in an efficient manner (as integer based fractions of 2PI)
	//! This still means that an angle has a precision of 0.010987 degrees per step, in either direction.
	struct c_Angle {
		//! Pitch Yaw and Roll respectively; each subsequent value being equal to (X * 2 Pi / 32767)
		int16_t Angle_AroundX, Angle_AroundZ, Angle_AroundY;
		
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
	};
	//! Class whichs contains pointers to three points to compose a triangle.
	struct c_Face_Simple {
		Base::c_Point3D_Floating* A, B, C;
	};
	//! Class which stores the simple point face plus information about it.
	struct c_Face_Triangle {
		double Area, Hypotenuse;
		//! Angles relative to their trigonometric identities
		c_Angle Angle_Sine, Angle_Cosine;
		Base::c_Point3D_Floating Center;
		c_Face_Simple Points;
		
		void calculateData();
	};
	//! Class which combines two triangular faces by two fused points; an edge between two faces.
	struct c_Edge {
		const c_Face_Triangle* FaceA, FaceB;
		const Base::c_Point3D_Floating* PointA, PointB;
		bool isValid() const noexcept;
	};
	//! Class which combines the raw points, the edges it makes, and the total faces, along with extra information.
	struct c_Mesh {
		std::vector<Base::c_Point3D_Floating> basePoints;
		std::vector<c_Face_Triangle> mainTriangles;
		std::vector<c_Edge> triangleEdges;
		struct Stats {
			Base::c_Point3D_Floating Average, Variance, Min_All, Max_All;
			long double SurfaceArea; // just the sum of the Areas
		};
		Base::c_Point3D_Integer meshCenter;
	};
	
}}; //End Anoptamin::Geometry

#endif
