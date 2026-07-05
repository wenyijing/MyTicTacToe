#include "GameModel.h"
#include <algorithm>

GameModel::GameModel() {
    resetGame();
}

void GameModel::resetGame() {
    board = std::vector<std::vector<Player>>(3, std::vector<Player>(3, Player::NONE));
    currentPlayer = Player::PLAYER1;
    state = GameState::PLAYING;
    moveCount = 0;
}

bool GameModel::makeMove(int row, int col) {
    if (!isValidMove(row, col) || state != GameState::PLAYING) {
        return false;
    }

    board[row][col] = currentPlayer;
    moveCount++;
    checkGameState();

    // 如果游戏仍在进行，切换玩家
    if (state == GameState::PLAYING) {
        currentPlayer = (currentPlayer == Player::PLAYER1) ? Player::PLAYER2 : Player::PLAYER1;
    }

    return true;
}

bool GameModel::isValidMove(int row, int col) const {
    return row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == Player::NONE;
}

Player GameModel::getCell(int row, int col) const {
    if (row >= 0 && row < 3 && col >= 0 && col < 3) {
        return board[row][col];
    }
    return Player::NONE;
}

void GameModel::checkGameState() {
    // 检查所有玩家是否获胜
    if (checkWin(Player::PLAYER1)) {
        state = GameState::PLAYER1_WIN;
        return;
    }
    if (checkWin(Player::PLAYER2)) {
        state = GameState::PLAYER2_WIN;
        return;
    }
    if (checkWin(Player::AI)) {
        state = GameState::AI_WIN;
        return;
    }

    // 检查平局
    if (isBoardFull()) {
        state = GameState::DRAW;
    }
}

bool GameModel::checkWin(Player player) const {
    // 检查行
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return true;
        }
    }

    // 检查列
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return true;
        }
    }

    // 检查对角线
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return true;
    }

    return false;
}

bool GameModel::isBoardFull() const {
    return moveCount >= 9;
}

GameState GameModel::getState() const {
    return state;
}

Player GameModel::getCurrentPlayer() const {
    return currentPlayer;
}

int GameModel::getMoveCount() const {
    return moveCount;
}

bool GameModel::makeAIMove() {
    if (state != GameState::PLAYING || currentPlayer != Player::AI) {
        return false;
    }

    // 简单AI：选择第一个可用的空格
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == Player::NONE) {
                return makeMove(i, j);
            }
        }
    }
    return false;
}

std::vector<std::vector<char>> GameModel::getBoardDisplay() const {
    std::vector<std::vector<char>> display(3, std::vector<char>(3));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            switch (board[i][j]) {
            case Player::PLAYER1: display[i][j] = 'X'; break;
            case Player::PLAYER2: display[i][j] = 'O'; break;
            case Player::AI: display[i][j] = 'A'; break;
            default: display[i][j] = ' ';
            }
        }
    }
    return display;
}