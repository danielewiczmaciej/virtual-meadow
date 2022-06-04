#include "headers.h"

#define SIGN(Y,X) world->world[pos.y + Y][pos.x + X]->get_sign()
#define COL_SIGN(Y,X) world->world[collider->pos.y + Y][collider->pos.x + X]->get_sign()
#define CPOS(Y,X)  world->world[collider->pos.y + Y][collider->pos.x + X]
#define POS(Y,X)  world->world[pos.y + Y][pos.x + X]


Human::Human() {}

Human::Human(World* world, const CORDS pos, const int index) {
	this->world = world;
	this->pos = pos;
	this->pow = 5;
	this->ini = 4;
	this->id = index % 5;
}

Human::Human(World* world, const CORDS pos, int age, int ini, int pow, int id, int turnsleft) {
	this->world = world;
	this->pos = pos;
	this->pow = pow;
	this->age = age;
	this->ini = ini;
	this->id = id;
	this->turns = turnsleft;
}

const void Human::draw() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, 12);
	cout << HUMAN;
	SetConsoleTextAttribute(console, 15);
}

const char Human::get_sign() { return HUMAN; }

const int Human::turns_left() { return turns; }

void Human::use_ability() {
	cout << "H tries to make himself immortal!" << endl;
	if (turns == 0) {
		turns = 5;
		cout << "Luckily, he succeedes(what a relief ;D)" << endl;
	}
	else cout << "But he's not ready yet, better prepare for battle -|----" << endl;
}

Human::~Human() {}

void Human::action(DIRECTION dir) {
	string temp = "";
	temp += this->get_sign();
	if (turns != 0) temp += " is still immortal for the next " + to_string(turns) + " turns and ";
	switch (dir) {
	case UP: temp += " goes up!"; break;
	case DOWN: temp += " goes down!"; break;
	case LEFT: temp += " goes left!"; break;
	case RIGHT: temp += " goes right!"; break;
	}
	if (dir == UP && pos.y > 0 || dir == DOWN && pos.y < world->get_height() - 1 || dir == LEFT && pos.x > 0 || dir == RIGHT && pos.x < world->get_width() - 1) {
		world->log(temp);
		if (dynamic_cast<Ground*>(next(dir, 1))) move(dir);
		else {
			if (turns > 0) {
				if (next(dir, 1)->get_pow() > this->get_pow()) immortal();
			}
			next(dir, 1)->collision(this);
			if (dynamic_cast<Ground*>(next(dir, 1))) move(dir);
		}
		if (turns != 0) turns--;
	}
}

void Human::collision(Org* collider) {
	if (turns > 0) {
		string temp = "";
		temp += this->get_sign();
		temp += " is invincible for the next ";
		temp += to_string(turns);
		temp += " turns! Get lost ;)";
		immortal();
	}
	else {
		if (collider->get_pow() > this->get_pow()) {
			string temp = "";
			temp += collider->get_sign();
			temp += " overpowers ";
			temp += this->get_sign();
			world->log(temp);
			world->world[this->pos.y][this->pos.x] = new Ground();
		}
		else {
			string temp = "";
			temp += collider->get_sign();
			temp += " attacks stonger ";
			temp += this->get_sign();
			world->log(temp);
			world->world[collider->pos.y][collider->pos.x] = new Ground();
		}
	}
}

Org* Human::next(const DIRECTION dir, const int distance) {
	switch (dir) {
	case UP:
		return world->world[pos.y - distance][pos.x];
		break;
	case DOWN:
		return world->world[pos.y + distance][pos.x];
		break;
	case LEFT:
		return world->world[pos.y][pos.x - distance];
		break;
	case RIGHT:
		return world->world[pos.y][pos.x + distance];
		break;
	}
}

Org* Human::next(Org* collider, DIRECTION dir, const int distance) {
	switch (dir) {
	case UP: return CPOS(-1, 0);	break;
	case DOWN: return CPOS(1, 0); break;
	case RIGHT:	return CPOS(0, 1); break;
	case LEFT: return CPOS(0, -1); break;
	}
}

void Human::move(DIRECTION dir) {
	switch (dir) {
	case UP:
		if (pos.y == 0) break;
		world->world[pos.y - 1][pos.x] = world->world[pos.y][pos.x];
		world->world[pos.y][pos.x] = new Ground();
		this->pos.y--;
		break;
	case DOWN:
		if (pos.y == world->get_height() - 1) break;
		world->world[pos.y + 1][pos.x] = world->world[pos.y][pos.x];
		world->world[pos.y][pos.x] = new Ground();
		this->pos.y++;
		break;
	case LEFT:
		if (pos.x == 0) break;
		world->world[pos.y][pos.x - 1] = world->world[pos.y][pos.x];
		world->world[pos.y][pos.x] = new Ground();
		this->pos.x--;
		break;
	case RIGHT:
		if (pos.x == world->get_width() - 1) break;
		world->world[pos.y][pos.x + 1] = world->world[pos.y][pos.x];
		world->world[pos.y][pos.x] = new Ground();
		this->pos.x++;
		break;
	}
}

void Human::move(Org* collider, DIRECTION dir) {
	switch (dir) {
	case UP:
		if (collider->pos.y == 0) break;
		CPOS(-1, 0) = CPOS(0, 0);
		CPOS(0, 0) = new Ground();
		collider->pos.y--;
		break;
	case DOWN:
		if (collider->pos.y == world->get_height() - 1) break;
		CPOS(1, 0) = CPOS(0, 0);
		CPOS(0, 0) = new Ground();
		collider->pos.y++;
		break;
	case LEFT:
		if (collider->pos.x == 0) break;
		CPOS(0, -1) = CPOS(0, 0);
		CPOS(0, 0) = new Ground();
		collider->pos.x--;
		break;
	case RIGHT:
		if (collider->pos.x == world->get_width() - 1) break;
		CPOS(0, 1) = CPOS(0, 0);
		CPOS(0, 0) = new Ground();
		collider->pos.x++;
		break;
	}
}

void Human::immortal() {
	world->log("H is immortal!");
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
		case UP: move(UP);	break;
		case DOWN: move(DOWN); break;
		case RIGHT: move(RIGHT); break;
		case LEFT: move(LEFT); break;
		}
	}
}