#include "Player.hpp"

Player::Player(PlayerColor c) : COLOR(c) 
{

}

void Player::initSet()
{
    for (int i = 0; i < NUM_BISHOP; i++)
    {
        char p[2];
        if (i == 0) {
            p[0] = 
        }
        auto bishop = new Bishop(COLOR, );
        pushBack(bishop);
    }
}



void Player::pushBack(ChessPiece piece)
{
    auto curr = _head;
    for (auto it = curr; curr->next != nullptr; curr = curr->next){}

    auto node = new PieceNode(piece);
    node->prev = curr;
    curr->next = node;

}