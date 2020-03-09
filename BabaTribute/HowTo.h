#ifndef _HOWTO_INCLUDE
#define _HOWTO_INCLUDE

#include "Text.h"
#include "Sprite.h"
#include "ShaderProgram.h"


#define HOWTO_TEXT_SIZE 16
#define MARGIN 200
#define SPRITE_SIZE 40

class HowTo
{
public:
	HowTo();
	~HowTo();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();

	void loadKeke();
	void loadRock();
	void loadIs();
	void loadRed();
	void loadRocks();
	void loadExpression();
	void loadKeys();

private:
	float currentTime, retTime, animTime;

	Text text;
	Sprite *keke, *rock, *is, *red, *expression;
	Sprite *rocks[3];

	Sprite *keys;

	enum { KEKE_SLEEP, KEKE_WALKS, KEKE_LOOKS };

	enum {SLEEP, WALKS_1, WALKS_2, LOOKS};
	int animation_state;

	Texture tex;
	Texture keyTex;
	ShaderProgram texProgram;
	
	glm::mat4 projection;
};
#endif
