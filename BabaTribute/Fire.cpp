#include "Fire.h"


void Fire::setAnimations() {

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	sprite->addKeyframe(0, glm::vec2(5.f / 32.f, 24.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(5.f / 32.f, 25.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(5.f / 32.f, 26.f / 66.f));

	sprite->changeAnimation(0);
}

void Fire::setColor() {
	color = glm::vec3(1.f, 86 / 255.f, 86 / 255.f);
}
