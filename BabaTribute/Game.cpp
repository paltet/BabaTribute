#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

void Game::init() {

	state = STATE_MENU;
	bPlay = true;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	menu.init();

}

bool Game::update(int deltaTime) {

	switch (state) {

	case STATE_MENU:
		menu.update(deltaTime);
		switch (menu.state) {
		case HOWTO:
			if (getKey(13)) {
				howto.init();
				state = STATE_HOWTO;
			}
			break;
		case PLAY:
			if (getKey(13)) {
				scene.init();
				state = STATE_PLAYING;
			}
			break;
		}
		break;

	case STATE_PLAYING:
		scene.update(deltaTime);
		break;

	case STATE_HOWTO:
		howto.update(deltaTime);
		if (howto.ret) {
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

