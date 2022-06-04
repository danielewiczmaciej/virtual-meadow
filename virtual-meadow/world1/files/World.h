#pragma once
#include <iostream>
#include "Base.h"
#include "Org.h"
#include "headers.h"
class World
{
private:
	int width;
	int height;
	list<Org*> organisms;
	string info;
	string logAdmin;
	list<Org*> toAdd;
	bool human_alive;
public:
	Org*** world;
	World(const int _width, const int _height);
	void add_organism(Org* _org, CORDS _position);
	void start();
	void simulate(int ch);
	void loop();
	void play();
	void next_turn(DIRECTION);
	int get_height();
	int get_width();
	bool is_human_alive();
	const void print_world();
	const void print_log();
	const void log(string _log);
	const void log_a(string _log);
	void start_human_ability();
	const string get_log();
	~World();
	const int amount_of_organisms();
};