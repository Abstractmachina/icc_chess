#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <cstdio>
#include <iostream>
#include <string>

#include "ChessPiece.hpp"
#include "ChessPiece_Impl.hpp"

class ChessBoard {
private:
    static int const MAX_TILE_NUM = 8;
    PlayerColor m_playerTurn = WHITE;
    //tiles of board. contains pointer to piece or nullptr if empty.
    ChessPiece* m_board[MAX_TILE_NUM][MAX_TILE_NUM];
    bool whiteCheck = false;
    bool blackCheck = false;
public:
    ChessBoard();
    ~ChessBoard(); //TODO: destruct tiles. 
    void submitMove(std::string source, std::string destination);
    void resetBoard();
    void checkCorrectPlayer(ChessPiece const* p) const;
    /*extraInfo: will be prepended to error message. 
    example usage: add parent function for extra info.*/
    void checkValidInput(std::string const& input, std::string const& extraInfo) const;

    ChessPiece* getPiece(int col, int row) const;
    void setTile(ChessPiece* piece, char col, char row);
    void print() const;
};

#endif