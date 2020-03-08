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
	expression = nullptr;
	keys = nullptr;

	for (int i = 0; i < 3; i++) {
		rocks[i] = nullptr;
	}
}


HowTo::~HowTo()
{
	if (keke != nullptr) delete keke;
	if (rock != nullptr) delete rock;
	if (is != nullptr) delete is;
	if (red != nullptr) delete red;
	if (expression != nullptr) delete expression;
	if (keys != nullptr) delete keys;

	for (int i = 0; i < 3; i++) {
		if (rocks[i] != nullptr) delete rocks[i];
	}
}

void HowTo::init() {
	currentTime = 0.f;
	animTime = 0.f;
	ret = false;
	retTime = NULL;
	animation_state = SLEEP;
	
	initShaders();
	tex.loadFromFile("images/baba.png", TEXTURE_PIXEL_FORMAT_RGBA);
	keyTex.loadFromFile("images/keys.png", TEXTURE_PIXEL_FORMAT_RGBA);

	loadKeke();
	loadRock();
	loadIs();
	loadRed();
	loadExpression();
	loadRocks();
	loadKeys();

	if (!text.init("fonts/INVASION2000.ttf"))
		//if(!text.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;

	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
}

void HowTo::update(int deltaTime) {
	currentTime += deltaTime;
	animTime += deltaTime;

	if (animTime >= 700) {
		animTime = 0.f;
		if (animation_state == LOOKS) animation_state = SLEEP;
		else animation_state++;
	}
	

	if (Game::instance().getKey(13)) {
		retTime = currentTime;
	}

	if (retTime != NULL && currentTime > retTime + MARGIN) ret = true;

	keke->update(deltaTime);
	rock->update(deltaTime);
	is->update(deltaTime);
	red->update(deltaTime);
	expression->update(deltaTime);
	for (int i = 0; i < 3; i++) {
		rocks[i]->update(deltaTime);
	}
	keys->update(deltaTime);

	switch (animation_state) {
	case SLEEP:
		if (keke->animation() != KEKE_SLEEP) keke->changeAnimation(KEKE_SLEEP);
		keke->setPosition(glm::vec2(CAMERA_WIDTH - SPRITE_SIZE * 7, CAMERA_HEIGHT / 2 + SPRITE_SIZE * 3));
		red->setPosition(glm::vec2(CAMERA_WIDTH - SPRITE_SIZE * 4, CAMERA_HEIGHT / 2 + SPRITE_SIZE * 3));

		expression->setPosition(glm::vec2(CAMERA_WIDTH - SPRITE_SIZE * 7, CAMERA_HEIGHT / 2 + SPRITE_SIZE * 2));
		expression->changeAnimation(0);
		break;
	case WALKS_1:
		keke->setPosition(glm::vec2(CAMERA_WIDTH - SPRITE_SIZE * 6, CAMERA_HEIGHT / 2 + SPRITE_SIZE * 3));
		if (keke->animation() != KEKE_WALKS) keke->changeAnimation(KEKE_WALKS);
		break;
	case WALKS_2:
		if (keke->animation() != KEKE_WALKS) keke->changeAnimation(KEKE_WALKS);
		keke->setPosition(glm::vec2(CAMERA_WIDTH - SPRITE_SIZE * 5, CAMERA_HEIGHT / 2 + SPRITE_SIZE * 3));
		break;
	case LOOKS:

		expression->setPosition(glm::vec2(CAMERA_WIDTH - SPRITE_SIZE * 4, CAMERA_HEIGHT / 2 + SPRITE_SIZE * 2));
		expression->changeAnimation(1);

		if (keke->animation() != KEKE_LOOKS) keke->changeAnimation(KEKE_LOOKS);
		keke->setPosition(glm::vec2(CAMERA_WIDTH - SPRITE_SIZE * 4, CAMERA_HEIGHT / 2 + SPRITE_SIZE * 3));
		red->setPosition(glm::vec2(CAMERA_WIDTH - SPRITE_SIZE * 3, CAMERA_HEIGHT / 2 + SPRITE_SIZE * 3));
		break;
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
	keke->render();
	keys->render();

	for (int i = 0; i < 3; i++) {
		if (animation_state == LOOKS) texProgram.setUniform4f("color", 1.0f, 0.0f, 0.0f, 1.0f);
		rocks[i]->render();
	}
	texProgram.setUniform4f("color", 1.0f, 0.0f, 0.0f, 1.0f);
	red->render();

	if (animation_state == LOOKS || animation_state == SLEEP) {
		texProgram.setUniform4f("color", 1.0f, 1.0f, 0.0f, 1.0f);
		expression->render();
	}

	text.render("USE ARROW KEYS TO MOVE", glm::vec2(HOWTO_TEXT_SIZE*2, HOWTO_TEXT_SIZE*2), HOWTO_TEXT_SIZE-2, glm::vec4(1.f, 1.f, 1.f, 1.f));
	text.render("CONCATENATE EXPRESSIONS TO ADVANCE", glm::vec2(HOWTO_TEXT_SIZE*2, CAMERA_HEIGHT / 2 - HOWTO_TEXT_SIZE / 2), HOWTO_TEXT_SIZE-2, glm::vec4(1.f, 1.f, 1.f, 1.f));
	text.render("PRESS ENTER TO GO BACK", glm::vec2(CAMERA_WIDTH/3 - HOWTO_TEXT_SIZE, CAMERA_HEIGHT - HOWTO_TEXT_SIZE*2), HOWTO_TEXT_SIZE, glm::vec4(1.f, 1.f, 1.f, 1.f));
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

	keke = Sprite::createSprite(glm::ivec2(SPRITE_SIZE, SPRITE_SIZE), glm::vec2(1.f / 32.f, 1.f / 66.f), &tex, &texProgram);
	keke->setNumberAnimations(3);

	keke->setAnimationSpeed(KEKE_SLEEP, 8);
	keke->setAnimationSpeed(KEKE_WALKS, 8);
	keke->setAnimationSpeed(KEKE_LOOKS, 8);

	keke->addKeyframe(KEKE_SLEEP, glm::vec2(0.f / 32.f, 3.f / 66.f));
	keke->addKeyframe(KEKE_SLEEP, glm::vec2(0.f / 32.f, 4.f / 66.f));
	keke->addKeyframe(KEKE_SLEEP, glm::vec2(0.f / 32.f, 5.f / 66.f));

	keke->addKeyframe(KEKE_WALKS, glm::vec2(1.f / 32.f, 3.f / 66.f));
	keke->addKeyframe(KEKE_WALKS, glm::vec2(2.f / 32.f, 3.f / 66.f));
	keke->addKeyframe(KEKE_WALKS, glm::vec2(3.f / 32.f, 3.f / 66.f));
	keke->addKeyframe(KEKE_WALKS, glm::vec2(4.f / 32.f, 3.f / 66.f));

	keke->addKeyframe(KEKE_LOOKS, glm::vec2(11.f / 32.f, 3.f / 66.f));
	keke->addKeyframe(KEKE_LOOKS, glm::vec2(11.f / 32.f, 4.f / 66.f));
	keke->addKeyframe(KEKE_LOOKS, glm::vec2(11.f / 32.f, 5.f / 66.f));


	keke->changeAnimation(KEKE_SLEEP);
	keke->setPosition(glm::vec2(CAMERA_WIDTH - SPRITE_SIZE * 7, CAMERA_HEIGHT / 2 + SPRITE_SIZE * 3));
	
}

void HowTo::loadRock() {
	rock = Sprite::createSprite(glm::ivec2(SPRITE_SIZE, SPRITE_SIZE), glm::vec2(1.f / 32.f, 1.f / 66.f), &tex, &texProgram);
	rock->setNumberAnimations(1);

	rock->setAnimationSpeed(0, 8);

	rock->addKeyframe(0, glm::vec2(11.f / 32.f, 33.f / 66.f));
	rock->addKeyframe(0, glm::vec2(11.f / 32.f, 34.f / 66.f));
	rock->addKeyframe(0, glm::vec2(11.f / 32.f, 35.f / 66.f));

	rock->setPosition(glm::vec2(CAMERA_WIDTH - SPRITE_SIZE*3, CAMERA_HEIGHT/2+SPRITE_SIZE));
	rock->changeAnimation(0);
}

void HowTo::loadIs() {
	is = Sprite::createSprite(glm::ivec2(SPRITE_SIZE, SPRITE_SIZE), glm::vec2(1.f / 32.f, 1.f / 66.f), &tex, &texProgram);
	is->setNumberAnimations(1);

	is->setAnimationSpeed(0, 8);

	is->addKeyframe(0, glm::vec2(18.f / 32.f, 30.f / 66.f));
	is->addKeyframe(0, glm::vec2(18.f / 32.f, 31.f / 66.f));
	is->addKeyframe(0, glm::vec2(18.f / 32.f, 32.f / 66.f));

	is->setPosition(glm::vec2(CAMERA_WIDTH - SPRITE_SIZE * 3, CAMERA_HEIGHT / 2 + SPRITE_SIZE*2));
	is->changeAnimation(0);
}

void HowTo::loadRed() {
	red = Sprite::createSprite(glm::ivec2(SPRITE_SIZE, SPRITE_SIZE), glm::vec2(1.f / 32.f, 1.f / 66.f), &tex, &texProgram);
	red->setNumberAnimations(1);

	red->setAnimationSpeed(0, 8);

	red->addKeyframe(0, glm::vec2(3.f / 32.f, 42.f / 66.f));
	red->addKeyframe(0, glm::vec2(3.f / 32.f, 43.f / 66.f));
	red->addKeyframe(0, glm::vec2(3.f / 32.f, 44.f / 66.f));

	red->setPosition(glm::vec2(CAMERA_WIDTH - SPRITE_SIZE * 4, CAMERA_HEIGHT / 2 + SPRITE_SIZE*3));
	red->changeAnimation(0);
	
}

void HowTo::loadRocks() {
	for (int i = 0; i < 3; i++) {
		rocks[i] = Sprite::createSprite(glm::ivec2(SPRITE_SIZE, SPRITE_SIZE), glm::vec2(1.f / 32.f, 1.f / 66.f), &tex, &texProgram);
		rocks[i]->setNumberAnimations(1);

		rocks[i]->setAnimationSpeed(0, 8);

		rocks[i]->addKeyframe(0, glm::vec2(15.f / 32.f, 21.f / 66.f));
		rocks[i]->addKeyframe(0, glm::vec2(15.f / 32.f, 22.f / 66.f));
		rocks[i]->addKeyframe(0, glm::vec2(15.f / 32.f, 23.f / 66.f));

		rocks[i]->setPosition(glm::vec2(SPRITE_SIZE*2, CAMERA_HEIGHT / 2 + SPRITE_SIZE*(i+1)));
		rocks[i]->changeAnimation(0);
	}
}

void HowTo::loadExpression() {
	expression = Sprite::createSprite(glm::ivec2(SPRITE_SIZE, SPRITE_SIZE), glm::vec2(1.f / 32.f, 1.f / 66.f), &tex, &texProgram);
	expression->setNumberAnimations(2);

	expression->setAnimationSpeed(0, 1);
	expression->setAnimationSpeed(1, 1);

	expression->addKeyframe(0, glm::vec2(28.f / 32.f, 44.f / 66.f));
	expression->addKeyframe(1, glm::vec2(29.f / 32.f, 44.f / 66.f));
}

void HowTo::loadKeys() {
	keys = Sprite::createSprite(glm::ivec2(SPRITE_SIZE*5, SPRITE_SIZE*3), glm::vec2(1.f, 1.f), &keyTex, &texProgram);
	keys->setNumberAnimations(1);
	keys->setAnimationSpeed(0, 1);
	keys->addKeyframe(0, glm::vec2(0.f, 0.f));
	keys->changeAnimation(0);
	keys->setPosition(glm::vec2(CAMERA_WIDTH / 2 - SPRITE_SIZE*2.5f, HOWTO_TEXT_SIZE * 4));
}