#pragma once
#include "Animal.h"

class Antylope : public Animal {
protected:
	void choose_diff_dir(DIRECTION& dir);
	void reproduce(Org*) override;
public:
	Antylope();
	Antylope(World* world, const CORDS pos);
	Antylope(World*, const CORDS, int age, int ini, int pow);
	const void draw() override;
	const char get_sign() override;
	void action() override;
	void collision(Org*) override;
	~Antylope();
};