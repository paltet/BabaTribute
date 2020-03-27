#include "Credits.h"
#include "Game.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>

Credits::Credits() {
	sprite = nullptr;
}

Credits::~Credits() {
	if (sprite != nullptr) sprite = nullptr;
}

void Credits::init() {
	initShaders();
	currentTime = 0.f;
	tex.loadFromFile("images/baba.png", TEXTURE_PIXEL_FORMAT_RGBA);
	if (!text.init("fonts/INVASION2000.ttf"))
		//if(!text.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);

	sprite = Sprite::createSprite(glm::vec2(64.f, 64.f), glm::vec2(1.f / 32.f, 1.f / 66.f), &tex, &texProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 4);

	sprite->addKeyframe(0, glm::vec2(10.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(10.f / 32.f, 4.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(10.f / 32.f, 5.f / 66.f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(CAMERA_WIDTH - 64.f * 2, CAMERA_WIDTH - 128.f));
}

void Credits::update(int deltaTime) {
	currentTime += deltaTime;
	sprite->update(deltaTime);
}

void Credits::render() {

	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	//0.054, 0.356, 0.505

	modelview = glm::mat4(1.f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	sprite->render();
	
	text.render("JOAN MUNTANER", glm::vec2(CAMERA_WIDTH / 5 - CREDITS_TEXT_SIZE, CAMERA_HEIGHT / 2 - 32.f - 25.f), CREDITS_TEXT_SIZE, glm::vec4(1.f, 1.f, 1.f, 1.f));
	text.render("AND", glm::vec2(CAMERA_WIDTH / 5 - CREDITS_TEXT_SIZE, CAMERA_HEIGHT / 2 - 25.f), CREDITS_TEXT_SIZE / 2, glm::vec4(1.f, 1.f, 1.f, 1.f));
	text.render("PAU ALTET", glm::vec2(CAMERA_WIDTH / 5 - CREDITS_TEXT_SIZE, CAMERA_HEIGHT / 2 + 16.f), CREDITS_TEXT_SIZE, glm::vec4(1.f, 1.f, 1.f, 1.f));

	text.render("PRESS ENTER TO GO BACK", glm::vec2(CAMERA_WIDTH / 3 - CREDITS_TEXT_SIZE, CAMERA_HEIGHT - CREDITS_TEXT_SIZE / 2), CREDITS_TEXT_SIZE / 2, glm::vec4(1.f, 1.f, 1.f, 1.f));
}

void Credits::initShaders() {
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