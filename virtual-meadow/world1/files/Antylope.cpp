#include "headers.h"

#define SIGN(Y,X) world->world[pos.y + Y][pos.x + X]->get_sign()
#define ADDANTYLOPE(Y,X) world->add_organism(new Antylope(world, {pos.x + X, pos.y + Y}), {pos.x + X, pos.y + Y})

Antylope::Antylope() {}

Antylope::Antylope(World* world, const CORDS pos) {
	this->world = world;
	this->pos = pos;
	this->ini = 4;
	this->pow = 4;
}

Antylope::Antylope(World* world, const CORDS pos, int age, int ini, int pow) {
	this->world = world;
	this->pos = pos;
	this->ini = ini;
	this->age = age;
	this->pow = pow;
}

const void Antylope::draw() { cout << ANTYLOPE; } 

const char Antylope::get_sign() { return ANTYLOPE; }

Antylope::~Antylope(){}

void Antylope::action() {
	DIRECTION dir;
	choose_diff_dir(dir);
	if (dir == UP && pos.y > 1 || dir == DOWN && pos.y < world->get_height() - 2 || dir == LEFT && pos.x > 1 || dir == RIGHT && pos.x < world->get_width() - 2) {
		if (next(dir, 2)->get_sign() == GROUND) {
			move(dir);
			move(dir);
		}
		else {
			move(dir);
			next(dir, 1)->collision(this);
			if (next(dir, 1)->get_sign() == GROUND) move(dir);
		}
	}
}

void Antylope::choose_diff_dir(DIRECTION& dir) {
	int temp;
	if (pos.x == 0 || pos.x == 1) {
		if (pos.y == 0) {
			temp = rand() % 2;
			dir = temp == 0 ? DOWN : RIGHT;
		}
		else if (pos.y == world->get_height() - 1) {
			temp = rand() % 2;
			dir = temp == 0 ? UP : RIGHT;
		}
		else {
			temp = rand() % 3;
			switch (temp) {
			case 0: dir = UP; break;
			case 1: dir = DOWN; break;
			case 2: dir = RIGHT; break;
			}
		}
	}
	else if (pos.x == world->get_width() - 1 || pos.x == world->get_width() - 2) {
		if (pos.y == 0) {
			temp = rand() % 2;
			dir = temp == 0 ? DOWN : LEFT;
		}
		else if (pos.y == world->get_height() - 1) {
			temp = rand() % 2;
			dir = temp == 0 ? UP : LEFT;
		}
		else
		{
			temp = rand() % 3;
			switch (temp) {
			case 0: dir = UP; break;
			case 1: dir = DOWN; break;
			case 2: dir = LEFT; break;
			}
		}
	}
	else if (pos.y == 0 || pos.y == 1) {
		temp = rand() % 3;
		switch (temp) {
		case 0: dir = RIGHT; break;
		case 1: dir = DOWN; break;
		case 2: dir = LEFT; break;
		}
	}
	else if (pos.y == world->get_height() - 1 || pos.y == world->get_height() - 2) {
		temp = rand() % 3;
		switch (temp) {
		case 0: dir = UP; break;
		case 1: dir = RIGHT; break;
		case 2: dir = LEFT; break;
		}
	}
	else {
		dir = (DIRECTION)(rand() % 4);
	}
}

void Antylope::reproduce(Org* collider) {
	Antylope* temp_a = dynamic_cast<Antylope*>(collider);
	DIRECTION dir = (DIRECTION)(rand() % 4);
	if (dir == UP && pos.y > 0 || \
		dir == DOWN && pos.y < (world->get_height() - 1) || \
		dir == RIGHT && pos.x < (world->get_width() - 1) || \
		dir == LEFT && pos.x > 0) {
		if (dynamic_cast<Ground*>(next(dir, 1))) {
			switch (dir) {
			case UP: ADDANTYLOPE(-1, 0); break;
			case DOWN: ADDANTYLOPE(1, 0); break;
			case RIGHT: ADDANTYLOPE(0, 1); break;
			case LEFT: ADDANTYLOPE(0, -1); break;
			}

		}
	}
}

void Antylope::collision(Org* collider) {
	int temp = rand() % 2;

	if (dynamic_cast<Antylope*>(collider)) {
		reproduce(collider);
	}
	else if (temp == 0) {
		world->log("A runs away");
		if (pos.x > 0 && SIGN(0, -1) == GROUND) move(LEFT);
		else if (pos.x < world->get_width() - 1 && SIGN(0, 1) == GROUND) move(RIGHT);
		else if (pos.y > 0 && SIGN(-1, 0) == GROUND) move(UP);
		else if (pos.y < world->get_height() - 1 && SIGN(1, 0) == GROUND) move(DOWN);
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
		temp += this->get_sign();
		temp += " kills ";
		temp += collider->get_sign();
		world->log(temp);
		world->world[collider->pos.y][collider->pos.x] = new Ground();
	}
}
