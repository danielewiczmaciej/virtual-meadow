#pragma once
#include "Plant.h"
class Dandelion : public Plant {
protected:
	void reproduce();
public:
	Dandelion();
	Dandelion(World*, const CORDS);
	Dandelion(World*, const CORDS, int age, int ini, int pow);
	const void draw() override;
	const char get_sign() override;
	void action() override;
	void collision(Org*) override;
	~Dandelion();
};