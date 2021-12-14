#include "Rook.hpp"

using namespace std;

bool Rook::isValidMove(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    int difC = dCol - m_col;
    int difR = dRow - m_row;
    //1 if going up, -1 if going down
    int stepC = difC / abs(difC);
    int stepR = difR / abs(difR);

    //vertical move
    if (dCol == m_col) {
        if (abs(difR) == 1) { 
            //updatePosition(dCol, dRow, board);
            return true;
        }
        for (int r = 1; r < abs(difR); r++) {
            if (board[m_col][m_row + (stepR * r)] != nullptr) {
                char msg[48];
                snprintf(msg, sizeof(msg),
                "%s's %s cannot move to %c%c\n", 
                getColorString().c_str(), getType().c_str(), colChar(dCol), rowChar(dRow));
                cerr << msg << endl;
                return false;
            }
        }
        //updatePosition(dCol, dRow, board);
        return true;
    }

    //horizontal move
    if (dRow == m_row) {
        if (abs(difC) == 1) { 
            //updatePosition(dCol, dRow, board);
            return true;
        }
        for (int i = 1; i < abs(difC); i++) {
            if (board[m_col + (stepC * i)][m_row] != nullptr) {
                char msg[48];
                snprintf(msg, sizeof(msg),
                "%s's %s cannot move to %c%c\n", 
                getColorString().c_str(), getType().c_str(), colChar(dCol), rowChar(dRow));
                cerr << msg << endl;
            }
        }
        //updatePosition(dCol, dRow, board);
        return true;
    }
    return false;
}

bool Rook::opponentIsChecked(ChessPiece* board[NUM_TILE][NUM_TILE]) {
    //north
    int cInd = m_col;
    int rInd = m_row+1;
    while (rInd < NUM_TILE) {
        PieceType type = isEnemyKing(board[cInd][rInd++]);
        if (type == KING) return true;
        else if (type == NOTKING) break;
    }
    //west
    cInd = m_col+1;
    rInd = m_row;
    while (cInd < NUM_TILE) {
        PieceType type = isEnemyKing(board[cInd++][rInd]);
        if (type == KING) return true;
        else if (type == NOTKING) break;
    }
    //south
    cInd = m_col;
    rInd = m_row-1;
    while (rInd > 0) {
        PieceType type = isEnemyKing(board[cInd][rInd--]);
        if (type == KING) return true;
        else if (type == NOTKING) break;
    }
    //east
    cInd = m_col-1;
    rInd = m_row;
    while (cInd > 0) {
        PieceType type = isEnemyKing(board[cInd--][rInd]);
        if (type == KING) return true;
        else if (type == NOTKING) break;
    }
    
    return false;
}