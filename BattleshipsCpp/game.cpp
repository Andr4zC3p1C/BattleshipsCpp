#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "game.h"

int Game::init(int gridWidth, int gridHeight, int numberOfInitialShips, int shipLength, int numberOfInitialShots, Renderer *renderer, int screenWidth, int screenHeight)
{
	// Initializes the random number generator of the standard C library STD; we use time(0), so that each time the game is ran, the seed for the generator is different, since time is different
	srand(time(0));

	// Initializes the grid
	m_grid = (int*)malloc(gridWidth*gridHeight * sizeof(int));
	m_width = gridWidth;
	m_height = gridHeight;

	// Initializes the game parameters
	m_numberOfInitialShips = numberOfInitialShips;
	m_numberOfInitialShots = numberOfInitialShots;
	m_shipLength = shipLength;

	//Other
	m_screenHeight = screenHeight;
	m_screenWidth = screenWidth;

	// Starts the game, i.e. sets all the game parameters
	start();

	// Loading all the textures for the renderer
	renderer->loadTextureFromFile("sea");
	renderer->loadTextureFromFile("miss");
	renderer->loadTextureFromFile("hit");

	// Initilaizing the sprites
	m_hit.init(TILE_SIZE, TILE_SIZE, "hit", renderer);
	m_miss.init(TILE_SIZE, TILE_SIZE, "miss", renderer);
	m_sea.init(TILE_SIZE, TILE_SIZE, "sea", renderer);

	// Initializing the text objects
	if(!m_font.loadFromFile("res/arial.ttf"))
	{
		return 1;
	}

	m_shotsLeftText.setFont(m_font);
	m_shotsLeftText.setString("Shots left: " + std::to_string(m_shotsLeft));
	m_shotsLeftText.setCharacterSize(25);
	m_shotsLeftText.setPosition(sf::Vector2f(m_width*TILE_SIZE + 15, 100));
	m_shotsLeftText.setStyle(sf::Text::Bold);

	m_shipsLeftText.setFont(m_font);
	m_shipsLeftText.setString("Ships left: " + std::to_string(m_numberOfInitialShips - m_hits / m_shipLength));
	m_shipsLeftText.setCharacterSize(25);
	m_shipsLeftText.setPosition(sf::Vector2f(m_width*TILE_SIZE + 15, 200));
	m_shipsLeftText.setStyle(sf::Text::Bold);

	// Restart button text
	m_restartButtonText.setFont(m_font);
	m_restartButtonText.setString("RESTART");
	m_restartButtonText.setCharacterSize(35);
	m_restartButtonText.setStyle(sf::Text::Bold);

	float restartW = m_restartButtonText.getGlobalBounds().width;
	m_restartButtonText.setPosition(sf::Vector2f(m_screenWidth / 2.0f - restartW / 2.0f, 400));

	// Quit button text
	m_quitButtonText.setFont(m_font);
	m_quitButtonText.setString("QUIT");
	m_quitButtonText.setCharacterSize(35);
	m_quitButtonText.setStyle(sf::Text::Bold);

	float quitW = m_quitButtonText.getGlobalBounds().width;
	m_quitButtonText.setPosition(sf::Vector2f(m_screenWidth / 2.0f - quitW / 2.0f, 480));

	// Game over text
	m_gameOverText.setFont(m_font);
	m_gameOverText.setString("GAME OVER!");
	m_gameOverText.setCharacterSize(70);
	m_gameOverText.setStyle(sf::Text::Bold);
	m_gameOverText.setFillColor(sf::Color::Cyan);

	float gameOverW = m_gameOverText.getGlobalBounds().width;
	m_gameOverText.setPosition(sf::Vector2f(m_screenWidth / 2.0f - gameOverW / 2.0f, 100));

	return 0;
}

