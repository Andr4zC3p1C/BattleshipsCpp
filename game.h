#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <vector.h>

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

class Game
{
public:
    int init(int gridWidth, int gridHeight, int numberOfInitialShips, int shipLength, int numberOfInitialShots);
    void update(bool& running, Input& input);
    void render(sf::RenderWindow *window);

private:
    // The grid data
    int *m_grid;
    int m_width;
    int m_height;
    
    // The game data
    bool m_gameOver;
    int m_numberOfInitialShips;
    int m_shipLength;
    int m_numberOfInitialShots;
    int m_shotsLeft;
    int m_hits;

    // Tempoprary prototype graphics that are SLOW
    std::vector<sf::Texture> m_textures;
    sf::Sprite m_currentTile;

    // Functions that are only relavent inside the game class
    void start();
    void generateShipsOnGrid();
    bool shipPositionValid(int& x, int& y,int& direction);
};

#endif