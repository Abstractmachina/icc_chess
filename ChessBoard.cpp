#include "ChessBoard.hpp"
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
        cerr << e.what() << endl;
        return;
    }
    //convert to int
    int srcPos[2] = { source[0] - 'A', source[1] - '1' };
    int destPos[2] = { destination[0] - 'A', destination[1] - '1' };
    
    //cerr <<"whitecheck: " << m_whiteCheck << endl;
    //cerr <<"blackcheck: " << m_blackCheck << endl;
    
    ChessPiece* currentPiece = nullptr;
    try {
        //check which piece is on source tile
        currentPiece = getPiece(srcPos[0], srcPos[1]);
        //check if correct player turn
        checkCorrectPlayer(currentPiece);
    } catch (const exception& e) {
        cerr <<e.what();
        return;
    }
    //attempt move
    cerr << "move: " << source << "->" << destination << endl;
    try { 
         currentPiece->move(destPos[0], destPos[1], m_board);
    } catch (const exception& e) {
        cerr << e.what();
        return;
    }
    //see if new move puts opponent in check
    if (currentPiece->isInCheck(m_board)) {
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
    if (m_playerTurn == WHITE)  m_playerTurn = BLACK;
    else                        m_playerTurn = WHITE;
}

void ChessBoard::checkCorrectPlayer(ChessPiece const* p) const {
    if (p->getColor() != m_playerTurn)
    {
        string msg = "It is not ";
        string wrongCol;
        if (m_playerTurn == WHITE)
            wrongCol = "Black";
        else
            wrongCol = "White";
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
    setTile(new King(WHITE, m_whiteCheck), 'E', '1');
    setTile(new King(BLACK, m_blackCheck), 'E', '8');
    //Queens
    setTile(new Queen(WHITE, m_whiteCheck), 'D', '1');
    setTile(new Queen(BLACK, m_blackCheck), 'D', '8');
    //Bishops
    setTile(new Bishop(WHITE, m_whiteCheck), 'C', '1');
    setTile(new Bishop(WHITE, m_whiteCheck), 'F', '1');
    setTile(new Bishop(BLACK, m_blackCheck), 'C', '8');
    setTile(new Bishop(BLACK, m_blackCheck), 'F', '8');
    //Knights
    setTile(new Knight(WHITE, m_whiteCheck), 'B', '1');
    setTile(new Knight(WHITE, m_whiteCheck), 'G', '1');
    setTile(new Knight(BLACK, m_blackCheck), 'B', '8');
    setTile(new Knight(BLACK, m_blackCheck), 'G', '8');
    //Rooks
    setTile(new Rook(WHITE, m_whiteCheck), 'A', '1');
    setTile(new Rook(BLACK, m_blackCheck), 'H', '1');
    setTile(new Rook(WHITE, m_whiteCheck), 'A', '8');
    setTile(new Rook(BLACK, m_blackCheck), 'H', '8');
    //Pawms
    for (int i =0; i < 8; i++) setTile(new Pawn(WHITE, m_whiteCheck), char('A' + i), '2');
    for (int i =0; i < 8; i++) setTile(new Pawn(BLACK, m_blackCheck), char('A' + i), '7');
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