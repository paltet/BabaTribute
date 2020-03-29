#include "Scene.h"
#include "Game.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include <iterator>

using namespace std;


Scene::Scene()
{
	//map = nullptr;
}


Scene::~Scene()
{
	//if (map != nullptr) map = nullptr;
}

void Scene::init(string levelFile) {
	tileSize = CAMERA_WIDTH / 15.f;
	currentTime = 0.f;
	initShaders();
	tex.loadFromFile("images/baba_blank.png", TEXTURE_PIXEL_FORMAT_RGBA);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	
	if (!text.init("fonts/INVASION2000.ttf"))
		//if(!text.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;
	textTimer = 0.f;
	textLine = "";

	load(levelFile);
}

void Scene::load(string levelFile) {
	level = levelFile;
	loadMap(levelFile);
	loadLevel();
	updateRules();
}

bool Scene::update(int deltaTime) {
	currentTime += deltaTime;
	textTimer += deltaTime;

	updateMap(deltaTime);

	if (getButton(GLUT_KEY_DOWN) == Input::KEY_PRESSED) {
		if (nMoves > 0) {
			move(DOWN);
			nMoves--;
		}
		else sound("defeat");
	}
	if (getButton(GLUT_KEY_RIGHT) == Input::KEY_PRESSED) {
		if (nMoves > 0) {
			move(RIGHT);
			nMoves--;
		}
		else sound("defeat");
	}
	if (getButton(GLUT_KEY_LEFT) == Input::KEY_PRESSED) {
		if (nMoves > 0) {
			move(LEFT);
			nMoves--;
		}
		else sound("defeat");
	}
	if (getButton(GLUT_KEY_UP) == Input::KEY_PRESSED) {
		if (nMoves > 0) {
			move(UP);
			nMoves--;
		}
		else sound("defeat");
	}
	if (getButton(GLUT_KEY_F1) == Input::KEY_PRESSED) {
		load(level);
	}
	if (getButton(GLUT_KEY_F2) == Input::KEY_PRESSED) {
		int x = 0;
	}

	if (checkDefeat()) {
		load(level);
	}

	return checkWin();
}

void Scene::updateMap(int deltaTime) {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			for (int k = 0; k < map[i][j].size(); k++) {
				map[i][j][k]->update(deltaTime, nMoves);
			}
		}
	}
}

void Scene::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::mat4(1.f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	renderMap();
	if (textTimer <= 1000.f) text.render(textLine, glm::vec2(CAMERA_WIDTH/2 - 105, CAMERA_HEIGHT/2 - 25), 32, glm::vec4(1.f, 0.f, 0.f, 1.f));
	text.render(to_string(nMoves), glm::vec2(tileSize + 11, CAMERA_HEIGHT - tileSize - 11), 32, glm::vec4(0.f, 0.f, 1.f, 1.f));
}

void Scene::renderMap() {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			for (int k = 0; k < map[i][j].size(); k++ ){
				map[i][j][k]->render();
			}
		}
	}
}

