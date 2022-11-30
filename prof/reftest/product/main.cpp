#include "Referee.h"
#include <iostream>

void displayBoard(int* board, int size) {
    for (int i = 0; i < 64; i++) {
        std::cout << board[i] << " ";
        if (i % 8 == 7) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}


int main()
{
    Referee referee;
    //get input from user
    int* board = referee.GetBoard();
    displayBoard(board, BOARD_SIZE);
    char input[256] = "e1e2";
    std::string move = input;

    while (move != "exit")
    {
        std::cin >> input;
        move = input;
        // if (referee.CheckMove(move))
        // {
        //     std::cout << "Valid move" << std::endl;
        // }
        // else
        // {
        //     std::cout << "Invalid move" << std::endl;
        // }
        referee.MakeMove(move);
        displayBoard(board, BOARD_SIZE);
    }
    
    return 0;
}