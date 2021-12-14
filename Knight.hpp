#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.hpp"

class Knight : public ChessPiece {
    public:
        using ChessPiece::ChessPiece;

        bool isValidMove(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) override;
        bool opponentIsChecked(ChessPiece* board[NUM_TILE][NUM_TILE]) override;
        std::string getType() const override { return "Knight"; }
};

#endif