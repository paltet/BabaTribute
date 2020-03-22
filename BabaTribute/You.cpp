#include "You.h"


void You::setAnimations() {

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	sprite->addKeyframe(0, glm::vec2(20.f / 32.f, 42.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(20.f / 32.f, 43.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(20.f / 32.f, 44.f / 66.f));

	sprite->changeAnimation(0);
}

void You::setColor() {
	color = glm::vec3(1.f, 1.f, 0.f);
}