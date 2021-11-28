#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <cstdio>
#include <iostream>
#include <string>

#include "ChessPiece.hpp"
#include "ChessPiece_Impl.hpp"
#include "Player.hpp"

class ChessBoard {
private:
    PlayerColor _playerTurn = WHITE;
public:
    ChessBoard();
    int submitMove(string source, string destination);
    void resetBoard();

    int checkValidInput(string const& input);

    ChessPiece& getPiece(char position[2]) const;

};

#endif