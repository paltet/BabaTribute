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

	if (Game::instance().getKey(13)) {
		retTime = currentTime;
	}

	if (retTime != NULL && currentTime > retTime + MARGIN) ret = true;

	//keke->update(deltaTime);

	rock->update(deltaTime);
	is->update(deltaTime);
	red->update(deltaTime);
	for (int i = 0; i < 4; i++) {
		rocks[i]->update(deltaTime);
	}

}

void HowTo::render() {

	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	modelview = glm::mat4(1.f);
	texProgram.setUniformMatrix4f("modelview", modelview);

	rock->render();
	is->render();
	for (int i = 0; i < 4; i++) rocks[i]->render();
	texProgram.setUniform4f("color", 1.0f, 0.0f, 0.0f, 1.0f);
	red->render();

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
	rock = Sprite::createSprite(glm::ivec2(SPRITE_SIZE, SPRITE_SIZE), glm::vec2(1.f / 32.f, 1.f / 66.f), &tex, &texProgram);
	rock->setNumberAnimations(1);

	rock->setAnimationSpeed(0, 8);

	rock->addKeyframe(0, glm::vec2(11.f / 32.f, 33.f / 66.f));
	rock->addKeyframe(0, glm::vec2(11.f / 32.f, 34.f / 66.f));
	rock->addKeyframe(0, glm::vec2(11.f / 32.f, 35.f / 66.f));

	rock->setPosition(glm::vec2(CAMERA_WIDTH / 2, 0));
	rock->changeAnimation(0);
}

void HowTo::loadIs() {
	is = Sprite::createSprite(glm::ivec2(SPRITE_SIZE, SPRITE_SIZE), glm::vec2(1.f / 32.f, 1.f / 66.f), &tex, &texProgram);
	is->setNumberAnimations(1);

	is->setAnimationSpeed(0, 8);

	is->addKeyframe(0, glm::vec2(18.f / 32.f, 30.f / 66.f));
	is->addKeyframe(0, glm::vec2(18.f / 32.f, 31.f / 66.f));
	is->addKeyframe(0, glm::vec2(18.f / 32.f, 32.f / 66.f));

	is->setPosition(glm::vec2(CAMERA_WIDTH / 2, 40));
	is->changeAnimation(0);
}

void HowTo::loadRed() {
	red = Sprite::createSprite(glm::ivec2(SPRITE_SIZE, SPRITE_SIZE), glm::vec2(1.f / 32.f, 1.f / 66.f), &tex, &texProgram);
	red->setNumberAnimations(1);

	red->setAnimationSpeed(0, 8);

	red->addKeyframe(0, glm::vec2(3.f / 32.f, 42.f / 66.f));
	red->addKeyframe(0, glm::vec2(3.f / 32.f, 43.f / 66.f));
	red->addKeyframe(0, glm::vec2(3.f / 32.f, 44.f / 66.f));

	red->setPosition(glm::vec2(CAMERA_WIDTH / 2, 80));
	red->changeAnimation(0);
	
}

void HowTo::loadRocks() {
	for (int i = 0; i < 4; i++) {
		rocks[i] = Sprite::createSprite(glm::ivec2(SPRITE_SIZE, SPRITE_SIZE), glm::vec2(1.f / 32.f, 1.f / 66.f), &tex, &texProgram);
		rocks[i]->setNumberAnimations(1);

		rocks[i]->setAnimationSpeed(0, 8);

		rocks[i]->addKeyframe(0, glm::vec2(15.f / 32.f, 21.f / 66.f));
		rocks[i]->addKeyframe(0, glm::vec2(15.f / 32.f, 22.f / 66.f));
		rocks[i]->addKeyframe(0, glm::vec2(15.f / 32.f, 23.f / 66.f));

		rocks[i]->setPosition(glm::vec2(CAMERA_WIDTH / 2 + 50*i, CAMERA_HEIGHT / 2));
		rocks[i]->changeAnimation(0);
	}
}