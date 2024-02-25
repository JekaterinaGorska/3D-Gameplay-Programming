#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/gl.h>
#include <GL/glu.h>


using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	//bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();
	void print(const float vertices[], int size);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void translate(float dx, float dy, float dz);
	void scale(float sx, float sy, float sz);

	float vertices[24];
	float colors[24];

	Clock clock;
	Time elapsed;
};