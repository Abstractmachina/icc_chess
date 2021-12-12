#include "ChessPiece.hpp"

using namespace std;

void ChessPiece::updatePosition(int const& destCol, int const& destRow, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    commentSuccessfulMove(destCol, destRow);
    if (board[destCol][destRow] != nullptr) captureEnemy(destCol, destRow, board);
    board[m_col][m_row] = nullptr;
    m_col = destCol;
    m_row = destRow;
    board[destCol][destRow] = this;
    cerr << endl;
}

void ChessPiece::captureEnemy(int const& col, int const& row, ChessPiece* board[NUM_TILE][NUM_TILE]) {
    ChessPiece* capture = board[col][row];
    commentSucessfulCapture(capture);
    board[col][row] = nullptr;
    delete capture;
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

char* ChessPiece::getPosition() const { 
    char res[] = {char(m_col + 'A'), char(m_row + '1')}; 
    return res;
}

void ChessPiece::setPosition(char col, char row) { 
    m_col = int(col) - 'A'; 
    m_row = int(row) - '1'; 
}