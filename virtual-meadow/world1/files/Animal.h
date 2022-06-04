#pragma once
#include "Org.h"
class Animal : public Org {
protected: 
	Org* next(const DIRECTION dir, const int distance);
	void move(DIRECTION dir);
	void choose_diff_dir(DIRECTION& dir);
	virtual void reproduce(Org*);
public:
	Animal();
	Animal(World* world, const CORDS _pos);
	Animal(World*, const CORDS, int age, int ini, int pow);
	const void draw() override;
	void action();
	void collision(Org*) override;
	const char get_sign() override;
	~Animal();
};