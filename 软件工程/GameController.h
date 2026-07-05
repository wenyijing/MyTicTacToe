#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "GameModel.h"
#include "GameView.h"

class GameController {
private:
    GameModel model;
    GameView view;
    int gameMode; // 1: 双人, 2: AI先手, 3: 玩家先手

    void handlePlayerMove();
    void handleAIMove();
    bool isGameOver() const;
    void runGameLoop();

public:
    GameController();
    void startGame();
    void resetGame();
};

#endif // GAMECONTROLLER_H