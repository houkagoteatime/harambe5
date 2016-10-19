#pragma once

class Damageable {
public:
	Damageable(float health, float damage);
	virtual ~Damageable();
	void takeDamage(float dmg);
	float getDamage() const;
	float getHealth() const;
	bool isDead();
protected:
	float health;
	float damage;
};
