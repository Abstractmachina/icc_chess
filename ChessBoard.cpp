#include "ChessBoard.h"
#include "errors.hpp"

using namespace std;

ChessBoard::ChessBoard() {
    resetBoard();
}

ChessBoard::~ChessBoard() {
}

void ChessBoard::submitMove(string source, string destination)
{
    //process input
    try {
        checkValidInput(source, "submitMove()");
        checkValidInput(destination, "submitMove()");
    } catch ( const exception& e) {
        cerr << e.what();
        return;
    }
    //convert to int
    int srcPos[2] = { source[0] - 'A', source[1] - '1' };
    int destPos[2] = { destination[0] - 'A', destination[1] - '1' };
    
    ChessPiece* selected = nullptr;
    try {
        //check which piece is on source tile
        selected = getPiece(srcPos[0], srcPos[1]);
        //check if correct player turn
        checkCorrectPlayer(selected);
    } catch (const exception& e) {
        cerr <<e.what();
        return;
    }

    //attempt move

    //check if valid move
    if (!selected->isValidMove(destPos[0], destPos[1], m_board)) {
        char msg[48];
        snprintf(msg, sizeof(msg), "%s's %s cannot move to %c%c\n",
        selected->getColorString().c_str(), selected->getType().c_str(), destination[0], destination[1]);
        cerr << msg << endl;
        return;
    }

    //peek
    ChessPiece* destContent = nullptr;
    peekMove(selected, srcPos, destPos, destContent);

    //if in check, query if move resolves check.
    if ((m_whiteCheck && m_playerTurn == WHITE) || (m_blackCheck && m_playerTurn == BLACK)) {
        
        //if move does not resolve check, undo. 
        if (findKing(m_playerTurn)->kingScan(m_board)) {
            char msg[48];
            snprintf(msg, sizeof(msg),
            "Illegal move. %s's King is still in check.\n",
            selected->getColorString().c_str());
            //reverse move
            undoMove(selected, srcPos, destPos, destContent);
            cerr <<msg << endl;
            return;
        }
        //if check resolved, unflag and commit move.
        (m_playerTurn == WHITE) ? m_whiteCheck = false : m_blackCheck = false;
    }

    commitMove(selected, srcPos, destPos, destContent);

    //see if new move puts opponent in check
    if (selected->opponentIsChecked(m_board)) {
        if (m_playerTurn == WHITE) {
            m_blackCheck = true;
            cerr << "Black";
        }
        else {
            m_whiteCheck = true;
            cerr << "White";
        }
        cerr << " is in check\n";
    }
    //toggle playerturn;
    (m_playerTurn == WHITE) ? m_playerTurn = BLACK : m_playerTurn = WHITE;
}

void ChessBoard::peekMove(ChessPiece* piece, int src[2], int dest[2], ChessPiece*& destContent) {
    destContent = m_board[dest[0]][dest[1]];
    m_board[dest[0]][dest[1]] = piece;
    m_board[src[0]][src[1]] = nullptr;
}

void ChessBoard::undoMove(ChessPiece* piece, int src[2], int dest[2], ChessPiece*& destContent) {
    m_board[src[0]][src[1]] = piece;
    m_board[dest[0]][dest[1]] = destContent;
}

void ChessBoard::commitMove(ChessPiece* piece, 
int src[2], int dest[2], ChessPiece*& destContent) {
    printf("%s's %s moves from %c%c to %c%c", 
            piece->getColorString().c_str(), 
            piece->getType().c_str(), 
            char(src[0] + 'A'), char(src[1] + '1'), 
            char(dest[0] + 'A'), char(dest[1] + '1'));
    
    piece->setPosition(dest);
    if (destContent != nullptr) {
        printf(" taking %s's %s", 
        destContent->getColorString().c_str(), 
        destContent->getType().c_str());
        delete destContent;
    }
    cerr << endl;
}

bool ChessBoard::isCheckmated(PlayerColor checkedSide) {
    auto king = findKing(checkedSide);
    //check if king can find safety by moving.

    int c = king->getC();
    int r = king->getR();
    int src[2] = { c, r }; 
    for (int col = c-1; col <= c+1; col++) {
        for (int row = r-1; row <= r+1; row++) {
            if (
            col < 0 || col >= NUM_TILES || 
            row < 0 || row >= NUM_TILES ||
            (col == c && row == r)          ) continue;
            int dest[2] = {col, row};
            ChessPiece* destContent = nullptr;
            peekMove(king, src, dest, destContent);
            
        }
    }
    //if not, by taking an opponent.
    //if not, by blocking path.
    //if all false -> checkmate!

    return false;
}

