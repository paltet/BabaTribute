#pragma once
class Menu
{
public:
	Menu();
	~Menu();

	void init();
	void update(int deltaTime);
	void render();

private:
	float currentTime;
};

