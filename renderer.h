#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <utility>

class Renderer
{
public:
	void loadTextureFromFile(const std::string textureName);
    void flush(sf::RenderWindow *window);
	void clear();

	sf::VertexArray* getVertexArrayPointer(const std::string textureName);
	sf::Texture* getTexture(const std::string textureName);

private:
	std::unordered_map<std::string, std::pair<sf::Texture, sf::VertexArray>> m_data;
};

#endif