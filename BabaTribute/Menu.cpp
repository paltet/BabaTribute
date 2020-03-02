#include "Menu.h"
#include "Game.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>

Menu::Menu()
{
	pointer = nullptr;
}

Menu::~Menu()
{
	if (pointer != nullptr) delete pointer;
}

void Menu::init() {
	currentTime = 0.f;
	state = PLAY;

	initShaders();

	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(128.f, 128.f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f )};

	pointer = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	tex.loadFromFile("images/icon.png", TEXTURE_PIXEL_FORMAT_RGBA);

	if (!text.init("fonts/INVASION2000.ttf"))
		//if(!text.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
}

void Menu::update(int deltaTime) {
	currentTime += deltaTime;

	if (currentTime > margin) {
		if (Game::instance().getSpecialKey(GLUT_KEY_UP))
		{
			if (state != PLAY) state--;
			currentTime = 0;
		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
		{
			if (state != EXIT) state++;
			currentTime = 0;
		}
	}
	if (Game::instance().getKey(13) && state == EXIT) {
		exit(0);
	}
}

void Menu::render() {
	glm::mat4 modelview;

	texProgram.use();

	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(CAMERA_WIDTH / 2 -130 - 40, CAMERA_HEIGHT / 3 - 8 + 50 * state, 0));
	modelview = glm::scale(modelview, glm::vec3(40.f / 128.f, 40.f / 128.f, 0));
	modelview = glm::translate(modelview, glm::vec3(-64.f, -64.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	pointer->render(tex);

	for (int i = 0; i < 4; i++) {
		text.render(options[i], glm::vec2(CAMERA_WIDTH / 2 - 130, CAMERA_HEIGHT/3 + 50*i), TEXT_SIZE, glm::vec4(1.f, 1.f, 1.f, 1.f));
	}
}

void Menu::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/simple.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/simple.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	simpleProgram.init();
	simpleProgram.addShader(vShader);
	simpleProgram.addShader(fShader);
	simpleProgram.link();
	if (!simpleProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << simpleProgram.log() << endl << endl;
	}
	simpleProgram.bindFragmentOutput("outColor");

	vShader.free();
	fShader.free();
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
}

