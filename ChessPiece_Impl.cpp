#include "ChessPiece_Impl.hpp"

using namespace std;

void Bishop::move(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    int colDif = dCol - m_col;
    int rowDif = dRow - m_row;
    //check valid move
    if (abs(colDif) == abs(rowDif)) {
        int stepCol = colDif / abs(colDif); //1 going right or -1 going left
        int stepRow = rowDif / abs(rowDif);
        //check if path is blocked
        for (int i = 1; i < abs(colDif); i++) {
            if (board[m_col + stepCol * i][m_row + stepRow * i] != nullptr) {
                char msg[48];
                snprintf(msg, sizeof(msg),
                "%s's %s cannot move to %c%c!\n", 
                getColorString().c_str(), getType().c_str(), char(dCol + 'A'), char(dRow + '1'));
                throw Err_InvalidMove(msg);
            }
        } 
        //valid move
        updatePosition(dCol, dRow, board);
        
        return;
    }
    throw Err_InvalidMove("Invalid Move! Bishop can only move diagonally.\n");
}

bool Bishop::isInCheck(ChessPiece* board[NUM_TILE][NUM_TILE]) {
    
    //left top quadrant
    int cInd = m_col;
    int rInd = m_row;
    cInd--;
    rInd++;
    ChessPiece* selection;

    while (cInd >= 0 && rInd < NUM_TILE) {

        selection = board[cInd][rInd];
        if ( selection != nullptr) {
            if (selection->getType() == "King") return true;
            else break;
        }
        cInd--;
        rInd++;

    }
    
    //left bottom quadrant
    cInd = m_col; rInd = m_row;
    cInd--; rInd--;
    while (cInd >= 0 && rInd >= 0) {
        selection = board[cInd][rInd];
        if ( selection != nullptr) {
            if (selection->getType() == "King") return true;
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
            if (selection->getType() == "King") return true;
            else break;
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
            if (selection->getType() == "King") return true;
            else break;
        }
        cInd++; rInd--;
    }
    return false;  
}

/*=========================   KING    =================================*/

void King::move(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    //evrytime king wants to move, need to check if move is legal and not trigger check.
}

bool King::isInCheck(ChessPiece* board[NUM_TILE][NUM_TILE]) {
    return false;
}


/*======================   KNIGHT    ==============================*/
void Knight::move(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    if (dCol == m_col - 2 || dCol == m_col + 2 ) {
        if (dRow == m_row -1 || dRow == m_row + 1) {
            updatePosition(dCol, dRow, board);
            return;
        }
    }
    if (dCol == m_col - 1 || dCol == m_col + 1 ) {
        if (dRow == m_row - 2 || dRow == m_row + 2) {
            updatePosition(dCol, dRow, board);
            return;
        }
    }
    char msg[64];
    snprintf(msg, sizeof(msg),
    "%s's Knight cammot move to %c%c\n!", getColorString().c_str(), colChar(dCol), rowChar(dRow));
    throw Err_InvalidMove("Knight Invalid Move!\n");
}
bool Knight::isInCheck(ChessPiece* board[NUM_TILE][NUM_TILE]) {
    return false;
}

/*======================   PAWN    ==============================*/

void Pawn::move(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    int colDif = dCol - m_col;
    int rowDif = dRow - m_row;

    //pawn cannot move backwards
    if ((rowDif < 1 && m_color == WHITE) ||
        (rowDif > -1 && m_color == BLACK)     )
        throw Err_InvalidMove("Pawn cannot move backwards.\n");
    if (abs(rowDif) > 2 || abs(colDif > 1)) 
        throw Err_InvalidMove("Invalid Move. Out of Range.\n");

    //diagonal capture condition
    if (diagonalCapture(dCol, dRow, board)) return;

    //not diagonal capture condition, pawn can only move straight forward.
    else if (dCol != m_col)
        throw Err_InvalidMove("Invalid move. Pawn can only go straight unless capturing diagonally.\n");

    //move two squares forward condition
    if (moveTwoSquares(dCol, dRow, board)) return;

    //move regular
    moveOneSquare(dCol, dRow, board);

    //only true on first turn, so toggle in any case
    if (m_firstTurn == true) m_firstTurn = false;
    
}

bool Pawn::moveOneSquare(int const& dCol, int const& dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    if (abs(dRow - m_row) == 1) {
        updatePosition(dCol, dRow, board);
        return true;
    }
    return false;
}

bool Pawn::diagonalCapture(int const& dCol, int const& dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    if (m_firstTurn == true && (abs(dCol - m_col) == 1) 
                                && abs(dRow - m_row ) == 1) {
        if (board[dCol][dRow] == nullptr)
            throw Err_InvalidMove("Invalid move. Diagonal capture on empty tile.\n");
        //else do nothing and go to valid move condition;
        
        //valid diagonal capture
        updatePosition(dCol, dRow, board);
        m_firstTurn = false;
        return true;
    }
    return false; //diagonal capture condition not met
}

bool Pawn::moveTwoSquares(int const& dCol, int const& dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    if (abs(dRow - m_row) == 2) {
        if (m_firstTurn == false)
        throw Err_InvalidMove("Pawn can only move two squares on first turn.\n");
        //check if move blocked
        int firstRowFront;
        if (m_color == WHITE) firstRowFront = m_row + 1;
        else firstRowFront = m_row - 1;
        if (board[m_col][firstRowFront] != nullptr) {
            string msg = "Invalid move. Pawn is blocked by a ";
            msg += board[m_col][firstRowFront]->getType();
            throw Err_InvalidMove(msg);
        }
        //move regular
        updatePosition(dCol, dRow, board);
        
        m_firstTurn = false;
        return true;
    }
    return false;
}

bool Pawn::isInCheck(ChessPiece* board[NUM_TILE][NUM_TILE]) {
    return false;
}

void Queen::move(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {

}

bool Queen::isInCheck(ChessPiece* board[NUM_TILE][NUM_TILE]) {
    return false;
}

void Rook::move(int dCol, int dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {

}

bool Rook::isInCheck(ChessPiece* board[NUM_TILE][NUM_TILE]) {
    return false;
}