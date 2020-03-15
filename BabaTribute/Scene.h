#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include "ShaderProgram.h"


class Scene
{
public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:

	void initShaders();

private:

	float currentTime;
	ShaderProgram texProgram;
	glm::mat4 projection;

	bool loadLevel(const string &levelName);
	int *map;

	glm::vec2 tileSize;

	Sprite* entities[];
};
#endif
