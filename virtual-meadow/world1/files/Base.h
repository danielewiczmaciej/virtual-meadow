#pragma once
#include <iostream>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <ctime>
#include <algorithm>
#include <list>
#include <string>
#include <windows.h>
#include <fstream>
#include <WinUser.h>
using namespace std;

#define GROUND '+'
#define INDEX 188555
#define NAME "Maciej"
#define SURNAME "Danielewicz"
#define HUMAN 'H'
#define SPECIES 10
#define WOLF 'W'
#define SHEEP 'S'
#define FOX 'F'
#define TURTLE 'T'
#define ANTYLOPE 'A'

#define GRASS '.'
#define DANDELION '@'
#define GUARANA '#'
#define WOLF_BERRIES '*'
#define BORSCHT '$'

#define ESC 0x1b			
#define ARROW_UP 72		
#define ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75
#define ENTER 0x0d 

enum DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct CORDS {
	int x;
	int y;
};
