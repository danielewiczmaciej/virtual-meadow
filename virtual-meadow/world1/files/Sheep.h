#pragma once
#include "Animal.h"

class Sheep : public Animal {
protected:
	void reproduce(Org*) override;
public:
	Sheep();
	Sheep(World* world, const CORDS _position);
	Sheep(World*, const CORDS, int age, int ini, int pow);
	const void draw() override;
	const char get_sign() override;
	~Sheep();
};