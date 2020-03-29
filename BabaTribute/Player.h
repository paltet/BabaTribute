#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE

#include "Entity.h"

class Player : public Entity
{
public:

	void setAnimations();
	void move(direction d, float length);
	void update(int deltaTime, int moves);

	float animTime = -1.f, currentTime = 0.f;

	enum anim {IDLE_DOWN, RUN_DOWN, IDLE_RIGHT, RUN_RIGHT, IDLE_LEFT, RUN_LEFT, IDLE_UP, RUN_UP};

};
#endif
