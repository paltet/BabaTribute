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

void Scene::init() {
	tileSize = CAMERA_WIDTH / 15.f;
	currentTime = 0.f;
	initShaders();
	tex.loadFromFile("images/baba.png", TEXTURE_PIXEL_FORMAT_RGBA);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);

	loadMap("levels/entities.txt");
	loadLevel();
}

void Scene::update(int deltaTime) {
	currentTime += deltaTime;

	updateRules();

	updateMap(deltaTime);

	/*
	if (getButton(GLUT_KEY_DOWN) == Input::KEY_PRESSED) {
		move(DOWN);
	}*/
}

void Scene::updateMap(int deltaTime) {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {

			if (map[i][j] != NULL) {
				map[i][j]->update(deltaTime);
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
}

void Scene::renderMap() {
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {

			if (map[i][j] != NULL) {
				map[i][j]->render();
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
	sstream >> mapSize.x >> mapSize.y;

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

	map = EntityMap(mapSize.y, vector<Entity*> (mapSize.x, nullptr));

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
					map[i][j] = p;
					break;
				}
			case 2:
				{
					Wall* w = new Wall();
					//move = typeid(*w).name();
					w->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j] = w;
					break;
				}
			case 6:
				{
					PlayerText* pt = new PlayerText();
					pt->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j] = pt;
					break;
				}
			case 7:
				{
					WallText* wt = new WallText();
					wt->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j] = wt;
					break;
				}
			case 11:
				{
					Is* ii = new Is();
					ii->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j] = ii;

					is = typeid(*ii).name();

					break;
				}
			case 13:
				{
					You* y = new You();
					y->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j] = y;
					youProp = typeid(*y).name();
					break;
				}
			case 14:
				{
					Win* win = new Win();
					win->init(glm::vec2(i*tileSize, j*tileSize), tex, texProgram);
					map[i][j] = win;
					break;
				}
			}
		}
	}
}

Input::KEY_STATE Scene::getButton(int key) {
	return Game::instance().input.getSpecialKey(key);
}

void Scene::updateRules() {


	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			if (map[i][j] != nullptr){

				string name;

				string id = typeid(*map[i][j]).name();
				if (id == is) {
					if (look(i, j, LEFT)) {
						if (map[i - 1][j] != nullptr) {
							name = map[i - 1][j]->getIdReferred();

							if (look(i, j, RIGHT)) {
								if (map[i + 1][j] != nullptr) {

									string prop = typeid(*map[i + 1][j]).name();
									if (prop == youProp)	you = name;
								}
							}

						}
					}
					if (look(i, j, UP)) {
						if (map[i][j - 1] != nullptr) {
							name = map[i][j - 1]->getIdReferred();

							if (look(i, j, DOWN)) {
								if (map[i][j + 1] != nullptr) {

									string prop = typeid(*map[i][j + 1]).name();
									if (prop == youProp)	you = name;
								}
							}

						}
					}
				}
			}
		}
	}
}

bool Scene::look(int i, int j, direction d) {

	if (map[i][j] == nullptr) return false;

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

void Scene::move(direction d) {

	EntityMap nMap;
	nMap = EntityMap(mapSize.y, vector<Entity*>(mapSize.x, nullptr));

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			if (map[i][j] != nullptr) {

				string tile = typeid(*map[i][j]).name();
				if (tile == you && look(i, j, d)) {
					switch (d) {
						case DOWN:
							if (map[i][j+1] == nullptr) {
								map[i][j]->move(DOWN, tileSize);
								nMap[i][j + 1] = map[i][j];
								map[i][j] = nullptr;
							}
							else {
								nMap[i][j] = map[i][j];
							}
							break;
					}
				}
				else {
					if (map[i][j] != nullptr) nMap[i][j] = map[i][j];
				}
			}
		}
	}
	map = nMap;
}