void Scene::initShaders() {
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

bool Scene::loadMap(const string &levelFile) {

	ifstream fin;
	string line;
	stringstream sstream;
	char tile;

	fin.open(levelFile.c_str());
	if (!fin.is_open()) return false;

	getline(fin, line);
	if (line.compare(0, 5, "LEVEL") != 0) return false;

	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y >> nMoves;

	grid = new int[mapSize.x * mapSize.y];

	for (int i = 0; i < mapSize.x; i++) {
		for (int j = 0; j < mapSize.y; j++) {
			fin.get(tile);
			if (tile == ' ') grid[j * mapSize.x + i] = 0;
			else grid[j * mapSize.x + i] = tile - 96;
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();

	return true;
}

void Scene::loadLevel() {

	
	map = EntityMap(mapSize.y, vector<vector<Entity*>> (mapSize.x, vector<Entity*> (0)));

	int tile;

	for (int i = 0; i < mapSize.x; i++) {
		for (int j = 0; j < mapSize.y; j++) {

			tile = grid[i * mapSize.x + j];

			switch (tile) {
				case 1:
				{
					Player* p = new Player();
					//move = typeid(*w).name();
					p->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(p);
					break;
				}
				case 2:
				{
					Wall* w = new Wall();
					//move = typeid(*w).name();
					w->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(w);
					break;
				}
				case 3:
				{
					Flag* f = new Flag();
					f->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(f);
					break;
				}
				case 4:
				{
					Rock* r = new Rock();
					r->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(r);
					break;
				}
				case 5:
				{
					Fire* f = new Fire();
					f->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(f);
					break;
				}
				case 6:
				{
					PlayerText* pt = new PlayerText();
					pt->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(pt);
					break;
				}
				case 7:
				{
					WallText* wt = new WallText();
					wt->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(wt);
					break;
				}
				case 8:
				{
					FlagText* ft = new FlagText();
					ft->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(ft);
					break;
				}
				case 9:
				{
					RockText* rt = new RockText();
					rt->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(rt);
					break;
				}
				case 10:
				{
					FireText* ft = new FireText();
					ft->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(ft);
					break;
				}
				case 11:
				{
					Is* ii = new Is();
					ii->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(ii);
					is = typeid(*ii).name();
					break;
				}
				case 12:
				{
					Eat* ea = new Eat();
					ea->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(ea);
					eat = typeid(*ea).name();
					break;
				}
				case 13:
				{
					You* y = new You();
					y->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(y);
					youProp = getId(y);
					break;
				}
				case 14:
				{
					Win* win = new Win();
					win->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(win);
					winProp = getId(win);
					break;
				}
				case 15:
				{
					Defeat* defeat = new Defeat();
					defeat->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(defeat);
					defeatProp = getId(defeat);
					break;
				}
				case 16:
				{
					Push* push = new Push();
					push->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(push);
					pushProp = getId(push);
					break;
				}
				case 17:
				{
					Stop* stop = new Stop();
					stop->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(stop);
					stopProp = getId(stop);
					break;
				}
				case 18:
				{
					Unities* u = new Unities();
					u->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(u);
					break;
				}
				case 19:
				{
					Tens* u = new Tens();
					u->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(u);
					break;
				}
				case 20:
				{
					Fruit* u = new Fruit();
					u->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(u);
					break;
				}
				case 21:
				{
					FruitText* u = new FruitText();
					u->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j].push_back(u);
					break;
				}
			}

			if (tile > 5 && tile != 20 && map[i][j].size() > 0) defaultPush.insert(getId(map[i][j][0]));
		}
	}
}

Input::KEY_STATE Scene::getButton(int key) {
	return Game::instance().input.getSpecialKey(key);
}

string Scene::getId(Entity* e) {
	return typeid(*e).name();
}

bool Scene::look(int i, int j, direction d) {

	switch (d) {
	case DOWN:
		if (j >= mapSize.y - 1) return false;
		break;
	case RIGHT:
		if (i >= mapSize.x - 1) return false;
		break;
	case LEFT:
		if (i <= 0) return false;
		break;
	case UP:
		if (j <= 0) return false;
		break;
	}
	return true;
}

void Scene::updateRules() {

	string name, prop, name2;
	you.clear();
	win.clear();
	defeat.clear();
	push.clear();
	stop.clear();

	eaters.clear();

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			for (int k = 0; k < map[i][j].size(); k++) {
				string id = getId(map[i][j][k]);
				if (id == is) {																//If we find an is
					if (look(i, j, LEFT)){													//Look left for a name
						for (int l = 0; l < map[i - 1][j].size(); l++) {
							name = map[i - 1][j][l]->getIdReferred();
							if (name != "") {												//If we find a name
								if (look(i, j, RIGHT)) {									//Look right for something
									for (int m = 0; m < map[i + 1][j].size(); m++) {
										prop = getId(map[i + 1][j][m]);						//If we find something we switch for each prop
										if (prop == youProp) you.insert(name);
										else if (prop == winProp) win.insert(name);
										else if (prop == defeatProp) defeat.insert(name);
										else if (prop == pushProp) push.insert(name);
										else if (prop == stopProp) stop.insert(name);
									}
								}
							}
						}
					}
					if (look(i, j, UP)) {													//Look left for a name
						for (int l = 0; l < map[i][j - 1].size(); l++) {
							name = map[i][j - 1][l]->getIdReferred();
							if (name != "") {												//If we find a name
								if (look(i, j, DOWN)) {										//Look right for something
									for (int m = 0; m < map[i][j + 1].size(); m++) {
										prop = getId(map[i][j + 1][m]);						//If we find something we switch for each prop
										if (prop == youProp) you.insert(name);
										else if (prop == winProp) win.insert(name);
										else if (prop == defeatProp) defeat.insert(name);
										else if (prop == pushProp) push.insert(name);
										else if (prop == stopProp) stop.insert(name);
									}
								}
							}
						}
					}
				}
				else if (id == eat) {
					if (look(i, j, LEFT)) {													//Look left for a name
						for (int l = 0; l < map[i - 1][j].size(); l++) {
							name = map[i - 1][j][l]->getIdReferred();
							if (name != "") {												//If we find a name
								if (look(i, j, RIGHT)) {									//Look right for something
									for (int m = 0; m < map[i + 1][j].size(); m++) {
										name2 = map[i + 1][j][m]->getIdReferred();
										if (name2 != "") {
											eaters.insert(make_pair(name, name2));
										}
									}
								}
							}
						}
					}
					if (look(i, j, UP)) {													//Look left for a name
						for (int l = 0; l < map[i][j - 1].size(); l++) {
							name = map[i][j - 1][l]->getIdReferred();
							if (name != "") {												//If we find a name
								if (look(i, j, DOWN)) {									//Look right for something
									for (int m = 0; m < map[i][j + 1].size(); m++) {
										name2 = map[i][j + 1][m]->getIdReferred();
										if (name2 != "") {
											eaters.insert(make_pair(name, name2));
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	push.insert(defaultPush.begin(), defaultPush.end());
}

bool Scene::move(direction d) {
	
	//EntityMap nMap;
	//nMap = EntityMap(mapSize.y, vector<vector<Entity*>>(mapSize.x, vector<Entity*>(1, nullptr)));
	set<Entity*> moved;
	moved.clear();
	bool ret = false;
	hasPushed = false;
	hasEaten = false;
	hasStopped = false;


	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			for (int k = 0; k < map[i][j].size(); k++) {
				if (you.find(getId(map[i][j][k])) != you.end()) {
					if (moved.find(map[i][j][k]) == moved.end()) {
						if (moveTile(i, j, k, d, moved)) ret = true;
					}
				}
			}
		}
	}

	updateRules();
	if (hasStopped) sound("stop");
	else if (hasPushed) sound("push");
	else if (hasEaten) sound("eat");
	else if (ret) sound("move");
	else sound("stop");
	return ret;
}

bool Scene::moveTile(int i, int j, int k, direction d, set<Entity*> &moved) { 
	bool move = true;
	int newI = i, newJ = j;

	switch (d) {
	case DOWN:
		newJ++;
		break;
	case RIGHT:
		newI++;
		break;
	case LEFT:
		newI--;
		break;
	case UP:
		newJ--;
		break;
	}


	if (!look(i, j, d)) move = false;
	else {
		if (map[newI][newJ].size() == 0) move = true;
		else {
			for (int nk = 0; nk < map[newI][newJ].size(); nk++) {
				string nId = getId(map[newI][newJ][nk]);

				string id = getId(map[i][j][k]);
				if (eaters.find(make_pair(id, nId)) != eaters.end()) {
					hasEaten = true;
					nMoves += map[newI][newJ][nk]->eatMoves();
					map[newI][newJ].erase(map[newI][newJ].begin() + nk);
					move = true;
				}
				else if (eaters.find(make_pair(nId, id)) != eaters.end()) {
					map[i][j].erase(map[i][j].begin() + k);
					return true;
				}

				else if (stop.find(nId) != stop.end()) {
					move = false;
					hasStopped = true;
				} else if (push.find(nId) != push.end() || you.find(nId) != you.end()){
					move = moveTile(newI, newJ, nk, d, moved);
					if (move) hasPushed = true;
				}
			}
		}
	}
	if (move) {
		moved.insert(map[i][j][k]);
		map[i][j][k]->move(d, tileSize);
		map[newI][newJ].push_back(map[i][j][k]);
		map[i][j].erase(map[i][j].begin()+k);
	}
	return move;
}

bool Scene::checkDefeat() {

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			for (int k = 0; k < map[i][j].size(); k++) {
				string id = getId(map[i][j][k]);
				if (you.find(id) != you.end()) {
					for (int l = 0; l < map[i][j].size(); l++) {
						string id2 = getId(map[i][j][l]);
						if (defeat.find(id2) != defeat.end()) {
							sound("defeat");
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

bool Scene::checkWin() {

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			for (int k = 0; k < map[i][j].size(); k++) {
				string id = getId(map[i][j][k]);
				if (you.find(id) != you.end()) {
					for (int l = 0; l < map[i][j].size(); l++) {
						string id2 = getId(map[i][j][l]);
						if (win.find(id2) != win.end()) {
							sound("level");
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

void Scene::sound(string filename) {
	Game::instance().sound(filename);
}

void Scene::loadText(string line) {
	textTimer = 0;
	textLine = line;
}