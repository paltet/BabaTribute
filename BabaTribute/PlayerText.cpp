#include "PlayerText.h"
#include "Player.h"


void PlayerText::setAnimations() {

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(0, 8);

	sprite->addKeyframe(0, glm::vec2(20.f / 32.f, 30.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(20.f / 32.f, 31.f / 66.f));
	sprite->addKeyframe(0, glm::vec2(20.f / 32.f, 32.f / 66.f));

	sprite->changeAnimation(0);
}

string PlayerText::getIdReferred() {
	Player *p = new Player();
	return (typeid(*p).name());
}

void PlayerText::setColor() {
	color = glm::vec3(237/255.f, 30/255.f, 192/255.f);
}
