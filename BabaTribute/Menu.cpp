#include "Menu.h"
#include "Game.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>

using namespace std;


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
	tex.loadFromFile("images/baba.png", TEXTURE_PIXEL_FORMAT_RGBA);

	pointer = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f / 32.f, 1.f / 66.f), &tex, &texProgram);
	//pointer = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	pointer->setNumberAnimations(1);

	pointer->setAnimationSpeed(0, 4);
	pointer->addKeyframe(0, glm::vec2(0.f / 32.f, 3.f / 66.f));
	pointer->addKeyframe(0, glm::vec2(0.f / 32.f, 4.f / 66.f));
	pointer->addKeyframe(0, glm::vec2(0.f / 32.f, 5.f / 66.f));

	pointer->changeAnimation(0);
	pointer->setPosition(glm::vec2(CAMERA_WIDTH / 2, CAMERA_HEIGHT / 2));


	if (!text.init("fonts/INVASION2000.ttf") || !title.init("fonts/kirbyss.ttf"))
		//if(!text.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;



	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
}

void Menu::update(int deltaTime) {
	currentTime += deltaTime;
	pointer->update(deltaTime);
	pointer->setPosition(glm::vec2(CAMERA_WIDTH / 2 - 130 - 48, CAMERA_HEIGHT / 3 + 50 * state - 25 +50));

	if (Game::instance().input.getSpecialKey(GLUT_KEY_UP) == Game::instance().input.KEY_PRESSED)
	{
		if (state != PLAY) {
			Game::instance().sound("cursor");
			state--;
		}
		else sound("stop");
		currentTime = 0;
	}
	else if (Game::instance().input.getSpecialKey(GLUT_KEY_DOWN) == Game::instance().input.KEY_PRESSED)
	{
		if (state != EXIT) {
			sound("cursor");
			state++;
		}
		else sound("stop");
		currentTime = 0;
	}
	if (Game::instance().input.getKey(13) == Game::instance().input.KEY_PRESSED && state == EXIT) {
		exit(0);
	}
}

void Menu::render() {

	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	//0.054, 0.356, 0.505

	modelview = glm::mat4(1.f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	pointer->render();

	for (int i = 0; i < 4; i++) {
		text.render(options[i], glm::vec2(CAMERA_WIDTH / 2 - 130, CAMERA_HEIGHT/3 + 50*i + 50), MENU_TEXT_SIZE, glm::vec4(1.f, 1.f, 1.f, 1.f));
	}
	title.render(gameName, glm::vec2(CAMERA_WIDTH / 2 - 200, MENU_TEXT_SIZE*4), 35, glm::vec4(1.f, 1.f, 1.f, 1.f));
}

void Menu::initShaders()
{
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

void Menu::sound(string filename) {
	Game::instance().sound(filename);
}
