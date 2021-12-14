#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.hpp"

class Pawn : public ChessPiece {
    private:
        bool m_firstTurn = true;

        bool diagonalCapture(int const& dCol, int const& dRow, ChessPiece* board[NUM_TILE][NUM_TILE]);
        //no error checking. assumes pawn is already moving to correct square
        bool moveTwoSquares(int const& dCol, int const& dRow, ChessPiece* board[NUM_TILE][NUM_TILE]);
        bool moveOneSquare(int const& dCol, int const& dRow, ChessPiece* board[NUM_TILE][NUM_TILE]);
    public:
        using ChessPiece::ChessPiece;

        bool isValidMove(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) override;
        bool opponentIsChecked(ChessPiece* board[NUM_TILE][NUM_TILE]) override;
        std::string getType() const override { return "Pawn"; }
};

#endif