#include "Stop.h"


void Stop::setAnimations() {

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	sprite->addKeyframe(0, glm::vec2(12.f / 32.f, 42.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(12.f / 32.f, 43.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(12.f / 32.f, 44.f / 66.f));

	sprite->changeAnimation(0);
}

void Stop::setColor() {
	color = glm::vec3(93 / 255.f, 147 / 255.f, 42 / 255.f);
}