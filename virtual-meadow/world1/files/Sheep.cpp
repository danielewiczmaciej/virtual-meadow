#include "headers.h"
#define ADDSHEEP(Y,X) world->add_organism(new Sheep(world, {pos.x + X, pos.y + Y}), {pos.x + X, pos.y + Y})

Sheep::Sheep() {}

Sheep::Sheep(World* world, const CORDS pos) {
	this->world = world;
	this->pos = pos;
	this->ini = 4;
	this->pow = 4;
}

Sheep::Sheep(World* world, const CORDS pos, int age, int ini, int pow) {
	this->world = world;
	this->pos = pos;
	this->ini = ini;
	this->age = age;
	this->pow = pow;
}

const void Sheep::draw() { cout << SHEEP; }

const char Sheep::get_sign() { return SHEEP; }

Sheep::~Sheep() {}

void Sheep::reproduce(Org* collider) {
	Sheep* temp_a = dynamic_cast<Sheep*>(collider);
	DIRECTION dir = (DIRECTION)(rand() % 4);
	if (dir == UP && pos.y > 0 || \
		dir == DOWN && pos.y < (world->get_height() - 1) || \
		dir == RIGHT && pos.x < (world->get_width() - 1) || \
		dir == LEFT && pos.x > 0) {
		if (dynamic_cast<Ground*>(next(dir, 1))) {
			switch (dir) {
			case UP: ADDSHEEP(-1, 0); break;
			case DOWN: ADDSHEEP(1, 0); break;
			case RIGHT: ADDSHEEP(0, 1); break;
			case LEFT: ADDSHEEP(0, -1); break;
			}
		}
	}
}