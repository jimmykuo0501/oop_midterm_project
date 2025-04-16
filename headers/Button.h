//
// Created by Miller on 2025/4/9.
//

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    sf::Sound clickSound;
    bool isPressed;
    bool isHovered;

public:
    // Constructor
    Button(const sf::Vector2f &size, const sf::Vector2f &position,
           const sf::Font &font, const std::string &buttonText,
           const sf::Color &idle, const sf::Color &hover, const sf::Color &active,
           const sf::SoundBuffer &soundBuffer): text(font),
                                                clickSound(sf::Sound(soundBuffer)) {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(idle);

        text.setString(buttonText);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);

        // Center text in button
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.getCenter());
        text.setPosition({position.x + size.x / 2.0f, position.y + size.y / 2.0f});

        idleColor = idle;
        hoverColor = hover;
        activeColor = active;

        isPressed = false;
        isHovered = false;
    }

    /**
    * Check whether mouse is over the block(button)
    * @param window
    * @return isMouseOver the button
    */
    bool isMouseOver(const sf::RenderWindow &window) const;

    /**
     * update the state of mouseHover and press
     * @param window (obj)
     */
    void update(const sf::RenderWindow &window);

    /**
     * Draw the button and text
     * @param window (object)
     */
    void draw(sf::RenderWindow &window) const {
        window.draw(shape);
        window.draw(text);
    }

    bool isClicked(const sf::RenderWindow &window) const;

    bool wasClicked() const {
        return isHovered && isPressed;
    }

    /**
     * Set button's position
     * @param position (vector)
     */
    void setPosition(const sf::Vector2f &position);

    /**
     * Setting text
     * @param newText
     */
    void setText(const std::string &newText);
};

#endif //BUTTON_H
