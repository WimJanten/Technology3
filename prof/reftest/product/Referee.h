#ifndef REFEREE_H
#define REFEREE_H

#include <string>

#define BOARD_SIZE 64

class Referee
{
private:
    static bool CheckValidPiece(std::string move);
    static bool CheckLegalMoveForPiece(std::string move);
    static bool CheckDesiredSpace(std::string move);
    static bool CheckPath(std::string move);
    void CreateBoard();
    int board[BOARD_SIZE];

public:
    Referee();
    ~Referee();
    bool CheckMove(std::string move);
    int MakeMove(std::string move);
    int* GetBoard();
};

#endif
