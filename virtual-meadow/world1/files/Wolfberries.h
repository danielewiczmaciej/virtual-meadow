#pragma once
#include "Plant.h"

class Wolfberries :public Plant {
protected:
	void reproduce();
public:
	Wolfberries();
	Wolfberries(World*, const CORDS);
	Wolfberries(World*, const CORDS, int age, int ini, int pow);
	const void draw() override;
	const char get_sign() override;
	void action() override;
	void collision(Org*) override;
	~Wolfberries();
};