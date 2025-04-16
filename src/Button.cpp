/*****************************************************************/ /**
* \file   Button.cpp
 * \brief  Deal with the the button that input address of playing chess in the game screen.
 *
 * \author Miller
 * \date   2025/4/9
 *********************************************************************/

#include "../headers/Button.h"

/**
 * Check whether the mouse is over the button.
 * @param window
 * @return Whether the button is over.
 */
bool Button::isMouseOver(const sf::RenderWindow &window) const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
    return shape.getGlobalBounds().contains(mousePosF);
}

void Button::update(const sf::RenderWindow &window) {
    isHovered = isMouseOver(window);

    // If is hover the button, change color. And detect the mouse is press or not
    if (isHovered) {
        shape.setFillColor(hoverColor);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if (!isPressed) {
                clickSound.play();
                isPressed = true;
            }
            shape.setFillColor(activeColor);
        } else {
            isPressed = false;
        }
    } else {
        shape.setFillColor(idleColor);
        isPressed = false;
    }
}

void Button::setText(const std::string &newText) {
    text.setString(newText);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.getCenter());
    text.setPosition({
        shape.getPosition().x + shape.getSize().x / 2.0f,
        shape.getPosition().y + shape.getSize().y / 2.0f
    });
}

void Button::setPosition(const sf::Vector2f &position) {
    shape.setPosition(position);
    text.setPosition({
        position.x + shape.getSize().x / 2.0f,
        position.y + shape.getSize().y / 2.0f
    });
}

bool Button::isClicked(const sf::RenderWindow &window) const {
    return isHovered && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

