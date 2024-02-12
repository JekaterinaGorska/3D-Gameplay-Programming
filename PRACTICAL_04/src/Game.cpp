#include <./include/Game.h>

Game::Game() : window(VideoMode(800, 600), "Vertex Array OpenGL Cube")
{

}

Game::~Game() {}


// Vertices for one Triangle
float vertices[] = {
					//front face
					 1.0f, 1.0f, 1.0f, 
					1.0f, -1.0f, 1.0f, 
					1.0f, 1.0f, 1.0f,
					-1.0f, 1.0f, 1.0f,
					//back face
					-1.0f, -1.0f, -1.0f,
					-1.0f, 1.0f, -1.0f,
					1.0f, 1.0f, -1.0f,
					1.0f, -1.0f, -1.0f,
					//top face
					-1.0f, 1.0f, -1.0f,
					-1.0f, 1.0f, 1.0f,
					1.0f, 1.0f, 1.0f,
					1.0f, 1.0f, -1.0f,
					//bottom face
					-1.0f, -1.0f, -1.0f,
					1.0f, -1.0f, -1.0f,
					1.0f, -1.0f, 1.0f,
					-1.0f, -1.0f, 1.0f,
					//right face
					1.0f, -1.0f, -1.0f,
					1.0f, 1.0f, -1.0f,
					1.0f, 1.0f, 1.0f, 
					1.0f, -1.0f, 1.0f,
					//left face
					-1.0f, -1.0f, -1.0f,
					-1.0f, -1.0f, 1.0f,
					-1.0f, 1.0f, 1.0f,
					-1.0f, 1.0f, -1.0f};

// Colors for those vertices
float colors[] = { 
					//front face
					1.0f, 0.0f, 0.0f, 1.0f, 
					0.0f, 1.0f, 0.0f, 1.0f,
					0.0f, 0.0f, 1.0f, 1.0f,
					1.0f, 1.0f, 0.0f, 1.0f,
					//back face
					1.0f, 0.0f, 1.0f, 1.0f,
					0.0f, 1.0f, 1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f, 0.0f, 1.0f, 1.0f,
					//top face
					0.0f, 1.0f, 0.0f, 1.0f,
					0.0f, 1.0f, 1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					1.0f, 1.0f, 0.0f, 1.0f,
					//bottom face
					1.0f, 0.5f, 0.0f, 1.0f,
					1.0f, 0.5f, 1.0f, 1.0f,
					0.5f, 0.5f, 1.0f, 1.0f,
					0.5f, 0.5f, 0.0f, 1.0f,
					//right face
					1.0f, 0.0f, 1.0f, 1.0f,
					1.0f, 1.0f, 1.0f, 1.0f,
					0.0f, 1.0f, 1.0f, 1.0f,
					0.0f, 0.0f, 1.0f, 1.0f,
					//left face
					0.0f, 0.0f, 0.0f, 1.0f,
					1.0f, 0.0f, 0.0f, 1.0f,
					1.0f, 1.0f, 0.0f, 1.0f,
					0.0f, 1.0f, 0.0f, 1.0f };
					
					 
// Index to be drawn
unsigned int vertex_index[] = { 0, 1, 2 };

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

void Game::initialize()
{
	isRunning = true;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, &vertices);
	glColorPointer(3, GL_FLOAT, 0, &colors);

	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(0.1f, 1.0f, 1.0f, 0.0f);

	glDrawArrays(GL_QUADS, 0, 24);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, &vertex_index);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}