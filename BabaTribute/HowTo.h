#ifndef _HOWTO_INCLUDE
#define _HOWTO_INCLUDE

#include "Text.h"

class HowTo
{
public:
	HowTo();
	~HowTo();

	void init();
	void update(int deltaTime);
	void render();

private:
	int currentTime;

	Text back;

};
#endif
