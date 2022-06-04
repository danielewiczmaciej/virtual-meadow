#pragma once
#include "Animal.h"

class Turtle : public Animal {
protected:
	void reproduce(Org*) override;
public:
	Turtle();
	Turtle(World* world, const CORDS _position);
	Turtle(World*, const CORDS, int age, int ini, int pow);
	const void draw() override;
	const char get_sign() override;
	void action() override;
	void collision(Org*) override;
	~Turtle();
};