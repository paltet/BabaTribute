#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include "ShaderProgram.h"
#include "TileMap.h"

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

	TileMap *map;
	ShaderProgram texProgram;

	glm::mat4 projection;
};
#endif
