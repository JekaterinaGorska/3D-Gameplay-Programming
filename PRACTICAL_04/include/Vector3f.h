#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <iostream>
#include <cmath>
#include <iomanip> 

using namespace std;

namespace gpp {
	class Vector3f
	{
	private:
		float x, y, z;
	public:
		Vector3f();
		Vector3f(const float, const float, const float);

		friend bool operator == (const Vector3f&, const Vector3f&);

		float getX() const;
		float getY() const;
		float getZ() const;

		float length() const;
		float lengthSquared() const;
		void normalise();

		friend ostream& operator << (ostream&, const Vector3f&);
		friend istream& operator >> (istream&, Vector3f&);
	};
}
#endif // !VECTOR3F_H
