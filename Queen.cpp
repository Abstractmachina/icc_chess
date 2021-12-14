#include "Queen.hpp"

using namespace std;

bool Queen::isValidMove(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    int difC = dCol - m_col;
    int difR = dRow - m_row;
    //1 if going up, -1 if going down
    int stepC = difC / abs(difC);
    int stepR = difR / abs(difR);

    //vertical move
    if (dCol == m_col) {
        if (abs(difR) == 1) { 

            return true;
        }
        for (int r = 1; r < abs(difR); r++) {
            if (board[m_col][m_row + (stepR * r)] != nullptr) {
                char msg[48];
                snprintf(msg, sizeof(msg),
                "%s's %s cannot move to %c%c\n", 
                getColorString().c_str(), getType().c_str(), colChar(dCol), rowChar(dRow));
                //cout << msg << endl;
                return false;
            }
        }

        return true;
    }

    //horizontal move
    else if (dRow == m_row) {
        if (abs(difC) == 1) { 
            return true;
        }
        for (int i = 1; i < abs(difC); i++) {
            //if blocked
            if (board[m_col + (stepC * i)][m_row] != nullptr) {
                char msg[48];
                snprintf(msg, sizeof(msg),
                "%s's %s cannot move to %c%c\n", 
                getColorString().c_str(), getType().c_str(), colChar(dCol), rowChar(dRow));
                //cout << msg << endl;
            }
        }
        return true;
    }
    else if (abs(difC) != abs(difR)) return false;
    //diagonal move
    //note: difC and difR should always be the same abs value, otherwise its not diagonal.
    for (int i = 1; i < abs(difC); i++) {
        //if blocked
        if (board[m_col + (stepC * i)][m_row + (stepR * i)] != nullptr) {
                char msg[48];
                snprintf(msg, sizeof(msg),
                "%s Queen's move is blocked.", 
                getColorString().c_str());
                //cout << msg << endl;
                return false;
        }
    }
    return true;
}

bool Queen::opponentIsChecked(ChessPiece* board[NUM_TILE][NUM_TILE]) {
    //north
    int cInd = m_col;
    int rInd = m_row + 1;
    while (rInd < NUM_TILE) {
        PieceType type = isEnemyKing(board[cInd][rInd++]);
        if (type == KING) return true;
        else if (type == NOTKING) break;
    }
    //northEast
    cInd = m_col + 1;
    rInd = m_row + 1;
    while (rInd < NUM_TILE && cInd < NUM_TILE) {
        PieceType type = isEnemyKing(board[cInd++][rInd++]);
        if (type == KING) return true;
        else if (type == NOTKING) break;
    }
    //East
    cInd = m_col + 1;
    rInd = m_row;
    while (cInd < NUM_TILE) {
        PieceType type = isEnemyKing(board[cInd++][rInd]);
        if (type == KING) return true;
        else if (type == NOTKING) break;
    }
    //southEast
    cInd = m_col + 1;
    rInd = m_row-1;
    while (cInd < NUM_TILE && rInd > 0) {
        PieceType type = isEnemyKing(board[cInd++][rInd--]);
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
    //southWest
    cInd = m_col-1;
    rInd = m_row-1;
    while (cInd  > 0 && rInd > 0) {
        PieceType type = isEnemyKing(board[cInd--][rInd++]);
        if (type == KING) return true;
        else if (type == NOTKING) break;
    }
    //West
    cInd = m_col-1;
    rInd = m_row;
    while (cInd  > 0) {
        PieceType type = isEnemyKing(board[cInd--][rInd]);
        if (type == KING) return true;
        else if (type == NOTKING) break;
    }
    //northWest
    cInd = m_col-1;
    rInd = m_row+1;
    while (cInd  > 0 && rInd < NUM_TILE) {
        PieceType type = isEnemyKing(board[cInd--][rInd++]);
        if (type == KING) return true;
        else if (type == NOTKING) break;
    }
    return false;
}