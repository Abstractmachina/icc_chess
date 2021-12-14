#ifndef KING_H
#define KING_H

#include "ChessPiece.hpp"

class King : public ChessPiece {
    private:
    public:
        using ChessPiece::ChessPiece; 
        
        bool isValidMove(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) override;
        bool opponentIsChecked(ChessPiece* board[NUM_TILE][NUM_TILE]) override;
        /*queries entire board to see if any pieces are putting king in check.*/
        bool kingScan(ChessPiece* board[NUM_TILE][NUM_TILE]) override;
        std::string getType() const override { return "King"; }
};

#endif