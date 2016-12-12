#pragma once

class Weapon {
public:
	Weapon(float delay, float currTime);
	virtual ~Weapon();
	virtual void attack(float time) = 0;;
	bool checkIfCanAttack(float time);
protected:
	float delay;
	float currTime;
};
