#include "FruitText.h"
#include "Fruit.h"

void FruitText::setAnimations() {

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	sprite->addKeyframe(0, glm::vec2(5.f / 32.f, 30.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(5.f / 32.f, 31.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(5.f / 32.f, 32.f / 66.f));

	sprite->changeAnimation(0);
}

string FruitText::getIdReferred() {
	Fruit *f = new Fruit();
	return (typeid(*f).name());
}