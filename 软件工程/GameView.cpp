#include "GameView.h"
#include <limits>

GameView::GameView() {}

void GameView::displayBoard(const GameModel& model) {
    auto board = model.getBoardDisplay();

    std::cout << "\n  1   2   3\n";
    std::cout << " ┌───┬───┬───┐\n";
    for (int i = 0; i < 3; i++) {
        std::cout << i + 1 << "│ ";
        for (int j = 0; j < 3; j++) {
            std::cout << board[i][j];
            if (j < 2) std::cout << " │ ";
        }
        std::cout << " │\n";
        if (i < 2) std::cout << " ├───┼───┼───┤\n";
    }
    std::cout << " └───┴───┴───┘\n";

    // 显示当前玩家
    Player current = model.getCurrentPlayer();
    if (model.getState() == GameState::PLAYING) {
        std::string playerName;
        if (current == Player::PLAYER1) playerName = "玩家1 (X)";
        else if (current == Player::PLAYER2) playerName = "玩家2 (O)";
        else if (current == Player::AI) playerName = "AI (A)";
        std::cout << "\n当前回合: " << playerName << std::endl;
    }
}

void GameView::displayMessage(const std::string& message) {
    std::cout << message << std::endl;
}

void GameView::displayGameResult(const GameModel& model) {
    std::cout << "\n========== 游戏结束 ==========\n";
    switch (model.getState()) {
    case GameState::PLAYER1_WIN:
        std::cout << "?? 玩家1 (X) 获胜！\n";
        break;
    case GameState::PLAYER2_WIN:
        std::cout << "?? 玩家2 (O) 获胜！\n";
        break;
    case GameState::AI_WIN:
        std::cout << "?? AI (A) 获胜！\n";
        break;
    case GameState::DRAW:
        std::cout << "?? 平局！\n";
        break;
    default:
        break;
    }
    std::cout << "==============================\n";
}

void GameView::displayWelcome() {
    std::cout << "====================================\n";
    std::cout << "      欢迎来到井字棋游戏！\n";
    std::cout << "====================================\n";
    std::cout << "玩家1: X, 玩家2: O, AI: A\n\n";
}

void GameView::displayGoodbye() {
    std::cout << "\n感谢游戏，再见！\n";
}

bool GameView::getUserMove(int& row, int& col) {
    std::cout << "请输入行号(1-3)和列号(1-3)，用空格分隔: ";
    std::cin >> row >> col;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    // 转换为0-based索引
    row--;
    col--;
    return true;
}

bool GameView::getGameModeChoice(int& choice) {
    std::cout << "\n请选择游戏模式：\n";
    std::cout << "1. 双人对战\n";
    std::cout << "2. 人机对战 (AI先手)\n";
    std::cout << "3. 人机对战 (玩家先手)\n";
    std::cout << "请输入选择 (1-3): ";
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    return choice >= 1 && choice <= 3;
}

void GameView::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}