#ifndef CHESSPIECEIMPL_H
#define CHESSPIECEIMPL_H

#include <iostream>

#include "ChessPiece.hpp"
#include "errors.hpp"


//===============   BISHOP    ================
class Bishop : public ChessPiece {
public:
    using ChessPiece::ChessPiece;

    void move(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) override;
    bool isInCheck(ChessPiece* board[NUM_TILE][NUM_TILE]) override;
    std::string getType() const override { return "Bishop"; }
};


//===============   KING    ================
class King : public ChessPiece {
public:
    using ChessPiece::ChessPiece; 
    
    void move(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) override;
    bool isInCheck(ChessPiece* board[NUM_TILE][NUM_TILE]) override;
    std::string getType() const override { return "King"; }
};


//===============   KNIGHT    ================
class Knight : public ChessPiece {
public:
    using ChessPiece::ChessPiece;

    void move(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) override;
    bool isInCheck(ChessPiece* board[NUM_TILE][NUM_TILE]) override;
    std::string getType() const override { return "Knight"; }
};


//===============   PAWN    ================
class Pawn : public ChessPiece {
    private:
        bool m_firstTurn = true;

        bool diagonalCapture(int const& dCol, int const& dRow, ChessPiece* board[NUM_TILE][NUM_TILE]);
        //no error checking. assumes pawn is already moving to correct square
        bool moveTwoSquares(int const& dCol, int const& dRow, ChessPiece* board[NUM_TILE][NUM_TILE]);
        bool moveOneSquare(int const& dCol, int const& dRow, ChessPiece* board[NUM_TILE][NUM_TILE]);
    public:
        using ChessPiece::ChessPiece;

        void move(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) override;
        bool isInCheck(ChessPiece* board[NUM_TILE][NUM_TILE]) override;
        std::string getType() const override { return "Pawn"; }
};


//===============   QUEEN    ================
class Queen : public ChessPiece {
public:
    using ChessPiece::ChessPiece;

    void move(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) override;
    bool isInCheck(ChessPiece* board[NUM_TILE][NUM_TILE]) override;
    std::string getType() const override { return "Queen"; }
};


//===============   ROOK    ================
class Rook : public ChessPiece {
public:
    using ChessPiece::ChessPiece;

    void move(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) override;
    bool isInCheck(ChessPiece* board[NUM_TILE][NUM_TILE]) override;
    std::string getType() const override { return "Rook"; }
};


#endif