#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE


#include "ShaderProgram.h"
#include "Text.h"
#include "Sprite.h"

#define MENU_TEXT_SIZE 32

class Menu
{
public:
	Menu();
	~Menu();

	void init();
	void update(int deltaTime);
	void render();

	int state;

private:
	void initShaders();

private:
	float currentTime;

	Text text;
	Sprite *pointer;
	Texture tex;

	enum {PLAY, HOWTO, ABOUT, EXIT};

	ShaderProgram texProgram;
	glm::mat4 projection;
	string options[4] = { "PLAY", "HOW TO PLAY", "CREDITS", "EXIT" };
};

#endif