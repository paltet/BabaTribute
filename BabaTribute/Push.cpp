#include "Push.h"


void Push::setAnimations() {

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	sprite->addKeyframe(0, glm::vec2(2.f / 32.f, 42.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(2.f / 32.f, 43.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(2.f / 32.f, 44.f / 66.f));

	sprite->changeAnimation(0);
}

void Push::setColor() {
	color = glm::vec3(0.f, 1.f, 1/6.f);
}