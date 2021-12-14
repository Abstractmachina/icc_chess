#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <cstdio>
#include <iostream>
#include <string>

#include "ChessPiece.hpp"
#include "Bishop.hpp"
#include "King.hpp"
#include "Knight.hpp"
#include "Pawn.hpp"
#include "Queen.hpp"
#include "Rook.hpp"

class ChessBoard {
private:
    static int const NUM_TILES = 8;
    PlayerColor m_playerTurn = WHITE;
    //tiles of board. contains pointer to piece or nullptr if empty.
    ChessPiece* m_board[NUM_TILES][NUM_TILES];
    //ChessPiece* whiteSet[16];
    //ChessPiece* blackSet[16];
    /*true if in check. 
    need to be switched tp false to execute next move*/
    bool m_gameOver = false;
    bool m_whiteCheck = false; 
    bool m_blackCheck = false;

    bool isCheckmated(PlayerColor);
    ChessPiece* findKing(PlayerColor);
    void peekMove(ChessPiece* piece, int src[2], int dest[2], ChessPiece*& out);
    void undoMove(ChessPiece* piece, int src[2], int dest[2], ChessPiece*& o_tempHolder);
    void commitMove(ChessPiece* piece, int src[2], int dest[2], ChessPiece*& destContent);
    
public:
    ChessBoard();
    ~ChessBoard(); 
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