#include "engine.h"

int Engine::init(const std::string windowTitle, int width, int height, int gridSize, int numberOfShips, int shipSize, int numberOfInitialShots)
{
    m_window.create(sf::VideoMode(width, height), windowTitle);
    m_window.setVerticalSyncEnabled(true); // This means that the window will refresh the rendering buffers at the monitor's refresh rate. Prevents tearing and similar issues.
    m_width = width;
    m_height = height;

	m_game.init(gridSize, gridSize, numberOfShips, shipSize, numberOfInitialShots, &m_renderer);

    return 0;
}

void Engine::run()
{
    while(m_running && m_window.isOpen())
    {
        // No FPS time management for updating the game is needed as no physics are present, thus the game can run as fast as possible
        update();
        render();
    }
}

void Engine::windowEventsUpdate()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // Closing the window if needed
        if (event.type == sf::Event::Closed)
            m_window.close();

        // Processing the input events
        m_input.update(event);
    }
}

void Engine::update()
{
	windowEventsUpdate();
    m_game.update(m_running, m_input);
}

void Engine::render()
{
    m_window.clear();

    // Setting up the rendering queue
    m_game.render(&m_renderer, &m_window);

    // Rendering the queue
    m_renderer.flush(&m_window);
    m_window.display();
	m_renderer.clear();
}
