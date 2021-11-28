/**
 * @file Player.hpp
 * 
 * @author Taole Chen
 * @brief 
 * @version 0.1
 * @date 2021-11-28
 * 
 * 
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "ChessPiece.hpp"
#include "ChessPiece_Impl.hpp"

enum PlayerColor{WHITE, BLACK};

class Player {
    private:
    struct PieceNode
    {
        ChessPiece val;
        PieceNode* next;
        PieceNode* prev;
        PieceNode(ChessPiece cp) : val(cp){}
    };
        
        const PlayerColor COLOR;
        const int NUM_BISHOP = 2;
        const int NUM_KING = 1;
        const int NUM_KNIGHT = 2;
        const int NUM_PAWN = 8;
        const int NUM_QUEEN = 1;
        const int NUM_ROOK = 2;
        PieceNode* _head = nullptr; //linkedList 
    public:
    Player(PlayerColor c);

    void initSet();

    void pushBack(ChessPiece piece);
    void insert(int i, ChessPiece piece);
    size_t size();
    void erase(int i);

};

#endif