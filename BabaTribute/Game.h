#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Menu.h"
#include "HowTo.h"
#include "Scene.h"

#define CAMERA_WIDTH 480
#define CAMERA_HEIGHT 480

#define MARGIN 200

class Game
{
public:
	Game() {};

	static Game &instance()
	{
		static Game G;
		return G;
	}

	void init();
	bool update(int deltaTime);
	void render();

	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	bool bPlay;

	//Game state
	enum { STATE_MENU, STATE_PLAYING, STATE_HOWTO, STATE_CREDITS };
	int state;

	//Menu state
	enum { PLAY, HOWTO, ABOUT, EXIT };

	Menu menu;
	HowTo howto;
	Scene scene;
	//Credits credits;
	//Instructions instructions

	bool keys[256], specialKeys[256]; // Store key states so that 
									  // we can have access at any time

};

#endif