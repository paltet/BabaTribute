#include "Eat.h"

void Eat::setAnimations() {

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	sprite->addKeyframe(0, glm::vec2(27.f / 32.f, 27.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(27.f / 32.f, 28.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(27.f / 32.f, 29.f / 66.f));

	sprite->changeAnimation(0);
}

void Eat::setColor() {
	color = glm::vec3(1.f, 86 / 255.f, 86 / 255.f);
}