#include "renderer.h"

void Renderer::loadTextureFromFile(const std::string textureName)
{
	// The texture that will be the first argument in the pair
	sf::Texture tex;
	tex.loadFromFile("res/" + textureName + ".png");

	m_data.emplace(textureName, std::make_pair(tex, sf::VertexArray(sf::Quads)));
	m_drawOrder.push_back(textureName);
}

void Renderer::flush(sf::RenderWindow *window)
{
	// Iterating through all the elements of the map
	for (int i = 0; i < m_drawOrder.size(); i++)
	{
	    auto it = m_data.find(m_drawOrder[i]);

		// Drawing each vertex array that depends on each texture (The data of the vertex array and the texture gets sent to the GPU memory and processed through the shader pipeline on the GPU)
		window->draw(it->second.second, &it->second.first);
	}
}

void Renderer::clear()
{
	// Clearing the vertex array for the next frame drawing
	for (auto it = m_data.begin(); it != m_data.end(); it++)
		it->second.second.clear();
}

sf::VertexArray* Renderer::getVertexArrayPointer(const std::string textureName)
{
	// We query through the map and return the vertex array that corresponds to the texture
	auto iteratorToTheEntry = m_data.find(textureName);

	return &iteratorToTheEntry->second.second;
}

sf::Texture* Renderer::getTexture(const std::string textureName)
{
	// We query through the map and return the vertex array that corresponds to the texture
	auto iteratorToTheEntry = m_data.find(textureName);

	return &iteratorToTheEntry->second.first;
}
