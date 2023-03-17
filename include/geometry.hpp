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
	//! Class whichs contains pointers to three points to compose a triangle.
	struct c_Face_Simple {
		Base::c_Point3D_Floating* A, B, C;
	};
	//! Class which stores the simple point face plus information about it.
	struct c_Face_Triangle {
		double Area, Opposite, Adjacent, Hypotenuse;
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
			long double SurfaceArea;
		};
		Base::c_Point3D_Integer meshCenter;
	};
	
}}; //End Anoptamin::Geometry

#endif
