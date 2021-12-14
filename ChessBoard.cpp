#include "ChessBoard.h"
#include "errors.hpp"

#include <vector>

using namespace std;

ChessBoard::ChessBoard() {
    resetBoard();
}

ChessBoard::~ChessBoard() {
}

void ChessBoard::submitMove(string source, string destination)
{
    if (m_gameOver) exit(0);

    //================  PROCESS INPUT   ==========================
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

    //===============   ATTEMPT MOVE    ==========================

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

    //commit move if legal
    commitMove(selected, srcPos, destPos, destContent);
    //print();
    //see if new move puts opponent in check
    if (selected->opponentIsChecked(m_board)) {
        PlayerColor checkedPlayer;
        if (m_playerTurn == WHITE) {
            m_blackCheck = true;
            checkedPlayer = BLACK;
            cerr << "Black";
        }
        else {
            m_whiteCheck = true;
            checkedPlayer = WHITE;
            cerr << "White";
        }
        cerr << " is in check";
        if (isCheckmated(checkedPlayer)) {
            m_gameOver = true;
            cerr << "mate\n";
            exit(0);
        }
        cerr <<endl;
    }

    togglePlayerTurn();
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
        destContent = nullptr;
    }
    cerr << endl;
}

bool ChessBoard::isCheckmated(PlayerColor checkedSide) {
    /*
    Rules of Checkmate
    1) The king is in check.
    2) There is no move that the king can make that takes it out of check.
    3) It is not possible to capture the attacking piece.
    4) It is not possible to interpose a piece between the king and the attacking piece.
    5) (3) and (4) are impossible if there is more than one attacking piece.
    6) (4) is impossible if the attacking piece is a knight.
    */
    auto king = findKing(checkedSide);
    int kingC = king->getC();
    int kingR = king->getR();
    int kingPos[2] = { kingC, kingR }; 
    //find how many pieces are checking king. 
    vector<ChessPiece*> attackers;
    for (int r = 0; r < NUM_TILES; r++) {
        for (int c = 0; c < NUM_TILES; c++) {
            ChessPiece* sel = m_board[c][r];
            if (sel != nullptr && 
            sel->getColor() != checkedSide &&
            sel->opponentIsChecked(m_board)) 
            { attackers.push_back(sel); }
        }
    }

    //attackers size should be at least 1 at this point.
    if (attackers.size() == 0) {
        throw Err_Checked("isCheckmated() error: no attackers found.\n");
    }
    //if more than 2 attacker -> double check -> only way is to move king
    //double check condition
    if (attackers.size() > 1) {
        //check if king can find safety by moving.
        for (int col = kingC-1; col <= kingC+1; col++) {
            for (int row = kingR-1; row <= kingR+1; row++) {
                if (
                col < 0 || col >= NUM_TILES || 
                row < 0 || row >= NUM_TILES ||
                (col == kingC && row == kingR)) continue;
                int dest[2] = {col, row};
                ChessPiece* destContent = nullptr;
                peekMove(king, kingPos, dest, destContent);
                //if no longer in check
                if (!king->kingScan(m_board)) { 
                    undoMove(king, kingPos, dest, destContent);
                    return false;
                }
                undoMove(king, kingPos, dest, destContent);
            }
        }
        /*
        if false was not returned by this point,
        it means king cannot move to safety, so double check applies and 
        therefore it is checkmate
        */
        return true;
    }
    
    //single check condition
    else {
        //try capturing the opponent.
        ChessPiece* attacker = attackers.back();
        int attC = attacker->getC();
        int attR = attacker->getR();

        for (int i = 0; i < NUM_TILES; i++) {
            for (int j = 0; j < NUM_TILES; j++) {
                ChessPiece* counterAttacker = m_board[i][j];
                
                if (counterAttacker != nullptr && counterAttacker->getColor() == checkedSide) {
                    //attacker can be captured -> not checkmate
                    if (counterAttacker->isValidMove(attC, attR, m_board)) {
                        return false;
                    }
                }
            }
        }
        
        /*if attacker cannot be captured and it is a knight, then it is checkmate,
        as it cannot be blocked.*/
        if (attacker->getType() == "Knight") return true;


        //last possible solution: attempt to block path
        //possible pieces: queen, rook, bishop, pawn
        int cDif = attC - kingC;
        int rDif = attR - kingR;
        
        //vertical movement ->queen, rook, pawn
        if (attC == kingC) {
            int stepR = rDif / abs(rDif); //-1 or 1
            for (int i = 1; i < abs(rDif); i++) {
                //find all friendly pieces
                for (int r = 0; r < NUM_TILES; r++) {
                    for (int c = 0; c < NUM_TILES; c++) {
                        ChessPiece* friendly = m_board[c][r];
                        if (friendly != nullptr && 
                        friendly->getType() != "Knight" &&
                        friendly->getColor() == checkedSide &&
                        friendly->isValidMove(attC, attR + stepR * i, m_board))
                        { return false; } //can be blocked 
                    }
                }
            }
        }
        //horizontal movement -> queen, rook
        else if (attR == kingR) {
            int stepC = cDif / abs(cDif); //-1 or 1
            for (int i = 1; i < abs(cDif); i++) {

                //find all friendly pieces
                for (int r = 0; r < NUM_TILES; r++) {
                    for (int c = 0; c < NUM_TILES; c++) {
                        ChessPiece* friendly = m_board[c][r];
                        if (friendly != nullptr && 
                        friendly->getType() != "Knight" &&
                        friendly->getColor() == checkedSide &&
                        friendly->isValidMove(attC + stepC * i, attR, m_board))
                        { return false; } //can be blocked 
                    }
                }
            }
        }
        //diagonal movement -> queen, bishop
        else if (abs(cDif) == abs(rDif)) {
            int stepC = cDif / abs(cDif); //-1 or 1
            int stepR = rDif / abs(rDif); //-1 or 1
            for (int i = 1; i < abs(cDif); i++) {
                //find all friendly pieces
                for (int r = 0; r < NUM_TILES; r++) {
                    for (int c = 0; c < NUM_TILES; c++) {
                        ChessPiece* friendly = m_board[c][r];
                        if (friendly != nullptr && 
                        friendly->getType() != "Knight" &&
                        friendly->getColor() == checkedSide &&
                        friendly->isValidMove(kingC + stepC*i, kingR + stepR*i, m_board))
                        { return false; } //can be blocked 
                    }
                }
            }
        }
    }
    //if all fails -> checkmate!
    return true;
}

