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
#include "Defeat.h"
#include "Push.h"
#include "Stop.h"

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
	void load(string levelFile);

	Input::KEY_STATE getButton(int key);

private:

	void initShaders();
	void updateMap(int deltaTime);
	void renderMap();

	bool look(int i, int j, direction d);
	void move(direction d);
	bool moveTile(int i, int j, int k, direction d, set<Entity*> &moved);
	string getId(Entity* p);

private:

	float currentTime;
	ShaderProgram texProgram;
	glm::mat4 projection;
	Texture tex;
	string level;

	void updateRules();
	string youProp;
	string pushProp;
	string winProp;
	string defeatProp;
	string stopProp;

	string is;
	string eat;

	set<string> push;
	set<string> defaultPush;
	set<string> you;
	set<string> win;
	set<string> defeat;
	set<string> stop;


	bool loadMap(const string &levelName);
	void loadLevel();
	int *grid;
	EntityMap map;
	float tileSize;
	glm::ivec2 mapSize;
};
#endif
