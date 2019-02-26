#include "engine.h"

int Engine::init(const std::string windowTitle, const int width, const int height)
{
    m_window.create(sf::VideoMode(width, height), windowTitle);
    m_window.setVerticalSyncEnabled(true); // This means that the window will refresh the rendering buffers at the monitor's refresh rate. Prevents tearing and similar issues.
    m_width = width;
    m_height = height;

    return 0;
}

void Engine::run()
{
    timer = clock();
    while(running && m_window.isOpen())
    {
        // No FPS time management for updating the game is needed as no physics are present, thus the game can run as fast as possible
        update();
        render();
    }
}

void Engine::windowEventsUpdate()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        // Closing the window if needed
        if (event.type == sf::Event::Closed)
            window.close();

        // Processing the input events
        m_input(event);
    }
}

void Engine::update()
{
    m_game.update(m_running, m_input);
}

void Engine::render()
{
    // Setting up the rendering queue
    m_game.render();

    // Rendering the queue
    m_window.clear();
    m_renderer.draw(&m_window);
    m_window.display();
}
