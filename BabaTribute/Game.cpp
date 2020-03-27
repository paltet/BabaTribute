#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
using namespace irrklang;

void Game::init() {

	state = STATE_MENU;
	bPlay = true;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	engine = createIrrKlangDevice();
	if (!engine) exit(0);

	menu.init();
	input.init();
	sound("level");
}

bool Game::update(int deltaTime) {

	input.update(keys, specialKeys);


	switch (state) {

	case STATE_MENU:
		menu.update(deltaTime);
		switch (menu.state) {
		case HOWTO:
			if (input.getKey(13) == input.KEY_PRESSED) {
				sound("select");
				howto.init();
				state = STATE_HOWTO;
			}
			break;
		case 2:
			if (input.getKey(13) == input.KEY_PRESSED) {
				sound("select");
				credits.init();
				state = STATE_CREDITS;
			}
			break;
		case PLAY:
			if (input.getKey(13) == input.KEY_PRESSED) {
				currentlevel = 0;
				sound("level");
				scene.init(levels[currentlevel]);
				scene.loadText("LEVEL " + to_string(currentlevel+1));
				state = STATE_PLAYING;
			}
			break;
		}
		break;

	case STATE_PLAYING:
		if (scene.update(deltaTime)) {
			currentlevel++;
			if (currentlevel < levels.size()) {
				scene.load(levels[currentlevel]);
				scene.loadText("LEVEL " + to_string(currentlevel+1));
			}
			else {
				menu.init();
				state = STATE_MENU;
			}
		}
		break;

	case STATE_HOWTO:
		howto.update(deltaTime);
		if (input.getKey(13) == input.KEY_PRESSED) {
			sound("select");
			state = STATE_MENU;
		}
		break;

	case STATE_CREDITS:
		credits.update(deltaTime);
		if (input.getKey(13) == input.KEY_PRESSED) {
			sound("select");
			state = STATE_MENU;
		}
		break;
	}
	return bPlay;

}

void Game::render() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch (state) {
	case STATE_MENU:
		menu.render();
		break;
	case STATE_HOWTO:
		howto.render();
		break;
	case STATE_PLAYING:
		scene.render();
		break;
	case STATE_CREDITS:
		credits.render();
		break;
	}
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}

void Game::sound(string filename) {
	filename = "sound/" + filename + ".mp3";
	if (!engine->isCurrentlyPlaying(filename.c_str())) engine->play2D(filename.c_str());
}