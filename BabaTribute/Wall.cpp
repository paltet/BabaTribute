#include "Wall.h"


void Wall::setAnimations(){

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	sprite->addKeyframe(0, glm::vec2(0.f / 32.f, 57.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(0.f / 32.f, 58.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(0.f / 32.f, 59.f / 66.f));

	sprite->changeAnimation(0);
}
