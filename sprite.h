#ifndef SPRITE_H
#define SPRITE_H

#include <SFML\Graphics.hpp>

#include "renderer.h"

class Sprite
{
public:
	void init(int width, int height, const std::string textureName, Renderer *renderer);
	void draw(Renderer *renderer);
	void draw(float x, float y, Renderer *renderer);

	void setPosition(sf::Vector2f& pos);
	sf::Vector2f& getPosition();

private:
	sf::Vector2f m_pos, m_dimensions;
	sf::Vector2u m_textureSize;

	// Draw data
	sf::VertexArray *m_vertexArrayDrawable;
	sf::Vertex m_spriteVertices[4];
};

#endif
