#ifndef QUATERNION_H
#define QUATERNION_H

#include <./include/Vector3f.h>
#include <iomanip> 

namespace gpp {
	class Quaternion {
	private:
		float w, x, y, z;
	public:
		Quaternion();
		Quaternion(const float, const float, const float, const float);

		friend Quaternion operator * (const Quaternion&, const Quaternion&);
		
		Quaternion conjugate() const;
		Quaternion normalise() const;

		Vector3f rotate(const Vector3f&, const float&) const;

		friend ostream& operator << (ostream&, const Quaternion&);
		friend istream& operator >> (istream&, Quaternion&);
	};
}
#endif // !QUATERNION_H