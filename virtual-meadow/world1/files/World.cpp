#include "headers.h"

World::World(const int width, const int height) {
	this->width = width;
	this->height = height;
	world = new Org * *[height];
	for (int i = 0; i < height; i++) world[i] = new Org * [width];
	for (int j = 0; j < height; j++) {
		for (int k = 0; k < width; k++) {
			world[j][k] = new Ground();
		}
	}
	this->info = "";
}

const void World::print_world() {
	for (int j = 0; j < height; j++) {
		for (int k = 0; k < width; k++) {
			world[j][k]->draw();
		}
		cout << endl;
	}
 }

void World::add_organism(Org* org, const CORDS pos) {
	if (dynamic_cast<Human*>(org))	this->human_alive = true;
	world[pos.y][pos.x] = org;
	if (organisms.size() == 0) organisms.push_front(org);
	else {
		for (auto temp : organisms) {
			if (org->get_ini() > temp->get_ini()) {
				auto it = find(organisms.begin(), organisms.end(), temp);
				organisms.insert(it, org);
				return;
			}
			else if (org->get_ini() == temp->get_ini()) {
				if (org->get_age() > temp->get_age()) {
					auto it = find(organisms.begin(), organisms.end(), temp);
					organisms.insert(it, org);
					return;
				}
			}
			else continue;
		}
		organisms.push_back(org);
	}
}

void World::start() {
	Human* human = new Human(this, { 1,1 }, 188555);
	add_organism(human, human->get_cords());
	Antylope* a1 = new Antylope(this, { 3,3 });
	add_organism(a1, a1->get_cords());
	Antylope* a2 = new Antylope(this, { this->width-3,this->height-3 });
	add_organism(a2, a2->get_cords());
	Borscht* b1 = new Borscht(this, { 15,15 });
	add_organism(b1, b1->get_cords());
	Borscht* b2 = new Borscht(this, { this->width - 15,this->height - 15 });
	add_organism(b2, b2->get_cords());
	Dandelion* d1 = new Dandelion(this, { 4,4 });
	add_organism(d1, d1->get_cords());
	Dandelion* d2 = new Dandelion(this, { this->width - 4,this->height - 4 });
	add_organism(d2, d2->get_cords());
	Fox* f1 = new Fox(this, { 3,8 });
	add_organism(f1, f1->get_cords());
	Fox* f2 = new Fox(this, { this->width - 3,this->height - 8 });
	add_organism(f2, f2->get_cords());
	Guarana* g1 = new Guarana(this, { 5,8 });
	add_organism(g1, g1->get_cords());
	Guarana* g2 = new Guarana(this, { this->width - 5,this->height - 8 });
	add_organism(g2, g2->get_cords());
	Sheep* s1 = new Sheep(this, { 6,1 });
	add_organism(s1, s1->get_cords());
	Sheep* s2 = new Sheep(this, { this->width - 6,this->height - 1 });
	add_organism(s2, s2->get_cords());
	Turtle* t1 = new Turtle(this, { 1,5 });
	add_organism(t1, t1->get_cords());
	Turtle* t2 = new Turtle(this, { this->width - 1,this->height - 5 });
	add_organism(t2, t2->get_cords());
	Wolf* w1 = new Wolf(this, { 8,4 });
	add_organism(w1, w1->get_cords());
	Wolf* w3 = new Wolf(this, { 8,5 });
	add_organism(w3, w3->get_cords());
	Wolf* w4 = new Wolf(this, { 8,6 });
	add_organism(w4, w4->get_cords());
	Wolf* w5 = new Wolf(this, { 7,4 });
	add_organism(w5, w5->get_cords());
	Wolf* w6 = new Wolf(this, { 6,4 });
	add_organism(w6, w6->get_cords());
	Wolf* w7 = new Wolf(this, { 8,3 });
	add_organism(w7, w7->get_cords());
	Sheep* s3 = new Sheep(this, { 8,4 });
	add_organism(s3, s3->get_cords());
	Wolf* w2 = new Wolf(this, { this->width - 8,this->height - 4 });
	add_organism(w2, w2->get_cords());
	Wolfberries* wb1 = new Wolfberries(this, { 4,8 });
	add_organism(wb1, wb1->get_cords());
	Wolfberries* wb2 = new Wolfberries(this, { this->width - 4,this->height - 8 });
	add_organism(wb2, wb2->get_cords());

}

void World::simulate(int ch) {
	
	switch (ch) {
	case UP:    next_turn(UP);    break;
	case DOWN:    next_turn(DOWN);  break;
	case RIGHT:    next_turn(RIGHT); break;
	case LEFT:    next_turn(LEFT);  break;
	}
	print_world();
	print_log();
	cout << endl;
}

void World::loop() {
	Sleep(1000);
	if (GetAsyncKeyState(VK_UP))
		simulate(UP);
	if (GetAsyncKeyState(VK_DOWN))
		simulate(DOWN);
	if (GetAsyncKeyState(VK_LEFT))
		simulate(LEFT);
	if (GetAsyncKeyState(VK_RIGHT))
		simulate(RIGHT);
}

void World::play() {
	start();
	print_world();
	cout << endl;
	while (is_human_alive()) {
		loop();
	}
	cout << "Game Over!";
}

void World::next_turn(DIRECTION dir) {
	list<Org*> toRemove;
	for (Org* temp : organisms) {
		if (temp->get_age() > 0) {
			if (temp->get_sign() == world[temp->pos.y][temp->pos.x]->get_sign())
				if (dynamic_cast<Human*>(temp)) {
					Human* temp_h = dynamic_cast<Human*>(temp);
					temp_h->action(dir);
				}
				else temp->action();
		}
		else if (dynamic_cast<Borscht*>(temp)) {
			Borscht* temp_p = dynamic_cast<Borscht*>(temp);
			temp_p->burn();
		}

	}
	for (Org* temp : organisms)
		if (dynamic_cast<Ground*>(world[temp->pos.y][temp->pos.x]))
			toRemove.push_back(temp);
	for (Org* temp : toRemove) {
		if (dynamic_cast<Human*>(temp)) {
			Human* temp_h = dynamic_cast<Human*>(temp);
			if (temp_h->getindex() == 0 && temp_h->turns_left() > 0) {
				temp_h->immortal();
				world[temp_h->pos.y][temp_h->pos.x] = temp_h;
			}
			else {
				this->human_alive = false;
				delete temp;
				organisms.remove(temp);
			}
		}
		else organisms.remove(temp);
		log_a(to_string(organisms.size()));
	}

	while (toRemove.size() != 0) toRemove.pop_back();
	for (Org* temp : organisms) temp->age++;
}

int World::get_height() { return this->height; }

int World::get_width() { return this->width; }

const void World::print_log() { cout << info; this->info = ""; }

const void World::log(string _log) { this->info += _log; this->info += '\n'; }

const void World::log_a(string _log) { this->logAdmin += _log; this->logAdmin += '\n'; }

const string World::get_log() { return info; }

void World::start_human_ability() {
	for (Org* temp : organisms) {
		if (dynamic_cast<Human*> (temp)) {
			Human* temp_h = dynamic_cast<Human*>(temp);
			temp_h->use_ability();
		}
	}
}

bool World::is_human_alive() { return human_alive; }

World::~World() {
	for (int i = 0; i < this->height; i++) delete[] world[i];
	delete[] world;
}

const int World::amount_of_organisms() { return organisms.size(); }


