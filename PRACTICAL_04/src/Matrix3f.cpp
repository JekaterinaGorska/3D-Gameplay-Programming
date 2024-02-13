#include <./include/Matrix3f.h>

using namespace gpp;

Matrix3f::Matrix3f() :
	A11(0.0f), A12(0.0f), A13(0.0f),
	A21(0.0f), A22(0.0f), A23(0.0f),
	A31(0.0f), A32(0.0f), A33(0.0f)
{
}

Matrix3f::Matrix3f(const Vector3f& row1, const Vector3f& row2, const Vector3f& row3) :
	A11(row1.getX()), A12(row1.getY()), A13(row1.getZ()),
	A21(row2.getX()), A22(row2.getY()), A23(row2.getZ()),
	A31(row3.getX()), A32(row3.getY()), A33(row3.getZ())
{
}

Matrix3f::Matrix3f(
	const float A11, const float A12, const float A13,
	const float A21, const float A22, const float A23,
	const float A31, const float A32, const float A33
) :
	A11(A11), A12(A12), A13(A13),
	A21(A21), A22(A22), A23(A23),
	A31(A31), A32(A32), A33(A33)
{
}

Vector3f gpp::operator * (const Matrix3f& lhs, const Vector3f& rhs) {
	return Vector3f(
		lhs.A11 * rhs.getX() + lhs.A12 * rhs.getY() + lhs.A13 * rhs.getZ(),
		lhs.A21 * rhs.getX() + lhs.A22 * rhs.getY() + lhs.A23 * rhs.getZ(),
		lhs.A31 * rhs.getX() + lhs.A32 * rhs.getY() + lhs.A33 * rhs.getZ()
	);
}

Vector3f Matrix3f::row(const int& i) const
{
	switch (i)
	{
	case 0:
		return Vector3f(A11, A12, A13);
	case 1:
		return Vector3f(A21, A22, A23);
	case 2:
	default:
		return Vector3f(A31, A32, A33);
	}
}

Vector3f Matrix3f::column(const int& i) const
{
	switch (i)
	{
	case 0:
		return Vector3f(A11, A21, A31);
	case 1:
		return Vector3f(A12, A22, A32);
	case 2:
	default:
		return Vector3f(A13, A23, A33);
	}
}

Matrix3f Matrix3f::rotateX(const float& angle) {
	float radians = (float)(angle * (acos(-1) / 180));
	return Matrix3f(
		1.0, 0.0, 0.0,
		0.0, cos(radians), -sin(radians),
		0.0, sin(radians), cos(radians)
	);
}

Matrix3f Matrix3f::rotateY(const float& angle) {
	float radians = (float)(angle * (acos(-1) / 180));
	return Matrix3f(
		cos(radians), 0.0, -sin(radians),
		0.0, 1.0, 0.0,
		sin(radians), 0.0, cos(radians)
	);
}

Matrix3f Matrix3f::rotateZ(const float& angle) {
	float radians = (float)(angle * (acos(-1) / 180));
	return Matrix3f(
		cos(radians), -sin(radians), 0.0,
		sin(radians), cos(radians), 0.0,
		0.0, 0.0, 1.0
	);
}

Matrix3f Matrix3f::scale(const float& x, const float& y, const float& z) {
	return Matrix3f(
		x, 0.0, 0.0,
		0.0, y, 0.0,
		0.0, 0.0, z
	);
}

Matrix3f Matrix3f::translateX(const float& x) {
	return Matrix3f(
		1.0, 0.0, x,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0
	);
}

Matrix3f Matrix3f::translateY(const float& y) {
	return Matrix3f(
		1.0, 0.0, 0.0,
		0.0, 1.0, y,
		0.0, 0.0, 1.0
	);
}

Matrix3f Matrix3f::translateZ(const float& z) {
	return Matrix3f(
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, z
	);
}

ostream& gpp::operator << (ostream& out, const Matrix3f& m) {
	cout << "...[ Matrix ]..." << endl;
	for (int i = 0; i < 3; i++) {
		cout << m.row(i); // Output the Vector
	}
	return out;
}

istream& gpp::operator >> (istream& in, Matrix3f& m) {
	Vector3f v;
	Vector3f rows[3];
	for (int i = 0; i <= 2; i++) {
		cout << "Enter Matrix Row " << i << " Vector" << endl;
		cin >> v; // cin each Matrix row as a Vector
		rows[i] = v;
	}
	m = Matrix3f(
		rows[0], 
		rows[1], 
		rows[2]
	);

	return in;
}