#include <./include/Vector3f.h>

using namespace gpp;

Vector3f::Vector3f() : x(0.0f), y(0.0f), z(0.0f) { }

Vector3f::Vector3f(const float x, const float y, const float z) : x(x), y(y), z(z) { }

bool gpp::operator == (const Vector3f& lhs, const Vector3f& rhs) {
	if (lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z)
		return true;
	else
		return false;
}

float Vector3f::getX() const {
	return x;
}

float Vector3f::getY() const {
	return y;
}

float Vector3f::getZ() const {
	return z;
}

float Vector3f::length() const {
	return sqrt(x * x + y * y + z * z);
}

float Vector3f::lengthSquared() const {
	return (x * x + y * y + z * z);
}

void Vector3f::normalise() {
	float magnitude = length();
	if (magnitude > 0)
	{
		x /= magnitude;
		y /= magnitude;
		z /= magnitude;
	}
}

ostream& gpp::operator << (ostream& out, const Vector3f& v){
	cout << "...[ Vector ]..." << endl;
	cout.setf(std::ios::fixed, std::ios::floatfield);
	out << "x:";
	out << setprecision(7) << v.x << "\t";
	out << " y:";
	out << setprecision(7) << v.y << "\t";
	out << " z:";
	out << setprecision(7) << v.z;
	out << endl;
	return out;
}

istream& gpp::operator >> (istream& in, Vector3f& v){
	cout << "Enter x: ";
	in >> v.x;
	cout << "Enter y: ";
	in >> v.y;
	cout << "Enter z: ";
	in >> v.z;
	return in;
}