#include "Input.h"



Input::Input()
{
}


Input::~Input()
{
}

void Input::init() {
	
	for (int i = 0; i < NUM_KEYS; i++) {
		keys[i] = KEY_IDLE;
	}
	for (int i = 0; i < NUM_KEYS; i++) {
		specialKeys[i] = KEY_IDLE;
	}

}

void Input::update(bool newKeys[], bool newSpecialKeys[]) {

	for (int i = 0; i < NUM_KEYS; i++) {
		switch (keys[i]) {

		case KEY_IDLE:
			if (newKeys[i]) keys[i] = KEY_PRESSED;
			break;

		case KEY_PRESSED:
			if (newKeys[i]) keys[i] = KEY_HOLD;
			else keys[i] = KEY_RELEASED;
			break;

		case KEY_HOLD:
			if (!newKeys[i]) keys[i] = KEY_RELEASED;
			break;

		case KEY_RELEASED:
			if (newKeys[i]) keys[i] = KEY_PRESSED;
			else keys[i] = KEY_IDLE;
			break;
		}
	}

	for (int i = 0; i < NUM_KEYS; i++) {
		switch (specialKeys[i]) {

		case KEY_IDLE:
			if (newSpecialKeys[i]) specialKeys[i] = KEY_PRESSED;
			break;

		case KEY_PRESSED:
			if (newSpecialKeys[i]) specialKeys[i] = KEY_HOLD;
			else keys[i] = KEY_RELEASED;
			break;

		case KEY_HOLD:
			if (!newSpecialKeys[i]) specialKeys[i] = KEY_RELEASED;
			break;

		case KEY_RELEASED:
			if (newSpecialKeys[i]) specialKeys[i] = KEY_PRESSED;
			else keys[i] = KEY_IDLE;
			break;
		}
	}
}

Input::KEY_STATE Input::getKey(int key) {

	if (key >= NUM_KEYS) return KEY_IDLE;
	else return keys[key];
}

Input::KEY_STATE Input::getSpecialKey(int key) {
	if (key >= NUM_KEYS) return KEY_IDLE;
	else return specialKeys[key];
}


