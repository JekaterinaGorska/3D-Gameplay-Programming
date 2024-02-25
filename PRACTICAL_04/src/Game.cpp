#include <./include/Game.h>
#include <cmath>
#include <./include/Matrix3f.h>
//#include "Game.h"
Game::Game() : window(VideoMode(800, 600), "Vertex Array OpenGL Cube")
{
	 std::copy(std::begin(vertices), std::end(vertices), std::begin(vertices));
    std::copy(std::begin(colors), std::end(colors), std::begin(colors));
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

void Game::run() {
    initialize();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        rotate(5.0f);
                        break;
                    case sf::Keyboard::Right:
                        rotate(-5.0f);
                        break;
                    case sf::Keyboard::Up:
                        translate(0.0f, 0.1f, 0.0f);
                        break;
                    case sf::Keyboard::Down:
                        translate(0.0f, -0.1f, 0.0f);
                        break;
                    case sf::Keyboard::A:
                        scale(1.1f, 1.1f, 1.1f);
                        break;
                    case sf::Keyboard::Z:
                        scale(0.9f, 0.9f, 0.9f);
                        break;
                    default:
                        break;
                }
            }
        }
        update();
        render();
    }
}


void Game::initialize()
{
	//isRunning = true;

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
void Game::print(const float vertices[], int size)
{
	 for (int i = 0; i < size; i += 3) {
        std::cout << "Vertex " << i / 3 << ": (" << vertices[i] << ", " << vertices[i + 1] << ", " << vertices[i + 2] << ")" << std::endl;
    }
}
void Game::rotateX(float angle)
{
	   Matrix3f rotationMatrix = Matrix3f::rotateX(angle);
    for (int i = 0; i < 24; i += 3) {
        Vector3f vertex(vertices[i], vertices[i + 1], vertices[i + 2]);
        vertex = rotationMatrix * vertex;
        vertices[i] = vertex.x;
        vertices[i + 1] = vertex.y;
        vertices[i + 2] = vertex.z;
    }
}

void Game::rotateY(float angle)
{
	  Matrix3f rotationMatrix = Matrix3f::rotateY(angle);
    for (int i = 0; i < 24; i += 3) {
        Vector3f vertex(vertices[i], vertices[i + 1], vertices[i + 2]);
        vertex = rotationMatrix * vertex;
        vertices[i] = vertex.x;
        vertices[i + 1] = vertex.y;
        vertices[i + 2] = vertex.z;
    }
}

void Game::rotateZ(float angle)
{
	   Matrix3f rotationMatrix = Matrix3f::rotateZ(angle);
    for (int i = 0; i < 24; i += 3) {
        Vector3f vertex(vertices[i], vertices[i + 1], vertices[i + 2]);
        vertex = rotationMatrix * vertex;
        vertices[i] = vertex.x;
        vertices[i + 1] = vertex.y;
        vertices[i + 2] = vertex.z;
    }
}

void Game::translate(float dx, float dy, float dz)
{
}

void Game::scale(float sx, float sy, float sz)
{
}