bool ChessBoard::isStaleMated(PlayerColor player) {
    /*
    Rules of stalemate
    1) king is not check
    2) there are no possible moves player can make
    3)only two kings are left
    */

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

void ChessBoard::togglePlayerTurn() {
    (m_playerTurn == WHITE) ? m_playerTurn = BLACK : m_playerTurn = WHITE;
}


//================================ Utility ============================================

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

void ChessBoard::resetBoard() {
    cerr << "A new chess game is started!\n";
    
    //reset all members
    m_playerTurn = WHITE;
    m_gameOver = false;
    m_whiteCheck = false; 
    m_blackCheck = false;

    //init pieces
    //assign nullptr to all tiles
    for (int row = 0; row < NUM_TILES; row++) {
        for (int col = 0; col < NUM_TILES; col++) m_board[col][row] = nullptr; 
    }
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
    setTile(new Rook(WHITE), 'H', '1');
    setTile(new Rook(BLACK), 'A', '8');
    setTile(new Rook(BLACK), 'H', '8');
    //Pawms
    for (int i =0; i < 8; i++) setTile(new Pawn(WHITE), char('A' + i), '2');
    for (int i =0; i < 8; i++) setTile(new Pawn(BLACK), char('A' + i), '7');
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
}

void ChessBoard::print() const {
    for (int row = 0; row < NUM_TILES; row++) {
        for (int col = 0; col < NUM_TILES; col++) {
            auto* it = m_board[col][row];
            cerr << "Pos(" << char(col + 'A') << " ; " << char(row + '1') << "): "; 
            if (it == nullptr) cerr << "empty\n";
            else cerr << it->getColorString() << " " << it->getType() << endl;
        }
    }
}