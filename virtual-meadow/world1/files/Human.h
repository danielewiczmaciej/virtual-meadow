#pragma once
#include "Animal.h"
class Human : public Animal {
private:
	int id;
	int turns;
	Org* next(Org*, DIRECTION, const int);
	Org* next(DIRECTION, const int);
	void move(DIRECTION);
	void move(Org*, DIRECTION);
public:
	Human();
	Human(World*, const CORDS, const int index);
	Human(World*, const CORDS, int age, int ini, int pow, int id, int turnsleft);
	const void draw() override;
	const char get_sign() override;
	const int turns_left();
	void use_ability();
	void action(DIRECTION);
	void collision(Org*) override;
	const int getindex() { return id; }
	void immortal();
	~Human();
};