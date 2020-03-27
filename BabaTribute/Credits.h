#ifndef _CREDITS_INCLUDE
#define _CREDITS_INCLUDE

#include "Text.h"
#include "ShaderProgram.h"
#include "Sprite.h"

#define CREDITS_TEXT_SIZE 32

class Credits
{
public:

	Credits();
	~Credits();

	void init();
	void update(int deltaTime);
	void render();

private:

	void initShaders();
	float currentTime;
	ShaderProgram texProgram;
	Texture tex;
	Sprite* sprite;
	Text text;
	glm::mat4 projection;

};
#endif

