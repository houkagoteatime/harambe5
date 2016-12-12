#pragma once
#include "Weapon.h"

class Katana : public Weapon{
public:
	Katana(float delay, float currTime);
	~Katana();
	virtual void attack();
};
