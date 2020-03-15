#include "Scene.h"
#include "Game.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>


Scene::Scene()
{
	//map = nullptr;
}


Scene::~Scene()
{
	//if (map != nullptr) map = nullptr;
}

void Scene::init() {
	currentTime = 0.f;
	initShaders();
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
}

void Scene::update(int deltaTime) {
	currentTime += deltaTime;
}

void Scene::render() {
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::mat4(1.f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	//map->render();
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

bool Scene::loadLevel(const string &levelFile) {

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

	map = new int[mapSize.x * mapSize.y];

	for (int j = 0; j < mapSize.y; j++) {
		for (int i = 0; i < mapSize.x; i++) {
			fin.get(tile);
			if (tile == ' ') map[j * mapSize.x + i] = 0;
			else map[j * mapSize.x + i] = tile;
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}
	fin.close();

	return true;
}