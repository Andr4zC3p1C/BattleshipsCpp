#include "engine.h"

int main()
{
	int gridSize = 10;

    Engine engine;
    engine.init("Battleships", TILE_SIZE*gridSize + 200, TILE_SIZE*gridSize, gridSize, 5, 4, 50);
    engine.run();

    return 0;
}