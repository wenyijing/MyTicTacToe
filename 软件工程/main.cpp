#include "GameController.h"
#include <iostream>

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   欢迎来到井字棋游戏！" << std::endl;
    std::cout << "   作者：wenyijing" << std::endl;
    std::cout << "   MVC架构实现" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    GameController controller;
    controller.startGame();
    return 0;
}