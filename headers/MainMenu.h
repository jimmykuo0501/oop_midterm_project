//
// Created by Miller on 2025/4/9.
//

#ifndef MAINMENU_H
#define MAINMENU_H

#include <utility>
#include <vector>
#include <memory>
#include <functional>

#include "../headers/GameState.h"
#include "../headers/NewGameMenu.h"
#include "../headers/Button.h"
#include "../headers/Global.h"

// 前向宣告
class NewMainMenu;
class LoadGameMenu;
class AboutMenu;


// Main Menu State
class MainMenu : public GameState {
private:
    sf::Sprite backgroundSprite;
    sf::Text titleText;

    std::vector<Button> buttons;

public:

    // Constructor
    MainMenu(sf::RenderWindow &window, std::function<void(std::shared_ptr<GameState>)> callback)
        : GameState(window, std::move(callback)),
          backgroundSprite(resources->getTexture("menu_bg")),
          titleText(sf::Text(resources->getFont("main"))) {
    }
    void init() override;

    void handleInput(sf::Event event) override;

    void update(float deltaTime) override;

    void render() override;

    void goToNewGameScreen();

    void goToLoadGameScreen();

    void goToAboutScreen();


};

#endif //MAINMENU_H
