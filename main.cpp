#include "engine.h"

int main()
{
	int gridSize = 10;

    Engine engine;
    engine.init("Battleships", TILE_SIZE*gridSize + 100, TILE_SIZE*gridSize, gridSize);
    engine.run();

    return 0;
}