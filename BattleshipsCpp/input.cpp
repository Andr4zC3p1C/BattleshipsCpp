#include "input.h"

void Input::update(sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
		m_buttonDown = true;
	}

    if(event.type == sf::Event::MouseButtonReleased)
    {
        // we record that the button has been released, thus it can be clicked again in the future
        m_buttonDown = false;
        m_buttonPressedInPast = false;
    }

	// We record the new mouse coordinates
	if (event.type == sf::Event::MouseMoved)
	{
		m_mousePosition.x = event.mouseMove.x;
		m_mousePosition.y = event.mouseMove.y;
	}
}

bool Input::isButtonClicked()
{
    // This function tells us if the button has been clicked or not and NOT if it is currently being pressed. 
    // For example we do not want to shoot 100 shots at the gird in game when clicking the mouse button in a second, so we record if the button has already been pressed
    m_buttonClicked = !m_buttonPressedInPast && m_buttonDown;
    if(m_buttonClicked)
        m_buttonPressedInPast = true;

    return m_buttonClicked;
}

bool Input::isButtonDown()
{
    return m_buttonDown;
}

sf::Vector2i& Input::getMousePosition()
{
	return m_mousePosition;
}
