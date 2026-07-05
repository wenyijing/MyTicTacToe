#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "GameModel.h"
#include <iostream>
#include <string>

class GameView {
public:
    GameView();

    // 显示游戏界面
    void displayBoard(const GameModel& model);
    void displayMessage(const std::string& message);
    void displayGameResult(const GameModel& model);
    void displayWelcome();
    void displayGoodbye();

    // 获取用户输入
    bool getUserMove(int& row, int& col);
    bool getGameModeChoice(int& choice);

    // 清除屏幕
    void clearScreen();
};

#endif // GAMEVIEW_H