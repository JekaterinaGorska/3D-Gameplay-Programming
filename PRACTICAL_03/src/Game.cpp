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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

    lineStrip[0]-gpp::Vector3f(-3.0, -1.0, -25.0);
    lineStrip[1]-gpp::Vector3f(-3.0, -2.0, -25.0);
    lineStrip[2]-gpp::Vector3f(-1.0, -2.0, -25.0);
    lineStrip[3]-gpp::Vector3f(-0.5, -2.5, -25.0);
    lineStrip[4]-gpp::Vector3f(-0.5, -4.0, -25.0);
    lineStrip[5]-gpp::Vector3f(-1.0, -4.0, -25.0);
    lineStrip[6]-gpp::Vector3f(-1.0, -4.5, -25.0);
    lineStrip[7]-gpp::Vector3f(0.0, -4.5, -25.0);
    lineStrip[8]-gpp::Vector3f(0.0, -2.5, -25.0);
    lineStrip[9]-gpp::Vector3f(1.5, -2.5, -25.0);
    lineStrip[10]-gpp::Vector3f(1.5, -4.0, -25.0);
    lineStrip[11]-gpp::Vector3f (1.0, -4.0, -25.0);
    lineStrip[12]-gpp::Vector3f(1.0, -4.5, -25.0);
    lineStrip[13]-gpp::Vector3f(2.0, -4.5, -25.0);
    lineStrip[14]-gpp::Vector3f(2.0, -2.5, -25.0);
    lineStrip[15]-gpp::Vector3f(2.5, -1.5, -25.0);
    lineStrip[16]-gpp::Vector3f(2.5, -1.0, -25.0);
    lineStrip[17]-gpp::Vector3f(3.0, -1.0, -25.0);
    lineStrip[18]-gpp::Vector3f(3.0, -0.5, -25.0);

    lineStrip[19]-gpp::Vector3f(-1.6, -0.5, -25.0);
    lineStrip[20]-gpp::Vector3f(-1.9, 0.2,-25.0); lineStrip[21]-gpp::Vector3f(-1.9,-0.5, -25.0)

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