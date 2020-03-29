#include "Entity.h"

void Entity::init(glm::vec2 pos, Texture &tex, ShaderProgram &program) {

	sProgram = program;
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f / 32.f, 1.f / 66.f), &tex, &program);
	setAnimations();
	position = pos;
	sprite->setPosition(position);
	setColor();
}

void Entity::update(int deltaTime, int moves) {
	sprite->update(deltaTime);
}

void Entity::render() {

	sProgram.setUniform4f("color", color.x, color.y, color.z, 1.0f);


	sprite->render();
}

void Entity::move(direction d, float length) {
	switch (d) {
		case DOWN:
			{
				position = glm::vec2(position.x, position.y + length);
				break;
			}
		case RIGHT:
			{
				position = glm::vec2(position.x + length, position.y);
				break;
			}
		case LEFT:
			{
				position = glm::vec2(position.x - length, position.y);
				break;
			}
		case UP:
			{
				position = glm::vec2(position.x, position.y - length);
				break;
			}
	}
	sprite->setPosition(position);
}

void Entity::setColor() {
	color = glm::vec3(1.f, 1.f, 1.f);
}

string Entity::getIdReferred() {
	return "";
}

int Entity::eatMoves() {
	return 0;
}