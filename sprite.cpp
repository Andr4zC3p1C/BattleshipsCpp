#include "sprite.h"

void Sprite::init(int width, int height, const std::string textureName, Renderer *renderer)
{
	m_dimensions = sf::Vector2f(width, height);
	m_pos = sf::Vector2f(0, 0);

	sf::Texture *tex = renderer->getTexture(textureName);
	m_textureSize = tex->getSize();
	m_vertexArrayDrawable = renderer->getVertexArrayPointer(textureName);

	// Setting up the vertices in clockwise order
	m_spriteVertices[0] = sf::Vertex(sf::Vector2f(m_pos.x, m_pos.y), sf::Vector2f(0,0));
	m_spriteVertices[1] = sf::Vertex(sf::Vector2f(m_pos.x, m_pos.y + height), sf::Vector2f(0, m_textureSize.y));
	m_spriteVertices[2] = sf::Vertex(sf::Vector2f(m_pos.x + width, m_pos.y + height), sf::Vector2f(m_textureSize.x, m_textureSize.y));
	m_spriteVertices[3] = sf::Vertex(sf::Vector2f(m_pos.x + width, m_pos.y), sf::Vector2f(m_textureSize.x, 0));
}

void Sprite::draw(Renderer *renderer)
{
	// Append the vertices in clockwise order.
	for(int i=0; i < 4; i++)
		m_vertexArrayDrawable->append(m_spriteVertices[i]);
}

void Sprite::setPosition(sf::Vector2f& pos)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;

	// Updating the vertices positions
	m_spriteVertices[0].position.x = m_pos.x;
	m_spriteVertices[0].position.y = m_pos.y;

	m_spriteVertices[1].position.x = m_pos.x;
	m_spriteVertices[1].position.y = m_pos.y + m_dimensions.y;
					 
	m_spriteVertices[2].position.x = m_pos.x + m_dimensions.x;
	m_spriteVertices[2].position.y = m_pos.y + m_dimensions.y;
					 
	m_spriteVertices[2].position.x = m_pos.x + m_dimensions.x;
	m_spriteVertices[2].position.y = m_pos.y;
}

sf::Vector2f& Sprite::getPosition()
{
	return m_pos;
}