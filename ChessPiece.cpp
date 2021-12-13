#include "ChessPiece.hpp"
#include "ChessPiece_Impl.hpp"

using namespace std;

void ChessPiece::updatePosition(int const& dCol, int const& dRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    //take snapshot of original.
    //move to new pos
    //if in check, verify no longer in check.
    //if all clear, delete snapshot.

    //cerr << getColorString() << " " << getType() << " check condition: " << m_inCheckCondition << endl;

    auto destContent = board[dCol][dRow];
    board[dCol][dRow] = this;
    board[m_col][m_row] = nullptr;
    //check flag set. querying if move will release check.
    if (m_inCheckCondition) {
        auto king = getKing(board);
        if (king->kingScan(board)) {
            char msg[64];
            snprintf(msg, sizeof(msg),
            "Illegal move. %s's King is still in check.\n",
            getColorString().c_str());
            //reverse move
            board[m_col][m_row] = this;
            board[dCol][dRow] = destContent;
            throw Err_Checked(msg);
        } 
        //check condition does not apply anymore, reset flag
        m_inCheckCondition = false;
    }
    //legal move
    commentSuccessfulMove(dCol, dRow);
    if (destContent != nullptr) {
        commentSucessfulCapture(destContent);
        delete destContent;
    }
    m_col = dCol;
    m_row = dRow;

    cerr << endl;
}

void ChessPiece::captureEnemy(int const& col, int const& row, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    ChessPiece* capture = board[col][row];
    commentSucessfulCapture(capture);
    board[col][row] = nullptr;
    delete capture;
}


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

void ChessPiece::commentSuccessfulMove(int const& dCol, int const& dRow) const {
    printf("%s's %s moves from %c%c to %c%c", 
            getColorString().c_str(), getType().c_str(), char(m_col + 'A'), char(m_row + '1'), char(dCol + 'A'), char(dRow + '1'));
}

void ChessPiece::commentSucessfulCapture(ChessPiece* capture) const {
    printf(" taking %s's %s", capture->getColorString().c_str(), capture->getType().c_str());
}

std::string ChessPiece::getColorString() const {
    if (m_color == WHITE) return "White";
    else return "Black";
}

void ChessPiece::setPosition(char col, char row) { 
    m_col = int(col) - 'A'; 
    m_row = int(row) - '1'; 
}