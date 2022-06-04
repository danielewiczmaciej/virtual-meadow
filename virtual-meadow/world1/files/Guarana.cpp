#include "headers.h"
#define SIGN(Y,X) world->world[pos.y + Y][pos.x + X]->get_sign()
#define ADD(X,Y) world->add_organism(new Guarana(world, { pos.x+X, pos.y+Y}), { pos.x+X, pos.y +Y })
Guarana::Guarana() {}

Guarana::Guarana(World* world, const CORDS pos) {
	this->world = world;
	this->pos = pos;
	this->ini = 0;
	this->pow = 0;
}

Guarana::Guarana(World* world, const CORDS pos, int age, int ini, int pow) {
	this->world = world;
	this->pos = pos;
	this->age = age;
	this->ini = ini;
	this->pow = pow;
}

void Guarana::action() {
	int temp = rand() % 30;
	if (temp == 0) reproduce();
}

const void Guarana::draw() { cout << GUARANA;}
const char Guarana::get_sign() { return GUARANA;}

void Guarana::collision(Org* collider) {
	collider->pow += 3;
	string temp = "";
	temp += collider->get_sign();
	temp += " eats ";
	temp += this->get_sign();
	temp += " now it has ";
	temp += to_string(collider->get_pow());
	world->log(temp);
	world->world[this->pos.y][this->pos.x] = new Ground();
}

void Guarana::reproduce() {
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

Guarana::~Guarana() {}