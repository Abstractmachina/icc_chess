#include "ChessPiece.hpp"
#include "errors.hpp"

using namespace std;

bool ChessPiece::isTileEnemyKing(int col, int row, ChessPiece* board[NUM_TILE][NUM_TILE]) const {
    if (col < 0 || col >= NUM_TILE || row < 0 || row >= NUM_TILE) 
        return false;
    ChessPiece* piece = board[col][row];
    if (piece != nullptr && piece->getType() == "King" && 
        piece->getColor() != m_color) return true;
    return false;
}

PieceType ChessPiece::isEnemyKing(ChessPiece const* piece) const {
    if (piece == nullptr) return EMPTY; 
    if (piece->getType() == "King" && piece->getColor() != m_color) return KING;
    return NOTKING;
}

std::string ChessPiece::getColorString() const {
    if (m_color == WHITE) return "White";
    else return "Black";
}

void ChessPiece::setPosition(char col, char row) { 
    m_col = int(col) - 'A'; 
    m_row = int(row) - '1'; 
}