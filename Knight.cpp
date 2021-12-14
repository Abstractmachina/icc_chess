#include "Knight.hpp"

using namespace std;

bool Knight::isValidMove(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    if (dCol == m_col - 2 || dCol == m_col + 2 ) {
        if (dRow == m_row -1 || dRow == m_row + 1) {
            return true;
        }
    }
    if (dCol == m_col - 1 || dCol == m_col + 1 ) {
        if (dRow == m_row - 2 || dRow == m_row + 2) {
            return true;
        }
    }
    char msg[64];
    snprintf(msg, sizeof(msg),
    "%s's Knight cammot move to %c%c\n!", getColorString().c_str(), colChar(dCol), rowChar(dRow));
    //throw Err_InvalidMove(msg);
    return false;
}

bool Knight::opponentIsChecked(ChessPiece* board[NUM_TILE][NUM_TILE]) {
    if (isTileEnemyKing(m_col-2, m_row-1, board)) return true;
    if (isTileEnemyKing(m_col-2, m_row+1, board)) return true;
    if (isTileEnemyKing(m_col+2, m_row-1, board)) return true;
    if (isTileEnemyKing(m_col+2, m_row+1, board)) return true;
    if (isTileEnemyKing(m_col-1, m_row-2, board)) return true;
    if (isTileEnemyKing(m_col-1, m_row+2, board)) return true;
    if (isTileEnemyKing(m_col+1, m_row-2, board)) return true;
    if (isTileEnemyKing(m_col+1, m_row+2, board)) return true;
    return false;
}