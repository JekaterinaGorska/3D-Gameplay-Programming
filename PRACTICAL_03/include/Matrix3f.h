#ifndef MATRIX3_H
#define MATRIX3_H

#include <./include/Vector3f.h>

namespace gpp {
	class Matrix3f {
	private:
		float	A11, // row 1 col 1
				A12, // row 1 col 2
				A13, // row 1 col 3

				A21, // row 2 col 1
				A22, // row 2 col 2
				A23, // row 2 col 3

				A31, // row 3 col 1
				A32, // row 3 col 2
				A33; // row 3 col 3
	public:

		Matrix3f();
		Matrix3f(const Vector3f&, const Vector3f&, const Vector3f&);
		Matrix3f(const float, const float, const float, const float, const float, const float, const float, const float, const float);

		friend Vector3f operator * (const Matrix3f&, const Vector3f&);
		
		Vector3f row(const int&) const;
		Vector3f column(const int&) const;

		static Matrix3f rotateX(const float&);
		static Matrix3f rotateY(const float&);
		static Matrix3f rotateZ(const float&);

		friend ostream& operator << (ostream&, const Matrix3f&);
		friend istream& operator >> (istream&, Matrix3f&);

	};
}

#endif // !MATRIX3_H

