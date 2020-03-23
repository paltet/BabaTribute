#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include <vector>
#include "ShaderProgram.h"

#include "Player.h"
#include "PlayerText.h"

#include "Wall.h"
#include "WallText.h"

#include "Is.h"

#include "You.h"
#include "Win.h"

#include "Input.h"
#include "Texture.h"

#include <set>


typedef vector<vector<vector<Entity*>>> EntityMap;

class Scene
{
public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

	Input::KEY_STATE getButton(int key);

private:

	void initShaders();
	void updateMap(int deltaTime);
	void renderMap();

	bool look(int i, int j, direction d);
	void move(direction d);
	string getId(Entity* p);

private:

	float currentTime;
	ShaderProgram texProgram;
	glm::mat4 projection;
	Texture tex;

	void updateRules();
	string you;
	string youProp;
	string is;
	set<string> push;


	bool loadMap(const string &levelName);
	void loadLevel();
	int *grid;
	EntityMap map;
	float tileSize;
	glm::ivec2 mapSize;
};
#endif
