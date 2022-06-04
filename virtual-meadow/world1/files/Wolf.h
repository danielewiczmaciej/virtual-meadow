#pragma once
#include "Animal.h"

class Wolf : public Animal {
protected:
	void reproduce(Org*) override;
public:
	Wolf();
	Wolf(World* world, const CORDS _position);
	Wolf(World*, const CORDS, int age, int ini, int pow);
	const void draw() override;
	const char get_sign() override;
	~Wolf();
};