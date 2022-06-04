#include "headers.h"
#define SIGN(Y,X) world->world[pos.y + Y][pos.x + X]->get_sign()
#define ADD(X,Y) world->add_organism(new Borscht(world, { pos.x+X, pos.y+Y}), { pos.x+X, pos.y +Y })
#define POS(Y,X) world->world[pos.y + Y][pos.x + X]
#define KILL(Y,X) if(dynamic_cast<Animal*> (POS(Y,X))) { \
						temp2="";\
						temp2+=POS(Y,X)->get_sign();\
						temp2+= " has been burned by $ ";\
						world->log(temp2);\
						POS(Y,X) = new Ground();}

Borscht::Borscht() {}

Borscht::Borscht(World* world, const CORDS pos) {
	this->world = world;
	this->pos = pos;
	this->ini = 0;
	this->pow = 10;
}

Borscht::Borscht(World* world, const CORDS pos, int age, int ini, int pow) {
	this->world = world;
	this->pos = pos;
	this->ini = ini;
	this->age = age;
	this->pow = pow;
}

const void Borscht::draw() { cout << BORSCHT; }

const char Borscht::get_sign() { return BORSCHT; }

void Borscht::action() {
	int temp = rand() % 30;
	if (temp == 0) reproduce();
	burn();
}

void Borscht::burn() {
	string temp2;
	if (pos.x == 0) {
		if (pos.y == 0) {
			KILL(1, 0);
			KILL(1, 1);
			KILL(0, 1);
		}
		else if (pos.y == world->get_height() - 1) {
			KILL(-1, 0);
			KILL(-1, 1);
			KILL(0, 1);
		}
		else {
			KILL(-1, 0);
			KILL(-1, 1);
			KILL(0, 1);
			KILL(1, 0);
			KILL(1, 1);
		}
	}
	else if (pos.x == world->get_width() - 1) {
		if (pos.y == 0) {
			KILL(1, 0);
			KILL(1, -1);
			KILL(0, -1);
		}
		else if (pos.y == world->get_height() - 1) {
			KILL(-1, 0);
			KILL(-1, -1);
			KILL(0, -1);
		}
		else {//right edge
			KILL(-1, 0);
			KILL(-1, -1);
			KILL(0, -1);
			KILL(1, 0);
			KILL(1, -1);
		}
	}
	else if (pos.y == 0) {//top without corners
		KILL(1, 0);
		KILL(1, 1);
		KILL(1, -1);
		KILL(0, 1);
		KILL(0, -1);
	}
	else if (pos.y == world->get_height() - 1) {//bot without corners
		KILL(-1, 0);
		KILL(-1, 1);
		KILL(-1, -1);
		KILL(0, 1);
		KILL(0, -1);
	}
	else {
		KILL(-1, 0);
		KILL(-1, 1);
		KILL(-1, -1);
		KILL(0, 1);
		KILL(0, -1);
		KILL(1, 0);
		KILL(1, 1);
		KILL(1, -1);
	}
}

void Borscht::collision(Org* collider) {
	string temp = "";
	temp += collider->get_sign();
	temp += " eats ";
	temp += this->get_sign();
	temp += " and dies";
	world->log(temp);
	world->world[this->pos.y][this->pos.x] = new Ground();
	world->world[collider->pos.y][collider->pos.x] = new Ground();
}

void Borscht::reproduce() {
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

Borscht::~Borscht() {}