ChessPiece* ChessBoard::findKing(PlayerColor color) {
    for(int i = 0; i < NUM_TILES; i++){
        for(int j = 0; j < NUM_TILES; j++) {
            auto sel = m_board[i][j];
            if (sel != nullptr && sel->getType() == "King" && sel->getColor() == color)
                return sel;
        }
    }
    return nullptr;
}

void ChessBoard::checkCorrectPlayer(ChessPiece const* p) const {
    if (p->getColor() != m_playerTurn)
    {
        string msg = "It is not ";
        string wrongCol = (m_playerTurn == WHITE) ? "Black" : "White";
        msg += wrongCol;
        msg += "’s turn to move!\n";
        throw Err_WrongPlayer(msg);
    }
}

void ChessBoard::checkValidInput(string const& input, string const& extraInfo) const {
    if (input.length() != 2) 
        throw Err_IncorrectInputLength("Input must consist of 2 characters.\n");
    if (input[0] < 'A' || input[0] > 'H' ||
        input[1] < '1' || input[1] > '8'    )
        throw Err_InvalidInput(extraInfo);
}

ChessPiece* ChessBoard::getPiece(int col, int row) const {
    if (m_board[col][row] == nullptr) { 
        char msg[48];
        snprintf(msg, sizeof(msg),
        "There is no piece at position %c%c!\n", char(col + 'A'), char(row + '1'));
        throw Err_InvalidInput(msg);
    }
    ChessPiece* result = m_board[col][row]; 
    return result;
}

void ChessBoard::resetBoard() {
    cerr << "A new chess game is started!\n";
    //assign nullptr to all tiles
    for (int row = 0; row < NUM_TILES; row++) {
        for (int col = 0; col < NUM_TILES; col++) {
            m_board[col][row] = nullptr; 
        }
    }
    m_playerTurn = WHITE;
    //init pieces
    //Kings
    setTile(new King(WHITE), 'E', '1');
    setTile(new King(BLACK), 'E', '8');
    //Queens
    setTile(new Queen(WHITE), 'D', '1');
    setTile(new Queen(BLACK), 'D', '8');
    //Bishops
    setTile(new Bishop(WHITE), 'C', '1');
    setTile(new Bishop(WHITE), 'F', '1');
    setTile(new Bishop(BLACK), 'C', '8');
    setTile(new Bishop(BLACK), 'F', '8');
    //Knights
    setTile(new Knight(WHITE), 'B', '1');
    setTile(new Knight(WHITE), 'G', '1');
    setTile(new Knight(BLACK), 'B', '8');
    setTile(new Knight(BLACK), 'G', '8');
    //Rooks
    setTile(new Rook(WHITE), 'A', '1');
    setTile(new Rook(BLACK), 'H', '1');
    setTile(new Rook(WHITE), 'A', '8');
    setTile(new Rook(BLACK), 'H', '8');
    //Pawms
    for (int i =0; i < 8; i++) setTile(new Pawn(WHITE), char('A' + i), '2');
    for (int i =0; i < 8; i++) setTile(new Pawn(BLACK), char('A' + i), '7');
}

//assign piece to tile. col (A-H) row (1-8)
void ChessBoard::setTile(ChessPiece* piece, char col, char row) {
    if (col < 'A' || col > 'H' || row < '1' || row > '8') {
        //cerr << "setTile Error: Input "<< col << row << "is invalid.\n";
        //cerr << "Column must be a letter A-H and row must be a number 1-8.\n";
        string errMsg = "setTile() error: Input(";
        errMsg += col;
        errMsg += " ; ";
        errMsg += row;
        errMsg += ") is invalid.\n";
        errMsg += "Column must be a letter A-H and row must be a number 1-8.\n";
        throw Err_InvalidInput(errMsg);
    }
    int colI = (int)col - 'A';
    int rowI = (int)row - '1';
    m_board[colI][rowI] = piece;
    piece->setPosition(col, row);
    //if (m_board[colI][rowI] == nullptr ) cerr << "piece not assigned.\n";
    //else cerr << "current piece: " << m_board[colI][rowI]->getType() << endl;
}

void ChessBoard::print() const {
    for (int row = 0; row < NUM_TILES; row++) {
        for (int col = 0; col < NUM_TILES; col++) {
            auto* it = m_board[col][row];
            cerr << "Pos(" << char(col + 'A') << " ; " << char(row + '1') << "): "; 
            if (it == nullptr) cerr << "empty\n";
            else cerr << it->getType() << endl;
        }
    }
}