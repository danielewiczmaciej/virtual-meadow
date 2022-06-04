#include "headers.h"

Ground::Ground() {}
Ground::Ground(World* world, const CORDS pos) {
	this->world = world;
	this->pos = pos;
}
void Ground::action() {}
const void Ground::draw() { cout << GROUND; }
const char Ground::get_sign() { return GROUND; }
Ground::~Ground() {};