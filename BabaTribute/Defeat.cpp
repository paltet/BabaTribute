#include "Defeat.h"


void Defeat::setAnimations() {

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	sprite->addKeyframe(0, glm::vec2(5.f / 32.f, 39.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(5.f / 32.f, 40.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(5.f / 32.f, 41.f / 66.f));

	sprite->changeAnimation(0);
}

void Defeat::setColor() {
	color = glm::vec3(1.f, 0.f, 1.f);
}