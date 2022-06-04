#pragma once
#include "Plant.h"
class Guarana : public Plant {
protected:
	void reproduce();
public:
	Guarana();
	Guarana(World*, const CORDS);
	Guarana(World*, const CORDS, int age, int ini, int pow);
	void action() override;
	const void draw() override;
	const char get_sign() override;
	void collision(Org*) override;
	~Guarana();
};