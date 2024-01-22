#include <./include/Game.h>

bool updatable = false;

Game::Game() : window(VideoMode(800, 600), "OpenGL Primatives")
{
	index = glGenLists(1);
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning)
	{

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		draw();
	}
}

void Game::initialize()
{
	isRunning = true;

	//set colour of colour buffer
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//set current matrix mode in matrix stack. It stores different transformations.
	//Different types of transformatin matrices include modelview, projection and texture matrices
	glMatrixMode(GL_PROJECTION);
	//replace current matrix with identity matrix. Matrices are used to perform various
	// transformations like translation, rotation, scaling, position
	glLoadIdentity();
	//gluPerspective is used to set up a perspective projection matrix for a 3D scene
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	//Setting another matrix mode. Three main modes-> Model, View, Projection.
	glMatrixMode(GL_MODELVIEW);

	// glNewList(index, GL_COMPILE);
	// Creates a new Display List
	// Initalizes and Compiled to GPU
	// https://www.opengl.org/sdk/docs/man2/xhtml/glNewList.xml
	glNewList(index, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	{

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0, 2.0, -5.0);

		glVertex3f(-2.0, -2.0, -5.0);

		glVertex3f(2.0, -2.0, -5.0);
	}

	glEnd();
	glEndList();
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!updatable)
		{
			updatable = true;
		}
		else
			updatable = false;
	}

	if (updatable)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}

	cout << "Update up" << endl;
}

void Game::draw()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Drawing Primatives " << endl;
	glLoadIdentity();
	glRotatef(rotationAngle, 0, 0, 1); // Rotates the camera on Z Axis

	glCallList(1);

	window.display();
}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}
