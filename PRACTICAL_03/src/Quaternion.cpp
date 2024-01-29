#include <./include/Quaternion.h>

using namespace gpp;

Quaternion::Quaternion() : w(0.0f), x(0.0f), y(0.0f), z(0.0f) { }

Quaternion::Quaternion(const float w, const float x, const float y, const float z) : w(w), x(x), y(y), z(z) {}

Quaternion gpp::operator * (const Quaternion& lhs, const Quaternion & rhs){
	return Quaternion(
		lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
		lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x
	);
}

Quaternion Quaternion::conjugate() const{
	return Quaternion(w, -x, -y, -z);
}

Quaternion Quaternion::normalise() const{
	float magnitude = w * w + x * x + y * y + z * z;
	if (magnitude > 0.001){
		magnitude = sqrt(magnitude);
		return Quaternion(
			w / magnitude, 
			x / magnitude, 
			y / magnitude, 
			z / magnitude
		);
	}
	else {
		return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
	}
}

Vector3f Quaternion::rotate(const Vector3f& v, const float& angle) const {
	Quaternion rotate;
	this->normalise();

	float radians = (float)(angle * (acos(-1) / 180));

	rotate = Quaternion(
		cos(radians / 2), 
		sin(radians / 2) * this->x, 
		sin(radians / 2) * this->y, 
		sin(radians / 2) * this->z
	);

	Quaternion conjugate = rotate.conjugate();

	Quaternion result = Quaternion(0, v.getX(), v.getY(), v.getZ());
	result = rotate * result * conjugate;

	return Vector3f(result.x, result.y, result.z);
}

ostream& gpp::operator << (ostream& out, const Quaternion& q) {
	cout << "...[ Quaternion ]..." << endl;
	cout.setf(std::ios::fixed, std::ios::floatfield);
	out << "w:";
	out << setprecision(7) << q.w << "\t";
	out << "x:";
	out << setprecision(7) << q.x << "\t";
	out << " y:";
	out << setprecision(7) << q.y << "\t";
	out << " z:";
	out << setprecision(7) << q.z;
	out << endl;
	return out;
}

istream& gpp::operator >> (istream& in, Quaternion& q) {
	cout << "Enter w: ";
	in >> q.x;
	cout << "Enter x: ";
	in >> q.x;
	cout << "Enter y: ";
	in >> q.y;
	cout << "Enter z: ";
	in >> q.z;
	return in;
}