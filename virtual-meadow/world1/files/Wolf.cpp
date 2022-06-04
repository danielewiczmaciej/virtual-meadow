#include "headers.h"
#define ADDWOLF(Y,X) world->add_organism(new Wolf(world, {pos.x + X, pos.y + Y}), {pos.x + X, pos.y + Y})

Wolf::Wolf() {}

Wolf::Wolf(World* world, const CORDS pos) {
	this->world = world;
	this->pos = pos;
	this->ini = 5;
	this->pow = 9;
}

Wolf::Wolf(World* world, const CORDS pos, int age, int ini, int pow) {
	this->world = world;
	this->pos = pos;
	this->ini = ini;
	this->age = age;
	this->pow = pow;
}

const void Wolf::draw() { cout << WOLF; }

const char Wolf::get_sign() { return WOLF; }

Wolf::~Wolf() {}

void Wolf::reproduce(Org* collider) {
	Wolf* temp_a = dynamic_cast<Wolf*>(collider);
	DIRECTION dir = (DIRECTION)(rand() % 4);
	if (dir == UP && pos.y > 0 || \
		dir == DOWN && pos.y < (world->get_height() - 1) || \
		dir == RIGHT && pos.x < (world->get_width() - 1) || \
		dir == LEFT && pos.x > 0) {
		if (dynamic_cast<Ground*>(next(dir, 1))) {
			switch (dir) {
			case UP: ADDWOLF(-1, 0); break;
			case DOWN: ADDWOLF(1, 0); break;
			case RIGHT: ADDWOLF(0, 1); break;
			case LEFT: ADDWOLF(0, -1); break;
			}
		}
	}
}