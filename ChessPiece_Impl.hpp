#ifndef CHESSPIECEIMPL_H
#define CHESSPIECEIMPL_H

#include "ChessPiece.hpp"


//===============   BISHOP    ================
class Bishop : public ChessPiece {
    private:
        /* data */
    public:
        Bishop(/* args */);

        void override move();
};


//===============   KING    ================
class King : public ChessPiece
{
private:
    /* data */
public:
    King(/* args */);
    ~King();
};

King::King(/* args */)
{
}

King::~King()
{
}

//===============   KNIGHT    ================
class Knight : ChessPiece
{
private:
    /* data */
public:
    Knight(/* args */);
    ~Knight();
};

Knight::Knight(/* args */)
{
}

Knight::~Knight()
{
}

//===============   PAWN    ================
class Pawn : ChessPiece
{
private:
    /* data */
public:
    Pawn(/* args */);
    ~Pawn();
};

Pawn::Pawn(/* args */)
{
}

Pawn::~Pawn()
{
}

//===============   QUEEN    ================
class Queen : ChessPiece
{
private:
    /* data */
public:
    Queen(/* args */);
    ~Queen();
};

Queen::Queen(/* args */)
{
}

Queen::~Queen()
{
}

//===============   ROOK    ================
class Rook : ChessPiece
{
private:
    /* data */
public:
    Rook(/* args */);
    ~Rook();
};

Rook::Rook(/* args */)
{
}

Rook::~Rook()
{
}

#endif