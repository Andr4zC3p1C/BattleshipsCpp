#ifndef INPUT_H
#define INPUT_H

#include <SFML\Window\Event.hpp>

class Input
{
public:
    void update(sf::Event& event);

    bool isButtonClicked();
    bool isButtonDown();
private:
    bool m_buttonDown = false;
    bool m_buttonClicked = false;
    bool m_buttonPressedInPast = false;
};

#endif