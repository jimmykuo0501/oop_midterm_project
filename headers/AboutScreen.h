//
// Created by Miller on 2025/4/9.
//

#ifndef ABOUTSCREEN_H
#define ABOUTSCREEN_H

#include "../headers/GameState.h"
#include "../headers/Button.h"
#include "../headers/MainMenu.h"
#include "../headers/Global.h"
#include <SFML/Graphics.hpp>
#include <utility>

// About Screen State
class AboutScreen : public GameState {
private:
    sf::Sprite backgroundSprite;
    sf::Text titleText;
    sf::Text aboutText;

    Button backButton;

public:
    AboutScreen(sf::RenderWindow &window, std::function<void(std::shared_ptr<GameState>)> callback)
        : GameState(window, std::move(callback)),
          backgroundSprite(resources->getTexture("menu_bg")),
          titleText(sf::Text(resources->getFont("main"))),
          aboutText(sf::Text(resources->getFont("main"))),
          backButton(
              sf::Vector2f(100.0f, 40.0f),
              sf::Vector2f(30.0f, WINDOW_HEIGHT - 70.0f),
              resources->getFont("main"),
              "Back",
              sf::Color(180, 180, 180),
              sf::Color(200, 200, 200),
              sf::Color(160, 160, 160),
              resources->getSoundBuffer("click")
          ) {
    }

    void init() override {
        // Set up background

        // Scale to fit the window
        sf::Vector2u textureSize = resources->getTexture("menu_bg").getSize();
        float scaleX = static_cast<float>(WINDOW_WIDTH) / textureSize.x;
        float scaleY = static_cast<float>(WINDOW_HEIGHT) / textureSize.y;
        backgroundSprite.setScale({scaleX, scaleY});

        // Set up title text
        titleText.setString("About");
        titleText.setCharacterSize(48);
        titleText.setFillColor(sf::Color::White);
        titleText.setOutlineThickness(2.0f);
        titleText.setOutlineColor(sf::Color::Black);

        // Center title
        sf::FloatRect titleBounds = titleText.getLocalBounds();
        titleText.setOrigin(titleBounds.getCenter());
        titleText.setPosition({WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 5.0f});

        // About text
        aboutText.setString(
            "Reversi Game\n\n"
            "Created by: Alan, Miller and Jimmy\n\n"
            "This is a classic Reversi (Othello) game implementation\n"
            "using SFML for the graphics and user interface.\n\n"
            "Controls:\n"
            "- Use the mouse to place your pieces\n"
            "- Press the Undo button to take back a move\n\n"
            "2025 All Rights Reserved"
        );
        aboutText.setCharacterSize(20);
        aboutText.setFillColor(sf::Color::White);
        aboutText.setLineSpacing(1.5f);

        // Center about text
        sf::FloatRect aboutBounds = aboutText.getLocalBounds();
        aboutText.setOrigin(aboutBounds.getCenter());
        aboutText.setPosition({WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f + 20.0f});

        // Start transition in
        startTransitionIn();
    }

    void handleInput(sf::Event event) override {
        if (event.is<sf::Event::MouseButtonReleased>() && !transitioning) {
            const auto &mouseEvent = event.getIf<sf::Event::MouseButtonReleased>();
            if (mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
                if (backButton.wasClicked()) {
                    auto mainMenu = std::make_shared<MainMenu>(window, stateChangeCallback);
                    mainMenu->init();
                    startTransitionTo(mainMenu);
                }
            }
        }
    }

    void update(float deltaTime) override {
        GameState::update(deltaTime);

        backButton.update(window);
    }

    void render() override {
        window.draw(backgroundSprite);
        window.draw(titleText);
        window.draw(aboutText);

        backButton.draw(window);

        renderTransition();
    }
};




#endif //ABOUTSCREEN_H
