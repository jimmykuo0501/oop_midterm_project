//
// Created by Miller on 2025/4/9.
//

#include "../headers/MainMenu.h"
#include "../headers/NewGameMenu.h"
#include "../headers/LoadGameMenu.h"
#include "../headers/AboutScreen.h"

void MainMenu::init() {
        // Set up background

        // Scale to fit the window
        const sf::Vector2u textureSize = resources->getTexture("menu_bg").getSize();
        float scaleX = static_cast<float>(WINDOW_WIDTH) / textureSize.x;
        float scaleY = static_cast<float>(WINDOW_HEIGHT) / textureSize.y;
        backgroundSprite.setScale({scaleX, scaleY});

        // Set up title text
        titleText.setString("REVERSI");
        titleText.setCharacterSize(72);
        titleText.setFillColor(sf::Color::White);
        titleText.setOutlineThickness(3.0f);
        titleText.setOutlineColor(sf::Color::Black);

        // Center title
        sf::FloatRect titleBounds = titleText.getLocalBounds();
        titleText.setOrigin(titleBounds.getCenter());
        titleText.setPosition({WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 5.0f});

        // Create buttons
        constexpr sf::Vector2f buttonSize(200.0f, 50.0f);
        float buttonY = WINDOW_HEIGHT / 2.0f - 75.0f;
        constexpr float spacing = 60.0f;

        // New Game button
        buttons.push_back(Button(
            buttonSize,
            sf::Vector2f(WINDOW_WIDTH / 2.0f - buttonSize.x / 2.0f, buttonY),
            resources->getFont("main"),
            "New Game",
            sf::Color(40, 120, 200),
            sf::Color(60, 140, 220),
            sf::Color(30, 100, 180),
            resources->getSoundBuffer("click")
        ));

        buttonY += spacing;

        // Load Game button
        buttons.push_back(Button(
            buttonSize,
            sf::Vector2f(WINDOW_WIDTH / 2.0f - buttonSize.x / 2.0f, buttonY),
            resources->getFont("main"),
            "Load Game",
            sf::Color(40, 120, 200),
            sf::Color(60, 140, 220),
            sf::Color(30, 100, 180),
            resources->getSoundBuffer("click")
        ));

        buttonY += spacing;

        // About button
        buttons.push_back(Button(
            buttonSize,
            sf::Vector2f(WINDOW_WIDTH / 2.0f - buttonSize.x / 2.0f, buttonY),
            resources->getFont("main"),
            "About",
            sf::Color(40, 120, 200),
            sf::Color(60, 140, 220),
            sf::Color(30, 100, 180),
            resources->getSoundBuffer("click")
        ));

        buttonY += spacing;

        // Exit button
        buttons.push_back(Button(
            buttonSize,
            sf::Vector2f(WINDOW_WIDTH / 2.0f - buttonSize.x / 2.0f, buttonY),
            resources->getFont("main"),
            "Exit",
            sf::Color(200, 60, 60),
            sf::Color(220, 80, 80),
            sf::Color(180, 40, 40),
            resources->getSoundBuffer("click")
        ));

        // Start transition in
        startTransitionIn();
    }

void MainMenu::goToNewGameScreen() {
    auto newGameMenu = std::make_shared<NewGameMenu>(window, stateChangeCallback);
    newGameMenu->init();
    startTransitionTo(newGameMenu);
}

void MainMenu::goToLoadGameScreen() {
    auto loadGameMenu = std::make_shared<LoadGameMenu>(window, stateChangeCallback);
    loadGameMenu->init();
    startTransitionTo(loadGameMenu);
}

void MainMenu::goToAboutScreen() {
    auto aboutScreen = std::make_shared<AboutScreen>(window, stateChangeCallback);
    aboutScreen->init();
    startTransitionTo(aboutScreen);
}

void MainMenu::handleInput(const sf::Event event) {
    if (event.is<sf::Event::MouseButtonReleased>() && !transitioning) {
        if (const auto &mouseEvent = event.getIf<sf::Event::MouseButtonReleased>(); mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
            // Check button clicks
            if (buttons[0].wasClicked()) {
                // New Game button
                goToNewGameScreen();
            } else if (buttons[1].wasClicked()) {
                // Load Game button
                goToLoadGameScreen();
            } else if (buttons[2].wasClicked()) {
                // About button
                goToAboutScreen();
            } else if (buttons[3].wasClicked()) {
                // Exit button
                window.close();
            }
        }
    }
}

void MainMenu::render() {
    window.draw(backgroundSprite);
    window.draw(titleText);

    for (const auto &button: buttons) {
        button.draw(window);
    }

    renderTransition();
}

void MainMenu::update(float deltaTime) {
    GameState::update(deltaTime);

    // Update buttons
    for (auto &button: buttons) {
        button.update(window);
    }
}