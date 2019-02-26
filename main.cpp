#include "engine.h"

int main()
{
    Engine engine;
    engine.init("Battleships", 1280, 720);
    engine.run();

    return 0;
}