void Game::update(bool& running, Input& input)
{
	static float mouseX;
	static float mouseY;

	mouseX = input.getMousePosition().x;
	mouseY = input.getMousePosition().y;

    if(!m_gameOver)
    {
        // Checking if the left mouse button has been clicked
        if(input.isButtonClicked())
        {
			// Check if mouse click is out of bounds or not (Y doesn't matter as the grid takes up the whole screen in the y direction)
			if (mouseX <= TILE_SIZE * m_width)
			{
				m_shotsLeft--;// We used one shot
				m_shotsLeftText.setString("Shots left: " + std::to_string(m_shotsLeft));

				// Getting the tile position in the grid
				int tileX = (int)(mouseX / (float)TILE_SIZE);
				int tileY = (int)(mouseY / (float)TILE_SIZE);

				// IF we missed OR hit a ship
				if (m_grid[tileX + tileY * m_width] == SEA)
					m_grid[tileX + tileY * m_width] = MISS;
				else if (m_grid[tileX + tileY * m_width] == SHIP)
				{
					m_grid[tileX + tileY * m_width] = HIT;
					m_hits++;
				}

				m_shipsLeftText.setString("Ships left: " + std::to_string(m_numberOfInitialShips - m_hits / m_shipLength));
			}
        }

		// Checking if the game has ended
		if (m_shotsLeft == 0 || m_hits  == m_numberOfInitialShips * m_shipLength)
		{
			m_gameOver = true;

			float w = m_shotsLeftText.getGlobalBounds().width;
			m_shotsLeftText.setPosition(sf::Vector2f(m_screenWidth / 2.0f - w / 2.0f, 230));

			w = m_shipsLeftText.getGlobalBounds().width;
			m_shipsLeftText.setPosition(sf::Vector2f(m_screenWidth / 2.0f - w / 2.0f, 280));
		}
    }
    else
    {
		static sf::FloatRect restartBounds;
		restartBounds = m_restartButtonText.getGlobalBounds();

		static sf::FloatRect quitBounds;
		quitBounds = m_quitButtonText.getGlobalBounds();

		// Check if mouse is hovering over the texts
		m_restartHover = (mouseX >= restartBounds.left && mouseX <= restartBounds.left + restartBounds.width)
						&& (mouseY >= restartBounds.top && mouseY <= restartBounds.top + restartBounds.height);

		m_quitHover = (mouseX >= quitBounds.left && mouseX <= quitBounds.left + quitBounds.width)
						&& (mouseY >= quitBounds.top && mouseY <= quitBounds.top + quitBounds.height);

		m_quitButtonText.setFillColor(sf::Color(180, 180, 180, 255));
		m_restartButtonText.setFillColor(sf::Color(180, 180, 180, 255));

		if (m_restartHover)
		{
			m_restartButtonText.setFillColor(sf::Color::Green);

			if (input.isButtonClicked())
				start();
		}
		else if(m_quitHover)
		{
			m_quitButtonText.setFillColor(sf::Color::Green);

			if (input.isButtonClicked())
				running = false;
		}
    }
}

void Game::render(Renderer *renderer, sf::RenderWindow *window)
{
    if(!m_gameOver)
    {
        // Rendering the grid
		for (int x=0; x < m_width; x++)
			for (int y = 0; y < m_height; y++)
			{
				m_sea.draw(x*TILE_SIZE, y*TILE_SIZE, renderer);

				if (m_grid[x+y*m_width] == HIT)
				{
					m_hit.draw(x*TILE_SIZE, y*TILE_SIZE, renderer);
				}
				else if (m_grid[x + y * m_width] == MISS)
				{
					m_miss.draw(x*TILE_SIZE, y*TILE_SIZE, renderer);
				}
			}

        // Rendering the shots left text
		window->draw(m_shotsLeftText);

        // Rendering the hits text
		window->draw(m_shipsLeftText);
    }
    else
    {
        // Rendering the game over text
		window->draw(m_gameOverText);

		// Rendering the shots left text
		window->draw(m_shotsLeftText);

		// Rendering the hits text
		window->draw(m_shipsLeftText);

        // Rendering the restart button
		window->draw(m_restartButtonText);

        // Rendering the quit button
		window->draw(m_quitButtonText);
    }
}

void Game::start()
{
    m_gameOver = false;
    m_shotsLeft = m_numberOfInitialShots;
    m_hits = 0;

	m_shotsLeftText.setString("Shots left: " + std::to_string(m_shotsLeft));
	m_shotsLeftText.setPosition(sf::Vector2f(m_width*TILE_SIZE + 15, 100));

	m_shipsLeftText.setString("Ships left: " + std::to_string(m_numberOfInitialShips - m_hits / m_shipLength));
	m_shipsLeftText.setPosition(sf::Vector2f(m_width*TILE_SIZE + 15, 200));

    // Clearing the whole grid to SEA
    for(int x = 0; x < m_width; x++)
        for(int y = 0; y < m_height; y++)
        {
            m_grid[x + y*m_width] = SEA;
        }

    generateShipsOnGrid();

}

void Game::generateShipsOnGrid()
{
    int counter = 0;
    int x, y, dir;

    while(counter < m_numberOfInitialShips){
        x = rand() % m_width;
        y = rand() % m_height;
        dir = rand() % 4; // 4 directions: up, left, down, right

        if(shipPositionValid(x, y, dir)){
            for(int j=0; j < m_shipLength; j++)
            {
                // Declaring the position of the shp in grid
                m_grid[x + y*m_width] = SHIP;

                if(dir == UP)
                {
                    y++;
                }
                else if(dir == LEFT)
                {
                    x--;
                }
                else if(dir == DOWN)
                {
                    y--;
                }
                else if(dir == RIGHT)
                {
                    x++;
                }
            }

            counter++;
        }
    }
}

bool Game::shipPositionValid(int& x, int& y,int& direction)
{
    // This function makes sure that we do not generate a ship outside the grid and that two ships do not collide with each other
    int temp_x = x;
    int temp_y = y;

    for(int j=0; j < m_shipLength; j++)
    {
        // Checking if the curent part of the ship sticks out of the grid
        if(temp_x < 0 || temp_x >= m_width || temp_y < 0 || temp_y >= m_height)
            return false;

        // Checking if the the current part of the ships colides with another ship
        if(m_grid[temp_x + temp_y*m_width] == SHIP)
            return false;

        // Calculating the position of the next part of the ship
        if(direction == UP)
        {
            temp_y++;
        }
        else if(direction == LEFT)
        {
            temp_x--;
        }
        else if(direction == DOWN)
        {
            temp_y--;
        }
        else if(direction == RIGHT)
        {
            temp_x++;
        }
    }

    return true;
}

Game::~Game()
{
	free(m_grid);
}
