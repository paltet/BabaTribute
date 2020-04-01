#include "Number.h"

void Number::setAnimations() {
	sprite->setNumberAnimations(10);
	for (int i = 0; i < 10; i++) sprite->setAnimationSpeed(i, 1);

	sprite->addKeyframe(0, glm::vec2(21.f / 32.f, 40.f / 66.f));
	sprite->addKeyframe(1, glm::vec2(18.f / 32.f, 39.f / 66.f));
	sprite->addKeyframe(2, glm::vec2(19.f / 32.f, 39.f / 66.f));
	sprite->addKeyframe(3, glm::vec2(20.f / 32.f, 39.f / 66.f));
	sprite->addKeyframe(4, glm::vec2(18.f / 32.f, 41.f / 66.f));
	sprite->addKeyframe(5, glm::vec2(19.f / 32.f, 41.f / 66.f));
	sprite->addKeyframe(6, glm::vec2(19.f / 32.f, 40.f / 66.f));
	sprite->addKeyframe(7, glm::vec2(20.f / 32.f, 40.f / 66.f));
	sprite->addKeyframe(8, glm::vec2(21.f / 32.f, 39.f / 66.f));
	sprite->addKeyframe(9, glm::vec2(18.f / 32.f, 40.f / 66.f));

	sprite->changeAnimation(0);
}

void Unities::update(int deltaTime, int moves) {
	sprite->update(deltaTime);
	sprite->changeAnimation(moves % 10);
}

void Tens::update(int deltaTime, int moves) {
	sprite->update(deltaTime);
	if (moves > 99) sprite->changeAnimation(9);
	else sprite->changeAnimation(moves / 10);
}

void Number::setColor() {
	color = glm::vec3(232 / 255.f, 217 / 255.f, 215 / 255.f);
}