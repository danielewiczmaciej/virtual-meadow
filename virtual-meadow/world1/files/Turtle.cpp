#include "headers.h"
#define ADDTURTLE(Y,X) world->add_organism(new Turtle(world, {pos.x + X, pos.y + Y}), {pos.x + X, pos.y + Y})

Turtle::Turtle() {}

Turtle::Turtle(World* world, const CORDS pos) {
	this->world = world;
	this->pos = pos;
	this->ini = 1;
	this->pow = 2;
}

Turtle::Turtle(World* world, const CORDS pos, int age, int ini, int pow) {
	this->world = world;
	this->pos = pos;
	this->ini = ini;
	this->age = age;
	this->pow = pow;
}

const void Turtle::draw() { cout << TURTLE; }

const char Turtle::get_sign() { return TURTLE; }

Turtle::~Turtle() {}

void Turtle::action() {
	int temp2 = rand() % 4;
	if (temp2 <= 2) {
		string temp = "";
		temp += "T stays in place";
		world->log(temp);
		return;
	}
	else {
		DIRECTION dir;
		choose_diff_dir(dir);
		if (dynamic_cast<Ground*>(next(dir, 1))) {
			move(dir);
		}
		else {
			next(dir, 1)->collision(this);
			if (dynamic_cast<Ground*>(next(dir, 1))) move(dir);
		}

	}
}

void Turtle::reproduce(Org* collider) {
	Turtle* temp_a = dynamic_cast<Turtle*>(collider);

	DIRECTION dir;
	choose_diff_dir(dir);
	if (dir == UP && pos.y > 0 || \
		dir == DOWN && pos.y < (world->get_height() - 1) || \
		dir == RIGHT && pos.x < (world->get_width() - 1) || \
		dir == LEFT && pos.x > 0) {

		if (dynamic_cast<Ground*>(next(dir, 1))) {


			switch (dir) {
			case UP: ADDTURTLE(-1, 0); break;
			case DOWN: ADDTURTLE(1, 0); break;
			case RIGHT: ADDTURTLE(0, 1); break;
			case LEFT: ADDTURTLE(0, -1); break;
			}

		}
	}
}

void Turtle::collision(Org* collider) {
	if (dynamic_cast<Turtle*>(collider)) {
		reproduce(collider);
	}
	else if (collider->get_pow() < 5) {
		string temp = "";
		temp += this->get_sign();
		temp += " stopped by ";
		temp += collider->get_sign();
		world->log(temp);
		return;
	}
	else if (collider->get_pow() > this->get_pow()) {
		string temp = "";
		temp += collider->get_sign();
		temp += " kills ";
		temp += this->get_sign();
		world->log(temp);
		world->world[this->pos.y][this->pos.x] = new Ground();
	}
	else {
		string temp = "";
		temp += collider->get_sign();
		temp += " was killed by ";
		temp += this->get_sign();
		world->log(temp);
		world->world[collider->pos.y][collider->pos.x] = new Ground();
	}
}
