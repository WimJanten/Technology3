
#include "Referee.h"
#include <iostream>
//Pawn: P (+ 10 for white)
//Rook: 2 (+ 10 for white)
//Knight: 3 (+ 10 for white)
//Bishop: 4 (+ 10 for white)
//Queen: 5 (+ 10 for white)
//King: 6 (+ 10 for white)

enum xPos { a, b, c, d, e, f, g, h };

Referee::Referee()
{
    CreateBoard();
}

Referee::~Referee()
{
}

void Referee::CreateBoard(){
    for (int i = 0; i < 64; i++) {
        board[i] = 0;
    }
    for (int i = 8; i < 16; i++)
    {
        board[i] = 1;
    }
    for (int i = 48; i < 56; i++)
    {
        board[i] = 11;
    }
    board[0] = 2;
    board[7] = 2;
    board[56] = 12;
    board[63] = 12;
    board[1] = 3;
    board[6] = 3;
    board[57] = 13;
    board[62] = 13;
    board[2] = 4;
    board[5] = 4;
    board[58] = 14;
    board[61] = 14;
    board[3] = 5;
    board[59] = 15;
    board[4] = 6;
    board[60] = 16;
}
/*

    Valid King move, if the piece moves from (X1, Y1) to (X2, Y2), the move is valid if and only if |X2-X1|<=1 and |Y2-Y1|<=1.

    Valid Bishop move, if the piece moves from (X1, Y1) to (X2, Y2), the move is valid if and only if |X2-X1|=|Y2-Y1|.

    Valid Rook move, if the piece moves from (X1, Y1) to (X2, Y2), the move is valid if and only if X2=X1 or Y2=Y1.

    Valid Queen move, a queen's move is valid if it is either a valid bishop or rook move.

    Valid Knight move, if the piece moves from (X1, Y1) to (X2, Y2), the move is valid if and only if (|X2-X1|=1 and |Y2-Y1|=2) or (|X2-X1|=2 and |Y2-Y1|=1).

    Valid Pawn move, if the piece moves from (X1, Y1) to (X2, Y2), the move is valid if and only if X2=X1 and Y2-Y1=1 (only for a white pawn).
*/

bool Referee::CheckMove(std::string move)
{
    if(!CheckValidPiece(move)){
        return false;
    }
    else if (!CheckLegalMoveForPiece(move))
    {
        return false;
    }
    else if (!CheckDesiredSpace(move))
    {
        return false;
    }
    else if (!CheckPath(move))
    {
        return false;
    }
    return true;
}

bool Referee::CheckValidPiece(std::string move)
{
    //check if the piece is a valid piece
    if (move[0] != 'K' && move[0] != 'B' && move[0] != 'R' && move[0] != 'Q' && move[0] != 'N' && move[0] != 'P')
    {
        return false;
    }
    return true;
}

bool Referee::CheckLegalMoveForPiece(std::string move){
    return true;
}

bool Referee::CheckDesiredSpace(std::string move){
    return true;
}

bool Referee::CheckPath(std::string move){
    return true;
}

int Referee::MakeMove(std::string move)
{
    int x1 = move[0] - 'a';
    int y1 = move[1] - '0';
    int x2 = move[2] - 'a';
    int y2 = move[3] - '0';
    std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;
    int piece = board[x1 + (y1 * 8)];
    
    board[(x1 - 1) + (y1 * 8)] = 0;
    board[(x2 - 1) + (y2 * 8)] = piece;
    return 0;
}

int* Referee::GetBoard()
{
    return board;
}