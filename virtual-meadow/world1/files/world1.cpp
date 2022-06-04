#include <iostream>
#include "headers.h"
#include "Base.h"
int main()
{
    int x, y;
    cout << "Put in dimensions: ";
    cin >> x >> y;
    World* world = new World(x, y);
    world->play();
    world->~World();
    return 0;
}

