#pragma once
#include "Plant.h"

class Borscht :public Plant {
protected:
	void reproduce();
public:
	Borscht();
	Borscht(World*, const CORDS);
	Borscht(World*, const CORDS, int age, int ini, int pow);
	const void draw() override;
	const char get_sign() override;
	void action() override;
	void burn();
	void collision(Org*) override;
	~Borscht();
};