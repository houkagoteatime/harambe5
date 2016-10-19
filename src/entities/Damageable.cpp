#include "Damageable.h"

Damageable::Damageable(float health, float damage) : health(health), damage(damage){

}

Damageable::~Damageable() {

}
bool Damageable::isDead() {
	if(health <= 0)
		return true;
	return false;
}

void Damageable::takeDamage(float damage) {
	health -= damage;
}

float Damageable::getDamage() const {
	return damage;
}

float Damageable::getHealth() const {
	return health;
}
