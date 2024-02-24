#include <./include/Debug.h>
#include <assert.h>

#include <./include/Vector3f.h>
#include <./include/Matrix3f.h>
#include <./include/Quaternion.h>

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <GL/gl.h>
#include <GL/glu.h>

// Enable asserts NDEBUG
// Comment / uncomment this line 
// to enable / disable assert macro
#define NDEBUG 

// Print Vector3f Array
static void print(const gpp::Vector3f v[]) {
	for (int i = 0; i < 3; i++) {
		DEBUG_MSG(v[i]);
	}
}

static void test() {
	gpp::Vector3f v1(0.0, 2.0, -5.0);
	DEBUG_MSG("Vectors v1");
	cout << v1 << endl;
	DEBUG_MSG("Vectors v1.length()");
	cout << v1.length() << "\n\n" << endl;
	assert(v1.length() == 5.3851647f);

	gpp::Vector3f v2(-2.0, -2.0, -5.0);
	DEBUG_MSG("Vectors v2");
	cout << v2 << endl;
	DEBUG_MSG("Vectors v2.lengthSquared()");
	cout << v2.lengthSquared() << "\n" << endl;
	assert(v2.lengthSquared() == 33.0f);

	gpp::Vector3f v3(2.0, -2.0, -5.0);
	DEBUG_MSG("Vectors v3");
	cout << v3;
	DEBUG_MSG("v3 Matrix rotated in Z axis by 23.21 degrees\n");
	cout << gpp::Matrix3f::rotateZ(23.21f) * v3 << "\n" << endl;

	// Test 23.21f
	assert((gpp::Matrix3f::rotateZ(23.21f) * v3) == gpp::Vector3f(2.6263378f, -1.0499284f, -5.0000000f));

	DEBUG_MSG("v3 Matrix rotated in Z axis by 5 degrees\n");
	cout << gpp::Matrix3f::rotateZ(5.0f) * v3 << "\n" << endl;

	// Test 5.0f
	assert((gpp::Matrix3f::rotateZ(5.0f) * v3) == gpp::Vector3f(2.1667008f, -1.8180779f, -5.0000000f));

	DEBUG_MSG("Quaternion about z axis gpp::Quaternion q(0.0f, 0.0f, 0.0f, 1.0f)");
	gpp::Quaternion q(0.0f, 0.0f, 0.0f, 1.0f);

	DEBUG_MSG("v3 Quaternion rotated Z axis 23.21 degrees");
	cout << q.rotate(v3, 23.21f);
	assert(q.rotate(v3, 23.21f).getX() > 2.6263370f && q.rotate(v3, 23.21f).getX() < 2.6263380f);
	assert(q.rotate(v3, 23.21f).getY() < -1.0499280f && q.rotate(v3, 23.21f).getY() > -1.0499290f);

	DEBUG_MSG("v3 Quaternion rotated Z axis 5.00 degrees");
	cout << q.rotate(v3, 5.0f);
	assert(q.rotate(v3, 5.0f).getX() > 2.1667000f && q.rotate(v3, 5.0f).getX() < 2.1667010f);
	assert(q.rotate(v3, 5.0f).getY() < -1.8180770f && q.rotate(v3, 5.0f).getY() > -1.8180780f);

	DEBUG_MSG("TODO : Complete all Math Library function tests");
}

int main()
{

#if defined NDEBUG
	DEBUG_MSG("****** Starting Tests ******");
	test();
	DEBUG_MSG("****** Tests Complete ******");
#endif
	// Quaternion about z axis
	gpp::Quaternion q(0.0f, 0.0f, 0.0f, 1.0f);

	// Vector3f used to draw Triangle using OpenGL
	gpp::Vector3f triangle[3];
	triangle[0] = gpp::Vector3f(0.0, 2.0, -5.0);
	triangle[1] = gpp::Vector3f(-2.0, -2.0, -5.0);
	triangle[2] = gpp::Vector3f(2.0, -2.0, -5.0);

	// Setup SFML Window
	sf::Window window(sf::VideoMode(800, 600), "Math Library Tests");

	// Initialise OpenGL
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				switch(event.key.code){
				case sf::Keyboard::Left:
					// Matrix Rotate Left
					triangle[0] = gpp::Matrix3f::rotateZ(5.0f) * triangle[0];
					triangle[1] = gpp::Matrix3f::rotateZ(5.0f) * triangle[1];
					triangle[2] = gpp::Matrix3f::rotateZ(5.0f) * triangle[2];
					print(triangle);
					break;
				case sf::Keyboard::Right:
					// Matrix Rotate Right
					triangle[0] = gpp::Matrix3f::rotateZ(-5.0f) * triangle[0];
					triangle[1] = gpp::Matrix3f::rotateZ(-5.0f) * triangle[1];
					triangle[2] = gpp::Matrix3f::rotateZ(-5.0f) * triangle[2];
					print(triangle); 
					break;
				case sf::Keyboard::Up:
					// Quaternion Rotate Left
					triangle[0] = q.rotate(triangle[0], 5.0f);
					triangle[1] = q.rotate(triangle[1], 5.0f);
					triangle[2] = q.rotate(triangle[2], 5.0f);
					print(triangle); 
					break;
				case sf::Keyboard::Down:
					// Quaternion Rotate Right
					triangle[0] = q.rotate(triangle[0], -5.0f);
					triangle[1] = q.rotate(triangle[1], -5.0f);
					triangle[2] = q.rotate(triangle[2], -5.0f);
					print(triangle); 
					break;
				}
				break;
			}

		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBegin(GL_TRIANGLES); {
			// Set OpenGL Vertices
			glVertex3f(triangle[0].getX(), triangle[0].getY(), triangle[0].getZ());
			glVertex3f(triangle[1].getX(), triangle[1].getY(), triangle[1].getZ());
			glVertex3f(triangle[2].getX(), triangle[2].getY(), triangle[2].getZ());
		}
		glEnd();

		window.display();
	}

	return EXIT_SUCCESS;
}