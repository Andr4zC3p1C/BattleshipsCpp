#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "game.h"

int Game::init(int gridWidth, int gridHeight, int numberOfInitialShips, int shipLength, int numberOfInitialShots, Renderer *renderer)
{
	// Loading all the textures for the renderer; file names hardcoded into the source code directly here in function calls: (FOR NOW JUST RANDOM TEST TEXTURES THAT WONT WORK CUZ THEY AINT THERE)
	/*
	renderer->loadTextureFromFile("sea");
	renderer->loadTextureFromFile("splah");
	renderer->loadTextureFromFile("explosion");
	*/

    // Initializes the random number generator of the standard C library STD; we use time(0), so that each time the game is ran, the seed for the generator is different, since time is different
    srand(time(0));

    // Initializes the grid
    m_grid = (int*)malloc(gridWidth*gridHeight*sizeof(unsigned char));
    m_width = gridWidth;
    m_height = gridHeight;

    // Initializes the game parameters
    m_numberOfInitialShips = numberOfInitialShips;
    m_numberOfInitialShots = numberOfInitialShots;
    m_shipLength = shipLength;

    // Loads the textures from files

    start();

	return 0;
}

void Game::update(bool& running, Input& input)
{
    if(!m_gameOver)
    {
        // Checking if the left mouse button has been clicked
        if(input.isButtonClicked())
        {
            // Testing if it works like we want: (WORKS PERFECTLY!)
			std::cout << "Click!\n";
        }

		if (input.isButtonDown())
		{
			// To see the difference between click and if we don't implement the click method:
			std::cout << "Down!\n"; // (You can see tha there are many more Down!-s as there are Click!-s, which would be a problem as too many shots would be fired!)
		}
    }
    else
    {

    }
}

void Game::render(Renderer *renderer)
{
    if(!m_gameOver)
    {
        // Rendering the grid

        // Rendering the shots left text

        // Rendering the hits text
    }
    else
    {
        // Rendering the game over text

        // Rendering the score text; number of misses and hits

        // Rendering the restart button

        // Rendering the quit button
    }
}

void Game::start()
{
    m_gameOver = false;
    m_shotsLeft = m_numberOfInitialShots;
    m_hits = 0;

    // Clearing the whole grid to SEA
    for(int x = 0; x < m_width; x++)
        for(int y = 0; y < m_height; y++)
        {
            m_grid[x + y*m_height] = SEA;
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