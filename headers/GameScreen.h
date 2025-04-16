//
// Created by Miller on 2025/4/9.
//

#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SFML/Graphics.hpp>
#include <utility>
#include <memory>
#include <functional>

#include "../headers/Button.h"
#include "../headers/GameState.h"
#include "../headers/FundamentalFunction.h"
#include "../headers/Global.h"
#include "../headers/Timer.h"
#include "../headers/SaveGame.h"

// 前向宣告
class MainMenu;
class VictoryScreen;
class GameScreen;

// Game Screen State
class GameScreen final : public GameState {
private:

    float aiThinkingTime = 0.0f;
    bool aiThinking = false;

    sf::Sprite backgroundSprite;
    sf::Text titleText;
    sf::Text player1Text;
    sf::Text player2Text;
    sf::Text scoreText;
    sf::Text currentPlayerText;

    // Timer display elements
    Timer player1Timer;
    Timer player2Timer;
    sf::Text timerLabel1;
    sf::Text timerLabel2;

    // Game board representation
    sf::RectangleShape boardBackground;
    sf::RectangleShape cellHighlight;
    std::vector<sf::CircleShape> pieces;

    // Buttons
    Button undoButton;
    Button menuButton;
    Button saveButton;

    // Game state
    std::string player1Name;
    std::string player2Name;
    bool vsComputer;
    bool gameOver;

    // Save game manager
    SaveGame saveGameManager;

    // Game logic
    FundamentalFunction gameLogic;
    int player1Score;
    int player2Score;
    bool isWhiteTurn;
    int selectedX;
    int selectedY;

    // Move history for undo
    struct Move {
        int x;
        int y;
        bool wasWhiteTurn;
    };

    std::vector<Move> moveHistory;

    // Constants for board rendering
    const float cellSize = 50.0f;
    const float boardX = (WINDOW_WIDTH - 8 * cellSize) / 2.0f;
    const float boardY = (WINDOW_HEIGHT - 8 * cellSize) / 2.0f + 20.0f;

    sf::Sound placeSound;

public:
    GameScreen(sf::RenderWindow &window, std::function<void(std::shared_ptr<GameState>)> callback,
               std::string p1Name, std::string p2Name, bool vsAI)
        : GameState(window, std::move(callback)),
          backgroundSprite(resources->getTexture("game_bg")),
          titleText(sf::Text(resources->getFont("main"))),
          player1Text(sf::Text(resources->getFont("main"))),
          player2Text(sf::Text(resources->getFont("main"))),
          scoreText(sf::Text(resources->getFont("main"))),
          currentPlayerText(sf::Text(resources->getFont("main"))),
          player1Timer(resources->getFont("main")),
          player2Timer(resources->getFont("main")),
          timerLabel1(sf::Text(resources->getFont("main"))),
          timerLabel2(sf::Text(resources->getFont("main"))),
          player1Name(std::move(p1Name)),
          player2Name(std::move(p2Name)),
          vsComputer(vsAI),
          gameOver(false),
          player1Score(2),
          player2Score(2),
          isWhiteTurn(false),
          selectedX(-1),
          selectedY(-1),
          undoButton(
              sf::Vector2f(100.0f, 40.0f),
              sf::Vector2f(WINDOW_WIDTH - 130.0f, WINDOW_HEIGHT - 70.0f),
              resources->getFont("main"),
              "Undo",
              sf::Color(180, 120, 60),
              sf::Color(200, 140, 80),
              sf::Color(160, 100, 40),
              resources->getSoundBuffer("click")
          ),
          menuButton(
              sf::Vector2f(100.0f, 40.0f),
              sf::Vector2f(30.0f, WINDOW_HEIGHT - 70.0f),
              resources->getFont("main"),
              "Menu",
              sf::Color(180, 180, 180),
              sf::Color(200, 200, 200),
              sf::Color(160, 160, 160),
              resources->getSoundBuffer("click")
          ),
          saveButton(
              sf::Vector2f(100.0f, 40.0f),
              sf::Vector2f(WINDOW_WIDTH / 2.0f - 50.0f, WINDOW_HEIGHT - 70.0f),
              resources->getFont("main"),
              "Save Game",
              sf::Color(60, 180, 120),
              sf::Color(80, 200, 140),
              sf::Color(40, 160, 100),
              resources->getSoundBuffer("click")
          ),
          placeSound(resources->getSoundBuffer("place")) {
    }

    void init() override;

    void setLoadedGameData(const FundamentalFunction &, bool, int, int);

    void handleInput(sf::Event event) override;

    void checkGameOver();

    void endGame();

    void update(float deltaTime) override;

    void render() override;

    void updateScores();

    void updateBoardPieces();

    bool makeMove(int, int);

    void checkTimers();

    void undoMove();

    void saveCurrentGame();

    void makeAIMove();
};

#endif //GAMESCREEN_H
