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
    bool isRunning = false;
    void initialize();
    void update();
    void draw();
    void unload();

   // gpp::Vector3f lineStrip[22];

    GLuint index;
    Clock clock;
    Time elapsed;

    float rotationAngle = 0.0f;
};