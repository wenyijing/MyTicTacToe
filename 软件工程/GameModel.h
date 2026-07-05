#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <vector>
#include <string>

enum class Player { NONE, PLAYER1, PLAYER2, AI };
enum class GameState { PLAYING, PLAYER1_WIN, PLAYER2_WIN, AI_WIN, DRAW };

class GameModel {
private:
    std::vector<std::vector<Player>> board;
    Player currentPlayer;
    GameState state;
    int moveCount;

public:
    GameModel();

    // 棋盘操作
    bool makeMove(int row, int col);
    bool isValidMove(int row, int col) const;
    Player getCell(int row, int col) const;

    // 游戏状态
    GameState getState() const;
    Player getCurrentPlayer() const;
    int getMoveCount() const;

    // 胜负判断
    void checkGameState();
    bool checkWin(Player player) const;
    bool isBoardFull() const;

    // 重置游戏
    void resetGame();

    // AI相关
    bool makeAIMove();

    // 获取棋盘字符串表示（供View使用）
    std::vector<std::vector<char>> getBoardDisplay() const;
};

#endif