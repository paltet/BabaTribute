#include "FireText.h"
#include "Fire.h"

void FireText::setAnimations() {

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	sprite->addKeyframe(0, glm::vec2(0.f / 32.f, 30.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(0.f / 32.f, 31.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(0.f / 32.f, 32.f / 66.f));

	sprite->changeAnimation(0);
}

string FireText::getIdReferred() {
	Fire *f = new Fire();
	return (typeid(*f).name());
}

void FireText::setColor() {
	color = glm::vec3(147 / 255.f, 0.f, 34 / 255.f);
}