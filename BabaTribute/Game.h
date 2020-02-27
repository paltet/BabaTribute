#pragma once
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
	//enum { STATE_MENU, STATE_PLAYING, STATE_CREDITS };
	//int state;

	//Menu menu;
	//Scene scene;
	//Credits credits;
	//Instructions instructions

	bool keys[256], specialKeys[256]; // Store key states so that 
									  // we can have access at any time

};

