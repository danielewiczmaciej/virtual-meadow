#include "headers.h"
#define SIGN(Y,X) world->world[pos.y + Y][pos.x + X]->get_sign()
#define ADD(X,Y) world->add_organism(new Plant(world, { pos.x+X, pos.y+Y}), { pos.x+X, pos.y +Y })
#define POS(Y,X)  world->world[pos.y + Y][pos.x + X]

Plant::Plant() {}

Plant::Plant(World* world, const CORDS pos) {
	this->world = world;
	this->pos = pos;
	this->ini = 0;
	this->pow = 0;
}

Plant::Plant(World* world, const CORDS pos, int age, int ini, int pow) {
	this->world = world;
	this->pos = pos;
	this->age = age;
	this->ini = ini;
	this->pow = pow;
}

const void Plant::draw() { cout << GRASS; }

const char Plant::get_sign() { return GRASS; }

Plant::~Plant() {}

void Plant::action() {
	int temp = rand() % 20;
	if (temp == 0) reproduce();
}

void Plant::reproduce() {
	list<DIRECTION> chances;
	if (pos.x == 0) {
		if (pos.y == 0) {
			if (SIGN(1, 0) == GROUND) chances.push_back(DOWN);
			if (SIGN(0, 1) == GROUND) chances.push_back(RIGHT);
		}
		else if (pos.y == world->get_height() - 1) {
			if (SIGN(-1, 0) == GROUND) chances.push_back(UP);
			if (SIGN(0, 1) == GROUND) chances.push_back(RIGHT);
		}
		else {
			if (SIGN(-1, 0) == GROUND) chances.push_back(UP);
			if (SIGN(1, 0) == GROUND) chances.push_back(DOWN);
			if (SIGN(0, 1) == GROUND) chances.push_back(RIGHT);
		}
	}
	else if (pos.x == world->get_width() - 1) {
		if (pos.y == 0) {
			if (SIGN(1, 0) == GROUND) chances.push_back(DOWN);
			if (SIGN(0, -1) == GROUND) chances.push_back(LEFT);
		}
		else if (pos.y == world->get_height() - 1) {
			if (SIGN(-1, 0) == GROUND) chances.push_back(UP);
			if (SIGN(0, -1) == GROUND) chances.push_back(LEFT);
		}
		else {
			if (SIGN(-1, 0) == GROUND) chances.push_back(UP);
			if (SIGN(1, 0) == GROUND) chances.push_back(DOWN);
			if (SIGN(0, -1) == GROUND) chances.push_back(LEFT);
		}
	}
	else if (pos.y == 0) {
		if (SIGN(1, 0) == GROUND) chances.push_back(DOWN);
		if (SIGN(0, -1) == GROUND) chances.push_back(LEFT);
		if (SIGN(0, 1) == GROUND) chances.push_back(RIGHT);
	}
	else if (pos.y == world->get_height() - 1) {
		if (SIGN(-1, 0) == GROUND) chances.push_back(UP);
		if (SIGN(0, -1) == GROUND) chances.push_back(LEFT);
		if (SIGN(0, 1) == GROUND) chances.push_back(RIGHT);
	}
	else {
		if (SIGN(-1, 0) == GROUND) chances.push_back(UP);
		if (SIGN(1, 0) == GROUND) chances.push_back(DOWN);
		if (SIGN(0, -1) == GROUND) chances.push_back(LEFT);
		if (SIGN(0, 1) == GROUND) chances.push_back(RIGHT);
	}
	if (chances.size() == 0) return;
	else {
		int temp = rand() % chances.size();
		for (int i = 0; i < temp; i++) chances.pop_front();
		switch (chances.front()) {
		case UP: ADD(0, -1);	break;
		case DOWN: ADD(0, 1); break;
		case RIGHT: ADD(1, 0); break;
		case LEFT: ADD(-1, 0); break;
		}
	}
}

Org* Plant::next(const DIRECTION dir, const int distance) {
	switch (dir) {
	case UP:
		return POS(-distance, 0);
		break;
	case DOWN:
		return POS(+distance, 0);
		break;
	case LEFT:
		return POS(0, -distance);
		break;
	case RIGHT:
		return POS(0, +distance);
		break;
	}
}

void Plant::collision(Org* collider) {
	world->world[this->pos.y][this->pos.x] = new Ground();
	string temp = "";
	temp += collider->get_sign();
	temp += " eats ";
	temp += this->get_sign();
	world->log(temp);
}