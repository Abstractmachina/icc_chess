#include "Pawn.hpp"

using namespace std;

bool Pawn::isValidMove(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    int colDif = dCol - m_col;
    int rowDif = dRow - m_row;

    //pawn cannot move backwards
    if ((rowDif < 1 && m_color == WHITE) || (rowDif > -1 && m_color == BLACK)) {
        //cout << "Pawn cannot move backwards.\n";
        return false;
    }
    //out of range
    if (abs(rowDif) > 2 || abs(colDif > 1)) {
        //cout << "Pawn Invalid Move. Out of Range.\n";
        return false;
    }

    //diagonal capture condition
    if (diagonalCapture(dCol, dRow, board)) return true;

    //not diagonal capture condition, pawn can only move straight forward.
    else if (dCol != m_col) {
        //cout <<"Invalid move. Pawn can only go straight unless capturing diagonally.\n";
        return false;
    }

    //move two squares forward condition
    if (moveTwoSquares(dCol, dRow, board)) return true;
    //only true on first turn, so flip to false to be safe in any case
    if (m_firstTurn == true) m_firstTurn = false;

    //move regular
    if (moveOneSquare(dCol, dRow, board))return true;

    return false; //catch all condition
}

bool Pawn::moveOneSquare(int const& dCol, int const& dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    if (abs(dRow - m_row) == 1 && board[dCol][dRow] == nullptr) {
        return true;
    }
    return false;
}

bool Pawn::diagonalCapture(int const& dCol, int const& dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    if ((abs(dCol - m_col) == 1) && abs(dRow - m_row ) == 1) {
        if (board[dCol][dRow] == nullptr) {
            //cout << "Invalid move. Diagonal capture on empty tile.\n";
            return false;
        }
        //else do nothing and go to valid move condition
        //valid diagonal capture
        return true;
    }
    return false; //diagonal capture condition not met
}

bool Pawn::moveTwoSquares(int const& dCol, int const& dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    if (abs(dRow - m_row) == 2 && board[dCol][dRow] == nullptr) {
        if (m_firstTurn == false) {
            //cout << "Pawn can only move two squares on first turn.\n";
            return false;
        }
        //check if move blocked
        int firstRowFront;
        if (m_color == WHITE) firstRowFront = m_row + 1;
        else firstRowFront = m_row - 1;
        if (board[m_col][firstRowFront] != nullptr) {
            string msg = "Invalid move. Pawn is blocked by a ";
            msg += board[m_col][firstRowFront]->getType();
            //cout <<msg << endl;
            return false;
        }
        //move regular
        //updatePosition(dCol, dRow, board);
        m_firstTurn = false;
        return true;
    }
    return false;
}

bool Pawn::opponentIsChecked(ChessPiece* board[NUM_TILE][NUM_TILE]) {
    int front = (m_color == WHITE) ? 1 : -1;
    if (m_firstTurn) {
        //move two squares
        if (isEnemyKing(board[m_col][m_row+front]) == EMPTY &&
            isEnemyKing(board[m_col][m_row+(front*2)]) == KING) return true;
    } 
    if (isTileEnemyKing(m_col-1, m_row+front, board))return true;
    if (isTileEnemyKing(m_col+1, m_row+front, board))return true;
    if (isTileEnemyKing(m_col, m_row+front, board))return true;
    return false;
}