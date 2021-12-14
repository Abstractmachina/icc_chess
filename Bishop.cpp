#include "Bishop.hpp"

using namespace std;

bool Bishop::isValidMove(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    int colDif = dCol - m_col;
    int rowDif = dRow - m_row;
    //check valid move
    if (abs(colDif) == abs(rowDif)) {
        int stepCol = colDif / abs(colDif); //1 going right or -1 going left
        int stepRow = rowDif / abs(rowDif);
        //check if path is blocked
        for (int i = 1; i < abs(colDif); i++) {
            //path is blocked
            if (board[m_col + stepCol * i][m_row + stepRow * i] != nullptr) return false;
        } 
        //valid move
        return true;
    }
    //cout << "Invalid Move! Bishop can only move diagonally.\n";
    return false;
}

bool Bishop::opponentIsChecked(ChessPiece* board[NUM_TILE][NUM_TILE]) {

    //left top quadrant
    int cInd = m_col;
    int rInd = m_row;
    cInd--; rInd++;
    ChessPiece* selection = nullptr;

    while (cInd >= 0 && rInd < NUM_TILE) {
        selection = board[cInd][rInd];
        if ( selection != nullptr) {
            if (selection->getType() == "King" && 
                selection->getColor() != m_color) 
                return true;
            else break;
        }
        cInd--; rInd++;
    }

    //left bottom quadrant
    cInd = m_col; 
    rInd = m_row;
    cInd--; rInd--;
    while (cInd >= 0 && rInd >= 0) {
        selection = board[cInd][rInd];
        if ( selection != nullptr) {
            if (selection->getType() == "King" && 
                selection->getColor() != m_color) 
                return true;
            else break;
        }
        cInd--; rInd--;
    }
    //right top quadrant
    cInd = m_col;
    rInd = m_row;
    cInd++; rInd++;
    while (cInd < NUM_TILE && rInd < NUM_TILE) {
        selection = board[cInd][rInd];
        if ( selection != nullptr) {
            if (selection->getType() == "King" && 
                selection->getColor() != m_color) 
                return true;
            break;
        }
        cInd++; rInd++;
    }

    //right bottom quadrant
    cInd = m_col;
    rInd = m_row;
    cInd++; rInd--;
    while (cInd < NUM_TILE && rInd >= 0) {
        selection = board[cInd][rInd];
        if ( selection != nullptr) {
            if (selection->getType() == "King" && 
                selection->getColor() != m_color) 
                return true;
            else break;
        }
        cInd++; rInd--;
    }
    return false;  
}