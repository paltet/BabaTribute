#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE

#include "Texture.h"
#include "ShaderProgram.h"
#include "Direction.h"
#include "Sprite.h"
#include <vector>

class Entity
{
public:
	void init(glm::vec2 pos, Texture &tex, ShaderProgram &program);
	void update(int deltaTime);
	void render();

	void move(direction d, float length);
	
	Sprite* sprite;
	virtual void setAnimations() = 0;
	virtual void setColor();
	glm::vec3 color;

	virtual string getIdReferred();

private:

	ShaderProgram sProgram;
	glm::vec2 position;
};

#endif