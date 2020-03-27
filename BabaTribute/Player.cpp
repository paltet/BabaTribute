#include "Player.h"


void Player::setAnimations() {

	sprite->setNumberAnimations(8);

	sprite->setAnimationSpeed(IDLE_DOWN, 8);
	sprite->setAnimationSpeed(RUN_DOWN, 8);
	sprite->setAnimationSpeed(IDLE_RIGHT, 8);
	sprite->setAnimationSpeed(RUN_RIGHT, 8);
	sprite->setAnimationSpeed(IDLE_LEFT, 8);
	sprite->setAnimationSpeed(RUN_LEFT, 8);
	sprite->setAnimationSpeed(IDLE_UP, 8);
	sprite->setAnimationSpeed(RUN_UP, 8);


	sprite->addKeyframe(IDLE_DOWN, glm::vec2(16.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(IDLE_DOWN, glm::vec2(16.f / 32.f, 4.f / 66.f));
	sprite->addKeyframe(IDLE_DOWN, glm::vec2(16.f / 32.f, 5.f / 66.f));

	sprite->addKeyframe(RUN_DOWN, glm::vec2(16.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(RUN_DOWN, glm::vec2(17.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(RUN_DOWN, glm::vec2(18.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(RUN_DOWN, glm::vec2(19.f / 32.f, 3.f / 66.f));

	sprite->addKeyframe(IDLE_RIGHT, glm::vec2(1.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(IDLE_RIGHT, glm::vec2(1.f / 32.f, 4.f / 66.f));
	sprite->addKeyframe(IDLE_RIGHT, glm::vec2(1.f / 32.f, 5.f / 66.f));

	sprite->addKeyframe(RUN_RIGHT, glm::vec2(1.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(RUN_RIGHT, glm::vec2(2.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(RUN_RIGHT, glm::vec2(3.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(RUN_RIGHT, glm::vec2(4.f / 32.f, 3.f / 66.f));

	sprite->addKeyframe(IDLE_LEFT, glm::vec2(11.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(IDLE_LEFT, glm::vec2(11.f / 32.f, 4.f / 66.f));
	sprite->addKeyframe(IDLE_LEFT, glm::vec2(11.f / 32.f, 5.f / 66.f));

	sprite->addKeyframe(RUN_LEFT, glm::vec2(11.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(RUN_LEFT, glm::vec2(12.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(RUN_LEFT, glm::vec2(13.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(RUN_LEFT, glm::vec2(14.f / 32.f, 3.f / 66.f));

	sprite->addKeyframe(IDLE_UP, glm::vec2(6.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(IDLE_UP, glm::vec2(6.f / 32.f, 4.f / 66.f));
	sprite->addKeyframe(IDLE_UP, glm::vec2(6.f / 32.f, 5.f / 66.f));

	sprite->addKeyframe(RUN_UP, glm::vec2(6.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(RUN_UP, glm::vec2(7.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(RUN_UP, glm::vec2(8.f / 32.f, 3.f / 66.f));
	sprite->addKeyframe(RUN_UP, glm::vec2(9.f / 32.f, 3.f / 66.f));


	sprite->changeAnimation(IDLE_DOWN);
}


void Player::move(direction d, float length) {
	switch (d) {
	case DOWN:
	{
		position = glm::vec2(position.x, position.y + length);
		sprite->changeAnimation(RUN_DOWN);
		break;
	}
	case RIGHT:
	{
		position = glm::vec2(position.x + length, position.y);
		sprite->changeAnimation(RUN_RIGHT);
		break;
	}
	case LEFT:
	{
		position = glm::vec2(position.x - length, position.y);
		sprite->changeAnimation(RUN_LEFT);
		break;
	}
	case UP:
	{
		position = glm::vec2(position.x, position.y - length);
		sprite->changeAnimation(RUN_UP);
		break;
	}
	}
	sprite->setPosition(position);
	animTime = currentTime;
	
}

void Player::update(int deltaTime) {
	currentTime += deltaTime;
	sprite->update(deltaTime);
	if (animTime > 0 && currentTime > animTime + 300.f){
		animTime = -1.f;
		int anim = sprite->animation();
		sprite->changeAnimation(anim - 1);
	}
}


