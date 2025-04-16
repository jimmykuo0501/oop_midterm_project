//
// Created by Miller on 2025/4/9.
//

#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <SFML/Graphics.hpp>


// TextInput class
class TextInput {
private:
    sf::RectangleShape background;
    sf::Text text;
    sf::Text placeholder;
    sf::Text cursor;
    std::string inputString;
    bool isActive;
    bool showCursor;
    float cursorBlinkTime;
    const float blinkInterval = 0.5f;

public:
    TextInput(const sf::Vector2f &size, const sf::Vector2f &position,
              const sf::Font &font, const std::string &placeholderText): text(sf::Text(font)),
                                                                         placeholder(sf::Text(font)),
                                                                         cursor(sf::Text(font)) {
        background.setSize(size);
        background.setPosition(position);
        background.setFillColor(sf::Color(240, 240, 240));
        background.setOutlineThickness(2.0f);
        background.setOutlineColor(sf::Color(200, 200, 200));

        text.setString("");
        text.setCharacterSize(18);
        text.setFillColor(sf::Color::Black);
        text.setPosition({position.x + 10.0f, position.y + size.y / 2.0f - 9.0f});

        placeholder.setString(placeholderText);
        placeholder.setCharacterSize(18);
        placeholder.setFillColor(sf::Color(150, 150, 150));
        placeholder.setPosition({position.x + 10.0f, position.y + size.y / 2.0f - 9.0f});

        cursor.setString("|");
        cursor.setCharacterSize(18);
        cursor.setFillColor(sf::Color::Black);
        cursor.setPosition({position.x + 10.0f, position.y + size.y / 2.0f - 9.0f});

        inputString = "";
        isActive = false;
        showCursor = false;
        cursorBlinkTime = 0.0f;
    }

    void update(const sf::RenderWindow &window, float deltaTime) {

        // Check if clicked
        if (isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            isActive = background.getGlobalBounds().contains(mousePosF);

            if (isActive) {
                background.setOutlineColor(sf::Color(100, 100, 255));
            }
        }

        // Update cursor blink
        if (isActive) {
            cursorBlinkTime += deltaTime;
            if (cursorBlinkTime >= blinkInterval) {
                cursorBlinkTime = 0.0f;
                showCursor = !showCursor;
            }

            // Position cursor after text
            sf::FloatRect textBounds = text.getGlobalBounds();
            cursor.setPosition({text.getPosition().x + textBounds.size.x, text.getPosition().y});
        } else {
            background.setOutlineColor(sf::Color(200, 200, 200));
            showCursor = false;
        }
    }

    void handleInput(sf::Event event) {
        if (!isActive) return;

        if (event.is<sf::Event::TextEntered>()) {
            const auto &textUnicode = event.getIf<sf::Event::TextEntered>();
            if (textUnicode->unicode == 8) {
                // Backspace
                if (!inputString.empty()) {
                    inputString.pop_back();
                }
            } else if (textUnicode->unicode == 13) {
                // Enter
                isActive = false;
            } else if (textUnicode->unicode >= 32 && textUnicode->unicode < 128) {
                inputString += static_cast<char>(textUnicode->unicode);
            }

            text.setString(inputString);
        }
    }

    void draw(sf::RenderWindow &window) const {
        window.draw(background);

        if (inputString.empty()) {
            window.draw(placeholder);
        } else {
            window.draw(text);
        }

        if (isActive && showCursor) {
            window.draw(cursor);
        }
    }

    std::string getValue() const {
        return inputString;
    }

    void setValue(const std::string &value) {
        inputString = value;
        text.setString(inputString);
    }

    bool isActiveInput() const {
        return isActive;
    }
};
#endif //TEXTINPUT_H