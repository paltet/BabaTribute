#include "WallText.h"
#include "Wall.h"

void WallText::setAnimations() {

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	sprite->addKeyframe(0, glm::vec2(27.f / 32.f, 33.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(27.f / 32.f, 34.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(27.f / 32.f, 35.f / 66.f));

	sprite->changeAnimation(0);
}

string WallText::getIdReferred() {
	Wall *w = new Wall();
	return (typeid(*w).name());
}