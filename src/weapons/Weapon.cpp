#include "Weapon.h"
Weapon::Weapon(float delay, float currTime) {
	this->delay = delay;
	this->currTime = currTime;
}

Weapon::~Weapon() {
}

bool Weapon::checkIfCanAttack(float time) {
	if((time - currTime) >= delay) {
		return true;
		currTime = time;
	}
	return false;
}
