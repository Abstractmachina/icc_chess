/*-------------------------------------------------------
Taole Chen 211214
The ChessBoard class contains the main functionality of the program.
I.e. it is the defacto world handler, it
-processes the input
-coordinates moves
-handles win conditions.
---------------------------------------------------------*/

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
    static int const NUM_TILES = 8; //Board size.
    PlayerColor m_playerTurn = WHITE;
    //tiles of board. contains pointer to piece or nullptr if empty.
    ChessPiece* m_board[NUM_TILES][NUM_TILES];
    bool m_gameOver = false; //win condition
    /*true if in check. 
    need to be switched to false to execute next move*/
    bool m_whiteCheck = false; 
    bool m_blackCheck = false;

    
    //=======================   Main Game Functions ============================
    void peekMove(ChessPiece*& piece, int src[2], int dest[2], ChessPiece*& out);
    void undoMove(ChessPiece*& piece, int src[2], int dest[2], ChessPiece*& o_tempHolder);
    void commitMove(ChessPiece*& piece, int src[2], int dest[2], ChessPiece*& destContent);
    bool isCheckmated(PlayerColor);
    bool isStaleMated(PlayerColor);
    ChessPiece* findKing(PlayerColor);
    void togglePlayerTurn();

    //input processing
    void checkCorrectPlayer(ChessPiece const* p) const;
    void checkValidInput(std::string const& input, std::string const& extraInfo) const;

public:
    ChessBoard();
    ~ChessBoard(); 
    //===============   public Functions ==============================
    void submitMove(std::string source, std::string destination);
    void resetBoard();
    //===============   Setters/Getters ==============================
    ChessPiece* getPiece(int col, int row) const;
    //place piece on tile. col (A-H) row (1-8)
    void setTile(ChessPiece* piece, char col, char row);
    void print() const;
};

#endif