#include "headers.h"

Org::Org() {}

Org::Org(World* world, const CORDS pos) {
	this->world = world;
	this->pos = pos;
}

Org::Org(World* world, const CORDS pos, int age, int ini, int pow) {
	this->world = world;
	this->pos = pos;
	this->age = age;
	this->ini = ini;
	this->pow = pow;
}

void Org::action() {}

void Org::collision(Org* collider) {
	if (collider->get_pow() > this->get_pow()) {
		string temp = "";
		temp += this->get_sign();
		temp += " attacks stronger ";
		temp += collider->get_sign();
		world->log(temp);
		world->world[this->pos.y][this->pos.x] = new Ground();
	}
}

const CORDS Org::get_cords() { return pos; }

const int Org::get_pow() { return pow; }

const int Org::get_ini() { return ini; }

const int Org::get_age() { return age; }

Org::~Org() {}