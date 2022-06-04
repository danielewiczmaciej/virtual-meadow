#pragma once
#include "Org.h"
class Plant : public Org {
protected:
	void reproduce();
	Org* next(const DIRECTION dir, const int dist);
public:
	Plant();
	Plant(World* world, const CORDS);
	Plant(World* world, const CORDS, int age, int ini, int pow);
	const void draw() override;
	const char get_sign() override;
	void action() override;
	void collision(Org*) override;
	~Plant();
};