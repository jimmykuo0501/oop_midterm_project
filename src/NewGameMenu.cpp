//
// Created by Miller on 2025/4/9.
//

#include "../headers/NewGameMenu.h"
#include "../headers/GameScreen.h"
#include "../headers/MainMenu.h"

void NewGameMenu::init() {
    // Set up background

    // Scale to fit the window
    sf::Vector2u textureSize = resources->getTexture("menu_bg").getSize();
    float scaleX = static_cast<float>(WINDOW_WIDTH) / textureSize.x;
    float scaleY = static_cast<float>(WINDOW_HEIGHT) / textureSize.y;
    backgroundSprite.setScale({scaleX, scaleY});

    // Set up title text
    titleText.setFont(resources->getFont("main"));
    titleText.setString("New Game");
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::White);
    titleText.setOutlineThickness(2.0f);
    titleText.setOutlineColor(sf::Color::Black);

    // Center title
    sf::FloatRect titleBounds = titleText.getLocalBounds();
    titleText.setOrigin(titleBounds.getCenter());
    titleText.setPosition({WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 5.0f});

    // Create buttons
    sf::Vector2f buttonSize(250.0f, 50.0f);

    // Player vs Player button
    buttons.push_back(Button(
        buttonSize,
        sf::Vector2f(WINDOW_WIDTH / 2.0f - buttonSize.x / 2.0f, WINDOW_HEIGHT / 3.0f),
        resources->getFont("main"),
        "Player vs Player",
        sf::Color(40, 120, 200),
        sf::Color(60, 140, 220),
        sf::Color(30, 100, 180),
        resources->getSoundBuffer("click")
    ));

    // Player vs Computer button
    buttons.push_back(Button(
        buttonSize,
        sf::Vector2f(WINDOW_WIDTH / 2.0f - buttonSize.x / 2.0f, WINDOW_HEIGHT / 3.0f + 60.0f),
        resources->getFont("main"),
        "Player vs Computer",
        sf::Color(40, 120, 200),
        sf::Color(60, 140, 220),
        sf::Color(30, 100, 180),
        resources->getSoundBuffer("click")
    ));

    // Text inputs for player names
    sf::Vector2f inputSize(250.0f, 40.0f);

    // Player 1 name input
    inputs.push_back(TextInput(
        inputSize,
        sf::Vector2f(WINDOW_WIDTH / 2.0f - inputSize.x / 2.0f, WINDOW_HEIGHT / 2.0f + 40.0f),
        resources->getFont("main"),
        "Player 1 Name"
    ));

    // Player 2 name input
    inputs.push_back(TextInput(
        inputSize,
        sf::Vector2f(WINDOW_WIDTH / 2.0f - inputSize.x / 2.0f, WINDOW_HEIGHT / 2.0f + 90.0f),
        resources->getFont("main"),
        "Player 2 Name"
    ));

    // Start Game button
    buttons.push_back(Button(
        sf::Vector2f(150.0f, 50.0f),
        sf::Vector2f(WINDOW_WIDTH / 2.0f - 75.0f, WINDOW_HEIGHT / 2.0f + 150.0f),
        resources->getFont("main"),
        "Start Game",
        sf::Color(40, 180, 80),
        sf::Color(60, 200, 100),
        sf::Color(30, 160, 60),
        resources->getSoundBuffer("click")
    ));

    // Back button
    buttons.push_back(Button(
        sf::Vector2f(100.0f, 40.0f),
        sf::Vector2f(30.0f, WINDOW_HEIGHT - 70.0f),
        resources->getFont("main"),
        "Back",
        sf::Color(180, 180, 180),
        sf::Color(200, 200, 200),
        sf::Color(160, 160, 160),
        resources->getSoundBuffer("click")
    ));

    // Start transition in
    startTransitionIn();
}

void NewGameMenu::handleInput(sf::Event event) {
    if (!transitioning) {
        // Handle text input
        for (auto &input: inputs) {
            input.handleInput(event);
        }

        if (event.is<sf::Event::MouseButtonReleased>() && !transitioning) {
            if (const auto &mouseEvent = event.getIf<sf::Event::MouseButtonReleased>(); mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
                // Check button clicks
                if (buttons[0].wasClicked()) {
                    // Player vs Player button
                    vsComputer = false;
                } else if (buttons[1].wasClicked()) {
                    // Player vs Computer button
                    vsComputer = true;
                    inputs[1].setValue("Computer");
                } else if (buttons[2].wasClicked()) {
                    // Start Game button
                    // Get player names
                    std::string player1Name = inputs[0].getValue();
                    std::string player2Name = inputs[1].getValue();

                    // Use default names if empty
                    if (player1Name.empty()) player1Name = "Player 1";
                    if (player2Name.empty() && !vsComputer) player2Name = "Player 2";

                    // Create game screen
                    const auto gameScreen = std::make_shared<GameScreen>(
                        window, stateChangeCallback, player1Name, player2Name, vsComputer);
                    gameScreen->init();
                    startTransitionTo(gameScreen);
                } else if (buttons[3].wasClicked()) {
                    // Back button
                    auto mainMenu = std::make_shared<MainMenu>(window, stateChangeCallback);
                    mainMenu->init();
                    startTransitionTo(mainMenu);
                }
            }
        }
    }
}

void NewGameMenu::update(float deltaTime) {
    GameState::update(deltaTime);

    // Update buttons
    for (auto &button: buttons) {
        button.update(window);
    }

    // Update text inputs
    for (auto &input: inputs) {
        input.update(window, deltaTime);
    }
}

void NewGameMenu::render() {
    window.draw(backgroundSprite);
    window.draw(titleText);

    for (const auto &button: buttons) {
        button.draw(window);
    }

    for (const auto &input: inputs) {
        input.draw(window);
    }

    renderTransition();
}