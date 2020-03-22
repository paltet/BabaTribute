#include "Player.h"


void Player::setAnimations() {

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	sprite->addKeyframe(0, glm::vec2(15.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(15.f / 32.f, 4.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(15.f / 32.f, 5.f / 66.f));

	sprite->changeAnimation(0);
}