#include "King.hpp"

using namespace std;

bool King::isValidMove(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    if (dCol < m_col - 1 || dCol > m_col + 1 || dRow < m_row -1 || dRow > m_row+1 ||
    (dCol == m_col && dRow == m_row)) {
        return false;
    }
    //evrytime king wants to move, need to check if move is legal and not trigger check.
    //peek
    ChessPiece* destContent = board[dCol][dRow];
    board[dCol][dRow] = this;
    board[m_col][m_row] = nullptr;
    //king cannot check himself
    if (kingScan(board)) {
        //cout <<"Illegal move! " << getColorString() << "King cannot put himself in check.\n";
        //undo
        board[dCol][dRow] = destContent;
        board[m_col][m_row] = this;
        return false;
    }
    //undo
    board[dCol][dRow] = destContent;
    board[m_col][m_row] = this;
    return true;
}

bool King::opponentIsChecked(ChessPiece* board[NUM_TILE][NUM_TILE]) {
    for (int col = m_col - 1; col <= m_col + 1; col++) {
        for (int row = m_row -1; row <= m_row + 1; row++) {
            //check for out of bound condition and self
            if (
            col < 0 || 
            row < 0 || 
            col >= NUM_TILE || 
            row >= NUM_TILE ||
            (col == m_col && row == m_row)) continue;
            //check if opponent king is checked
            ChessPiece* sel = board[col][row];
            if (
            sel != nullptr && 
            sel->getType() == "King" &&
            sel->getColor() != m_color  ) return true;
        }
    }
    return false;
}

bool King::kingScan(ChessPiece* board[NUM_TILE][NUM_TILE]) {
    for (int i = 0; i < NUM_TILE; i++) {
        for (int j = 0; j < NUM_TILE; j++) {
            ChessPiece* sel = board[i][j];
            if (sel != nullptr && sel->getColor() != m_color) {
                
                if (sel->opponentIsChecked(board)) {
                    return true;
                } 
            }
        }
    }
    return false;
}