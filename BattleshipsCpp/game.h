#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "renderer.h"
#include "sprite.h"
#include "input.h"

// The macros for the values of the grid, just to make the code more readable
#define SEA 0
#define SHIP 1
#define MISS 2
#define HIT 3

// The macros for the directions for the ships
#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

// Other macros
#define TILE_SIZE 64

class Game
{
public:
    int init(int gridWidth, int gridHeight, int numberOfInitialShips, int shipLength, int numberOfInitialShots, Renderer *renderer, int screenWidth, int screenHeight);
    void update(bool& running, Input& input);
    void render(Renderer *renderer, sf::RenderWindow *window);

	~Game();

private:
    // The grid data
    int *m_grid;
    int m_width, m_height;
	int m_screenWidth, m_screenHeight;
    
    // The game data
    bool m_gameOver;
    int m_numberOfInitialShips;
    int m_shipLength;
    int m_numberOfInitialShots;
    int m_shotsLeft;
    int m_hits;

    // Sprites
	Sprite m_hit, m_miss, m_sea;
	sf::Text m_shotsLeftText, m_shipsLeftText, m_restartButtonText, m_quitButtonText, m_gameOverText;
	sf::Font m_font;
	sf::String m_shotsLeftString, m_shipsLeftString;
	bool m_restartHover = 0;
	bool m_quitHover = 0;

    // Functions that are only relavent inside the game class
    void start();
    void generateShipsOnGrid();
    bool shipPositionValid(int& x, int& y,int& direction);
};

#endif