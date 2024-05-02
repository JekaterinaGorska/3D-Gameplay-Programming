#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
using namespace gpp;
using namespace glm;
using namespace std;
class Player : public GameObject
{
public:
	~Player();
	Player(TYPE type);
	bool checkCollision(GameObject* obj);
	vec3 getPosition();
	void setPosition(vec3 position);
	mat4 getModelMatrix();
	void setModelMatrix(mat4 model);
	mat4 getMVPMatrix();
	void setMVPMatrix(mat4 model);
	GLfloat* getVertex();
	int getVertexCount();
	GLfloat* getColor();
	int getColorCount();
	GLfloat* getUV();
	int getUVCount();
	GLfloat* getIndex();
	int getIndexCount();
	TYPE getType();
	bool isAlive();
	void kill();
	void revive();

	void update(double dt);

	void moveRight();
	void moveLeft();

	void handleKeyInputs();
private:
	bool alive{ true };
	double dt;
	const float speed = 15.0f;
};

#endif
