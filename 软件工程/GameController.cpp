#include "GameController.h"
#include <iostream>
#include <thread>
#include <chrono>

GameController::GameController() : gameMode(1) {}

void GameController::startGame() {
    view.clearScreen();
    view.displayWelcome();

    int choice;
    while (!view.getGameModeChoice(choice)) {
        view.displayMessage("输入无效，请重新选择！");
    }

    gameMode = choice;
    view.clearScreen();

    // 根据模式设置初始玩家
    model.resetGame();
    if (gameMode == 2) {
        // AI先手
        model.makeMove(1, 1); // AI下在中心
        view.displayMessage("AI 已落子中心位置\n");
    }

    runGameLoop();
}

void GameController::runGameLoop() {
    while (!isGameOver()) {
        view.displayBoard(model);

        Player current = model.getCurrentPlayer();

        // 根据模式处理不同玩家的回合
        if (gameMode == 1) {
            // 双人模式
            handlePlayerMove();
        }
        else if (gameMode == 2 || gameMode == 3) {
            // 人机模式
            if (current == Player::AI) {
                handleAIMove();
            }
            else {
                handlePlayerMove();
            }
        }
    }

    // 游戏结束
    view.displayBoard(model);
    view.displayGameResult(model);

    // 询问是否重新开始
    std::cout << "\n是否重新开始？(y/n): ";
    char choice;
    std::cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        view.clearScreen();
        startGame();
    }
    else {
        view.displayGoodbye();
    }
}

void GameController::handlePlayerMove() {
    int row, col;
    view.displayMessage("请输入您的落子位置：");

    while (true) {
        if (view.getUserMove(row, col)) {
            if (model.makeMove(row, col)) {
                break;
            }
            else {
                view.displayMessage("无效位置，请重新输入！");
            }
        }
        else {
            view.displayMessage("输入无效，请重新输入！");
        }
    }
}

void GameController::handleAIMove() {
    view.displayMessage("AI 思考中...");
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // 模拟思考

    if (!model.makeAIMove()) {
        view.displayMessage("AI 无法落子！");
    }
}

bool GameController::isGameOver() const {
    GameState state = model.getState();
    return state != GameState::PLAYING;
}

void GameController::resetGame() {
    model.resetGame();
}