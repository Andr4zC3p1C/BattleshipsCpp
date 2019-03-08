#include "input.h"

void Input::update(sf::Event& event)
{
    m_buttonDown = (event.type == sf::Event::MouseButtonPressed);

    if(event.type == sf::Event::MouseButtonReleased)
    {
        // we record that the button has been released, thus it can be clicked again in the future
        m_buttonDown = false;
        m_buttonPressedInPast = false;
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