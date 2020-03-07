#ifndef _HOWTO_INCLUDE
#define _HOWTO_INCLUDE

#include "Text.h"
#include "Sprite.h"
#include "ShaderProgram.h"


#define HOWTO_TEXT_SIZE 16
#define MARGIN 200
#define SPRITE_SIZE 48

class HowTo
{
public:
	HowTo();
	~HowTo();

	void init();
	void update(int deltaTime);
	void render();

public:
	bool ret;

private:
	void initShaders();

	void loadKeke();
	void loadRock();
	void loadIs();
	void loadRed();
	void loadRocks();

private:
	float currentTime, retTime;

	Text back;
	Sprite *keke, *rock, *is, *red;
	Sprite *rocks[4];

	Texture tex;
	ShaderProgram texProgram;
	
	glm::mat4 projection;
};
#endif
