#include "headers.h"

#define SIGN(Y,X) world->world[pos.y + Y][pos.x + X]->get_sign()
#define ADDFOX(Y,X) world->add_organism(new Fox(world, {pos.x + X, pos.y + Y}), {pos.x + X, pos.y + Y})

Fox::Fox() {}

Fox::Fox(World* world, const CORDS pos) {
	this->world = world;
	this->pos = pos;
	this->ini = 7;
	this->pow = 3;
}

Fox::Fox(World* world, const CORDS pos, int age, int ini, int pow) {
	this->world = world;
	this->pos = pos;
	this->ini = ini;
	this->age = age;
	this->pow = pow;
}

const void Fox::draw() { cout << FOX; }

const char Fox::get_sign() { return FOX; }

Fox::~Fox() {}

void Fox::action() {
	DIRECTION dir;
	choose_diff_dir(dir);
	if (dynamic_cast<Ground*>(next(dir, 1))) {
		move(dir);
	}
	else {
		if (next(dir, 1)->get_pow() <= this->get_pow()) {
			next(dir, 1)->collision(this);
			if (next(dir, 1)->get_sign() == GROUND) move(dir);
		}
	}
}


void Fox::collision(Org* collider) {
	if (collider->get_pow() > this->get_pow()) {
		string temp = "";
		temp += collider->get_sign();
		temp += " kills ";
		temp += this->get_sign();
		world->log(temp);
		world->world[this->pos.y][this->pos.x] = new Ground();
	}
	else {
		string temp = "";
		temp += this->get_sign();
		temp += " kills ";
		temp += collider->get_sign();
		world->log(temp);
		world->world[collider->pos.y][collider->pos.x] = new Ground();
	}
}

void Fox::reproduce(Org* collider) {
	Fox* temp_a = dynamic_cast<Fox*>(collider);
	DIRECTION dir = (DIRECTION)(rand() % 4);
	if (dir == UP && pos.y > 0 || \
		dir == DOWN && pos.y < (world->get_height() - 1) || \
		dir == RIGHT && pos.x < (world->get_width() - 1) || \
		dir == LEFT && pos.x > 0) {
		if (dynamic_cast<Ground*>(next(dir, 1))) {
			switch (dir) {
			case UP: ADDFOX(-1, 0); break;
			case DOWN: ADDFOX(1, 0); break;
			case RIGHT: ADDFOX(0, 1); break;
			case LEFT: ADDFOX(0, -1); break;
			}
		}
	}
}
