#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <string>

#include "Player.hpp"

//abstract base class.
class ChessPiece {
    private:
        bool _isAlive = true;
        char _position[2];
        Player* _owner;
        PlayerColor _color;
    public:
        ChessPiece();
        ChessPiece(PlayerColor c) : _color(c) {}
        ChessPiece(PlayerColor c, char pos[2], Player* own) 
        : _color(c), _position(pos), _owner(own) {}

        virtual void move() = 0; //pure virtual function

        PlayerColor const& getColor() const { return _color;}
        void setColor(PlayerColor c) { _color = c; }
        Player& getOwner() const;
        char[2] getPosition() const;
};
#endif