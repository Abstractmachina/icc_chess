#include "ChessPiece.hpp"
#include "errors.hpp"

using namespace std;

/*
ChessPiece* ChessPiece::getKing(ChessPiece* board[NUM_TILE][NUM_TILE]) {
    for (int i = 0; i < NUM_TILE; i++) {
        for (int j = 0; j < NUM_TILE; j++) {
            auto sel = board[i][j];
            if (   sel != nullptr && 
                    sel->getType() == "King" && 
                    sel->getColor() == m_color) 
                    { return sel; }
        }
    }
    return nullptr;
}
*/
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