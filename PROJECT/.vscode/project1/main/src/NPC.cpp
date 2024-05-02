#include <./include/NPC.h>

NPC::~NPC()
{
    delete this;
}

NPC::NPC(TYPE type, float zPosition) : GameObject(type)
{
    switch (type)
    {
    case gpp::TYPE::RED:
        this->position = vec3(0.0f, 0.0f, -10.0f-zPosition);
        break;
    case gpp::TYPE::BLUE:
        this->position = vec3(-4.0f, 0.0f, -10.0f-zPosition);
        break;
    case gpp::TYPE::GREEN:
        this->position = vec3(4.0f, 0.0f, -10.0f- zPosition);
        break;
    default:
        break;
    }
    this->startPos = this->position;
}


bool NPC::checkCollision(GameObject* obj)
{
    vec3 pos1 = obj->getPosition();
    vec3 pos2 = this->getPosition();

    // Calculate the distances between the centers of the two cubes
    float distX = abs(pos1.x - pos2.x);
    float distY = abs(pos1.y - pos2.y);
    float distZ = abs(pos1.z - pos2.z);

    // Calculate the minimum distance needed for collision
    float minDist = 2.0f; // Sum of the lengths of the sides of two cubes

    // Check if the cubes are colliding
    if (distX < minDist && distY < minDist && distZ < minDist) {
        if (this->getType() != obj->getType())
        {
            return true; // Collision detected
        }
    }

    return false; // No collision detected
}

vec3 NPC::getPosition()
{
    return position;
}

void NPC::setPosition(vec3 position)
{
    this->position = position;
    model = glm::translate(glm::mat4(1.0f), position);
}

mat4 NPC::getModelMatrix() { return this->model; }

void NPC::setModelMatrix(mat4 model) { this->model = model; }

mat4 NPC::getMVPMatrix() { return this->mvp; }

void NPC::setMVPMatrix(mat4 mvp) { this->mvp = mvp; }

GLfloat* NPC::getVertex() { return this->vertex; }

int NPC::getVertexCount() { return ARRAY_SIZE(vertex) / 3; }

GLfloat* NPC::getColor() { return this->colour; }

int NPC::getColorCount() { return ARRAY_SIZE(colours) / 4; }

GLfloat* NPC::getUV() { return this->uv; }

int NPC::getUVCount() { return ARRAY_SIZE(uv); }

GLfloat* NPC::getIndex() { return this->index; }

int NPC::getIndexCount() { return ARRAY_SIZE(index) / 3; }

TYPE NPC::getType() { return type; }


void NPC::update(double dt)
{
    vec3 translationVector(0.0f, 0.0f, 20.0f*dt);
    this->setModelMatrix(translate(this->getModelMatrix(), this->getPosition()));
    this->setModelMatrix(translate(this->getModelMatrix(), translationVector));
    this->setPosition(this->getPosition() + translationVector);


    if (this->position.z > 10)
    {
        isRenderable = false;
    }
}

void NPC::setOriginalPosition()
{
    this->position = this->startPos;
}
void NPC::setRenderable(bool r)
{
    isRenderable = r;
}
bool NPC::renderable()
{
    return isRenderable;
}