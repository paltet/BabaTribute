#include "HowTo.h"
#include "Game.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>


HowTo::HowTo()
{
	keke = nullptr;
	rock = nullptr;
	is = nullptr;
	red = nullptr;

	for (int i = 0; i < 4; i++) {
		rocks[i] = nullptr;
	}
}


HowTo::~HowTo()
{
	if (keke != nullptr) delete keke;
	if (rock != nullptr) delete rock;
	if (is != nullptr) delete is;
	if (red != nullptr) delete red;

	for (int i = 0; i < 4; i++) {
		if (rocks[i] != nullptr) delete rocks[i];
	}
}

void HowTo::init() {
	currentTime = 0.f;
	ret = false;
	retTime = NULL;
	
	initShaders();
	tex.loadFromFile("images/baba.png", TEXTURE_PIXEL_FORMAT_RGBA);

	loadKeke();
	loadRock();
	loadIs();
	loadRed();
	loadRocks();

	if (!back.init("fonts/INVASION2000.ttf"))
		//if(!text.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
}

void HowTo::update(int deltaTime) {
	currentTime += deltaTime;
	/*
	keke->update(deltaTime);
	rock->update(deltaTime);
	is->update(deltaTime);
	red->update(deltaTime);
	*/
	for (int i = 0; i < 4; i++) {
		rocks[i]->update(deltaTime);
	}

	if (Game::instance().getKey(13)) {
		retTime = currentTime;
	}

	if (retTime != NULL && currentTime > retTime + MARGIN) ret = true;
}

void HowTo::render() {

	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::mat4(1.f);
	texProgram.setUniformMatrix4f("modelview", modelview);

	for (int i = 0; i < 4; i++) rocks[i]->render();

	back.render("PRESS ENTER TO GO BACK", glm::vec2(HOWTO_TEXT_SIZE, CAMERA_HEIGHT - HOWTO_TEXT_SIZE), HOWTO_TEXT_SIZE, glm::vec4(1.f, 1.f, 1.f, 1.f));
}

void HowTo::initShaders() {
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

void HowTo::loadKeke() {

}

void HowTo::loadRock() {

}

void HowTo::loadIs() {

}

void HowTo::loadRed() {

}

void HowTo::loadRocks() {
	for (int i = 0; i < 4; i++) {
		rocks[i] = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f / 32.f, 1.f / 66.f), &tex, &texProgram);
		rocks[i]->setNumberAnimations(1);

		rocks[i]->addKeyframe(0, glm::vec2(15.f / 32.f, 21.f / 66.f));
		rocks[i]->addKeyframe(0, glm::vec2(15.f / 32.f, 22.f / 66.f));
		rocks[i]->addKeyframe(0, glm::vec2(15.f / 32.f, 23.f / 66.f));

		rocks[i]->setPosition(glm::vec2(CAMERA_WIDTH / 2 + 50*i, CAMERA_HEIGHT / 2));
		rocks[i]->changeAnimation(0);
	}
}