#include "Flag.h"


void Flag::setAnimations() {

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	sprite->addKeyframe(0, glm::vec2(6.f / 32.f, 21.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(6.f / 32.f, 22.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(6.f / 32.f, 23.f / 66.f));

	sprite->changeAnimation(0);
}
