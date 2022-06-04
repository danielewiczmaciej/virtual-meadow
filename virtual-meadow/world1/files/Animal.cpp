#include "headers.h"

#define SIGN(Y,X) world->world[pos.y + Y][pos.x + X]->get_sign()
#define COL_SIGN(Y,X) world->world[collider->pos.y + Y][collider->pos.x + X]->get_sign()
#define POS(Y,X) world->world[pos.y + Y][pos.x + X]
#define COL_POS(Y,X) world->world[collider->.pos.y + Y][collider->pos.x + X]

Animal::Animal() {
}

Animal::Animal(World* world, const CORDS pos) {
	this->world = world;
	this->pos = pos;
}

Animal::Animal(World* world, const CORDS pos, int age, int ini, int pow) {
	this->world = world;
	this->pos = pos;
	this->age = age;
	this->ini = ini;
	this->pow = pow;
}

void Animal::action() {
	DIRECTION dir;
	choose_diff_dir(dir);
	if (dir == UP && pos.y > 0 || dir == DOWN && pos.y < this->world->get_height() - 1 || dir == LEFT && pos.x>0 || dir == RIGHT && pos.x < this->world->get_width() - 1) {
		if (dynamic_cast<Ground*>(next(dir, 1))) {
			move(dir);
		}
		else {
			next(dir, 1)->collision(this);
			if (dynamic_cast<Ground*>(next(dir, 1))) move(dir);
		}
	}
}

void Animal::reproduce(Org* mate) {}

Org* Animal::next(const DIRECTION dir, const int dist) {
	switch (dir) {
	case UP:
		return POS(-dist, 0);
		break;
	case DOWN:
		return POS(dist, 0);
		break;
	case LEFT:
		return POS(0, -dist);
		break;
	case RIGHT:
		return POS(0, dist);
		break;
	}
}

void Animal::move(DIRECTION dir) {
	switch (dir) {
	case UP:
		if (pos.y > 0) {
			POS(-1, 0) = POS(0, 0);
			POS(0, 0) = new Ground();
			this->pos.y--;
		}
		break;
	case DOWN:
		if (pos.y < world->get_height()-1) {
			POS(1, 0) = POS(0, 0);
			POS(0, 0) = new Ground();
			this->pos.y++;
		}
		break;
	case LEFT:
		if (pos.x > 0) {
			POS(0, -1) = POS(0, 0);
			POS(0, 0) = new Ground();
			this->pos.x--;
		}
		break;
	case RIGHT:
		if (pos.x < world->get_width()-1) {
			POS(0, 1) = POS(0, 0);
			POS(0, 0) = new Ground();
			this->pos.x++;
		}
		break;
	}
}

void Animal::choose_diff_dir(DIRECTION& dir) {
	int temp;

	if (pos.x == 0) {
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
	else if (pos.x == world->get_width() - 1) {
		if (pos.y == 0) {
			temp = rand() % 2;
			dir = temp == 0 ? DOWN : LEFT;
		}
		else if (pos.y == world->get_height() - 1) {
			temp = rand() % 2;
			dir = temp == 0 ? UP : LEFT;
		}
		else {
			temp = rand() % 3;
			switch (temp) {
			case 0: dir = UP; break;
			case 1: dir = DOWN; break;
			case 2: dir = LEFT; break;
			}
		}
	}
	else if (pos.y == 0) {
		temp = rand() % 3;
		switch (temp) {
		case 0: dir = DOWN; break;
		case 1: dir = LEFT; break;
		case 2: dir = RIGHT; break;
		}
	}
	else if (pos.y == world->get_height() - 1) {
		temp = rand() % 3;
		switch (temp) {
		case 0: dir = UP; break;
		case 1: dir = LEFT; break;
		case 2: dir = RIGHT; break;
		}
	}
	else dir = (DIRECTION)(rand() % 4);
}

void Animal::collision(Org* collider) {
	if (collider->get_sign() == this->get_sign()) {
		reproduce(collider);
	}
	else if (collider->get_pow() > this->get_pow()) {
		string temp = "";
		temp += collider->get_sign();
		temp += " defeats ";
		temp += this->get_sign();
		world->log(temp);
		world->world[this->pos.y][this->pos.x] = new Ground();
	}
	else {
		string temp = "";
		temp += collider->get_sign();
		temp += " gets defeated by ";
		temp += this->get_sign();
		world->log(temp);
		world->world[collider->pos.y][collider->pos.x] = new Ground();
	}
}

const void Animal::draw() { cout << 'a'; }
const char Animal::get_sign() { return 'a'; }
Animal::~Animal() {}