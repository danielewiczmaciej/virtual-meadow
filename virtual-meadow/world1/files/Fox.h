#pragma once
#include "Animal.h"

class Fox : public Animal {
protected:
	void reproduce(Org*) override;
public:
	Fox();
	Fox(World* world, const CORDS _position);
	Fox(World*, const CORDS, int age, int ini, int pow);
	const void draw() override;
	const char get_sign() override;
	void action() override;
	void collision(Org*) override;
	~Fox();
};