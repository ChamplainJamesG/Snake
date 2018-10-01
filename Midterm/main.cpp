/*
Jimmy Griffiths
EGP - 310-01
Smurfs using mouse input
*/
#include <iostream>
#include <cassert>
#include <string>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include "GraphicsLib.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsLib\Color.h"

#include <random>
#include <ctime>
#include <Game.h>

#include "EventSystem.h"

using namespace std;

int main()
{
	ifstream in;
	in.open("INIT.init");
	Game game = Game(EventSystem::getInstance());
	int width, height;
	in >> width;
	in >> height;
	
	game.init(width, height, in);
	game.doLoop();

	game.cleanup();
	gMemoryTracker.reportAllocations(std::cout);
	system("pause");

}