#include "Fruit.h"


void Fruit::setAnimations() {

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	sprite->addKeyframe(0, glm::vec2(8.f / 32.f, 21.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(8.f / 32.f, 22.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(8.f / 32.f, 23.f / 66.f));

	sprite->changeAnimation(0);
}

int Fruit::eatMoves() {
	return 11;
}

void Fruit::setColor() {
	color = glm::vec3(187 / 255.f, 1.f, 124 / 255.f);
}