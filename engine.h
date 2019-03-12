#ifndef ENGINE_H
#define ENGINE_H

#include <time.h>
#include <string.h>
#include <SFML/Graphics.hpp>

#include "renderer.h"
#include "game.h"
#include "input.h"

class Engine
{
public:
	int init(const std::string windowTitle, int width, int height, int gridSize, int numberOfShips = 5, int shipSize = 4, int numberOfInitialShots = 25); // It has return type int, so that if an error occurs while loading things, we can report
    void run();
    
private:
    // Game variables
    bool m_running = true;
    Game m_game;
    Input m_input;

    // Graphics variables
    sf::RenderWindow m_window;
    unsigned int m_width, m_height;
    Renderer m_renderer;

    void update();
	void windowEventsUpdate();
    void render();
};

#endif