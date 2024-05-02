#ifndef NPC_H
#define NPC_H

#include "GameObject.h"
using namespace gpp;
using namespace glm;
using namespace std;
class NPC : public GameObject
{
public:
	~NPC();
	NPC(TYPE type, float zPosition);
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
	void update(double dt);
	void setOriginalPosition();
	void moveRight() {}
	void moveLeft() {}
	void setRenderable(bool r);
	bool renderable();
private:
	vec3 startPos;
	bool isRenderable{ true };
};

#endif