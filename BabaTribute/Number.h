#ifndef _NUMBER_INCLUDE
#define _NUMBER_INCLUDE

#include "Entity.h"

class Number : public Entity
{
public:
	void setAnimations();
	void setColor();
};

class Unities: public Number
{
public:
	void update(int deltaTime, int moves);
};

class Tens : public Number
{
public:
	void update(int deltaTime, int moves);
};

#endif

