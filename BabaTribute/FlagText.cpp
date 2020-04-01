#include "FlagText.h"
#include "Flag.h"

void FlagText::setAnimations() {

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	sprite->addKeyframe(0, glm::vec2(1.f / 32.f, 30.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(1.f / 32.f, 31.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(1.f / 32.f, 32.f / 66.f));

	sprite->changeAnimation(0);
}

string FlagText::getIdReferred() {
	Flag *w = new Flag();
	return (typeid(*w).name());
}

void FlagText::setColor() {
	color = glm::vec3(1.f, 236 / 255.f, 132 / 255.f);
}