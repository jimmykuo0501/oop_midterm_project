//
// Created by Miller on 2025/4/9.
//

#include "../headers/LoadGameMenu.h"
#include "../headers/GameScreen.h"

void LoadGameMenu::loadSavedGames() {
    // Get save files using the SaveGame manager
    savedGames = saveGameManager.getSaveFiles();
}

void LoadGameMenu::createSaveButtons() {
    saveButtons.clear();

    sf::Vector2f saveButtonSize(300.0f, 40.0f);
    float startY = WINDOW_HEIGHT / 3.0f;
    float spacing = 50.0f;

    for (size_t i = 0; i < savedGames.size(); ++i) {
        std::string displayName = saveGameManager.getSaveDisplayName(savedGames[i]);

        saveButtons.push_back(Button(
            saveButtonSize,
            sf::Vector2f(WINDOW_WIDTH / 2.0f - saveButtonSize.x / 2.0f, startY + i * spacing),
            resources->getFont("main"),
            displayName,
            sf::Color(60, 120, 160),
            sf::Color(80, 140, 180),
            sf::Color(40, 100, 140),
            resources->getSoundBuffer("click")
        ));
    }
}

void LoadGameMenu::handleInput(sf::Event event) {
    if (event.is<sf::Event::MouseButtonReleased>() && !transitioning) {
        if (const auto &mouseEvent = event.getIf<sf::Event::MouseButtonReleased>(); mouseEvent && mouseEvent->button == sf::Mouse::Button::Left) {
            // Check back button
            if (buttons[0].wasClicked()) {
                auto mainMenu = std::make_shared<MainMenu>(window, stateChangeCallback);
                mainMenu->init();
                startTransitionTo(mainMenu);
                return;
            }

            // Check save buttons for selection
            for (size_t i = 0; i < saveButtons.size(); ++i) {
                if (saveButtons[i].wasClicked()) {
                    // Handle save selection
                    selectedSaveIndex = i;

                    // Update button appearance
                    for (size_t j = 0; j < saveButtons.size(); ++j) {
                        if (j == selectedSaveIndex) {
                            // Highlight selected save
                            saveButtons[j].setText("> " + saveGameManager.getSaveDisplayName(savedGames[j]));
                        } else {
                            // Reset other buttons
                            saveButtons[j].setText(saveGameManager.getSaveDisplayName(savedGames[j]));
                        }
                    }
                    return;
                }
            }

            // Check action buttons
            if (selectedSaveIndex >= 0 && selectedSaveIndex < savedGames.size()) {
                // Open button
                if (actionButtons[0].wasClicked()) {
                    loadGame(savedGames[selectedSaveIndex]);
                    return;
                }

                // Delete button
                if (actionButtons[1].wasClicked()) {
                    deleteGame(savedGames[selectedSaveIndex]);
                    return;
                }
            }
        }
    }
}

void LoadGameMenu::loadGame(const std::string& savePath) {
    // Create a new game screen with loaded game data
    FundamentalFunction gameLogic;
    std::string player1Name, player2Name;
    bool isWhiteTurn, vsComputer;
    int player1Chances = 0, player2Chances = 0;

    // Load the game data
    if (saveGameManager.loadGame(savePath, gameLogic, player1Name, player2Name, isWhiteTurn, vsComputer, player1Chances, player2Chances)) {
        auto gameScreen = std::make_shared<GameScreen>(
            window, stateChangeCallback, player1Name, player2Name, vsComputer);

        // Initialize the base components
        gameScreen->init();

        // We need to pass the loaded game data to the GameScreen
        gameScreen->setLoadedGameData(gameLogic, isWhiteTurn, player1Chances, player2Chances);

        startTransitionTo(gameScreen);
    }
}

void LoadGameMenu::deleteGame(const std::string& savePath) {
    if (saveGameManager.deleteSave(savePath)) {
        // Refresh saved games list
        loadSavedGames();
        createSaveButtons();
        selectedSaveIndex = -1;
    }
}

void LoadGameMenu::update(float deltaTime) {
    GameState::update(deltaTime);

    // Update buttons
    for (auto &button: buttons) {
        button.update(window);
    }

    for (auto &button: saveButtons) {
        button.update(window);
    }

    for (auto &button: actionButtons) {
        button.update(window);
    }
}

void LoadGameMenu::render() {
    window.draw(backgroundSprite);
    window.draw(titleText);

    if (saveButtons.empty()) {
        window.draw(infoText);
    }

    // Draw save buttons
    for (const auto &button: saveButtons) {
        button.draw(window);
    }

    // Draw control buttons
    for (const auto &button: buttons) {
        button.draw(window);
    }

    // Draw action buttons only if a save is selected
    if (selectedSaveIndex >= 0) {
        for (const auto &button: actionButtons) {
            button.draw(window);
        }
    }

    renderTransition();
}