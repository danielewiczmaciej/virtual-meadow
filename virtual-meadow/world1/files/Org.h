#pragma once
#include <iostream> 
#include "Base.h"

class World;

class Org {
	friend World;
public:
	int age = 0;
	int pow;
	int ini;
	CORDS pos;
	World* world;
	Org();
	Org(World* world, const CORDS pos);
	Org(World*, const CORDS, int age, int ini, int pow);
	virtual void action() = 0;
	virtual void collision(Org*);
	virtual const char get_sign() = 0;
	virtual const void draw() = 0;

	const CORDS get_cords();
	const int get_pow();
	const int get_ini();
	const int get_age();
	~Org();
};