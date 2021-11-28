#include "ChessBoard.hpp"
#include "errors.hpp"

using namespace std;

ChessBoard::ChessBoard()
{
    resetBoard();
}

int ChessBoard::submitMove(string source, string destination)
{
    //process input
    int validSrcInputStatus = checkValidInput(source);
    if (validSrcInputStatus != 0) return validSrcInputStatus;

    int validDestInputStatus = checkValidInput(destination);
    if (validDestInputStatus != 0) return validDestInputStatus;

    char srcPos[2];
    srcPos[0] = source[0];
    srcPos[1] = source[1];

    char destPos[2];
    destPos[0] = destination[0];
    destPos[1] = destination[1];
    
    //check which piece is on source tile
    auto& currentPiece = getPiece(srcPos); //TODO: error check for empty tile
    //check for correct player color
    if (currentPiece.getColor() != _playerTurn)
    {
        cerr << "It is not";
        if (_playerTurn == WHITE)
            cerr << "Black";
        else
            cerr << "White";
         cerr << "’s turn to move!" << endl;
        return INVALID_PLAYER;
    }
    //determine if move is legal

    //is a legal move for selected piece
    //move -> update piece state.
    //check if killed any enemy piece.

    //toggle playerturn;


}

int ChessBoard::checkValidInput(string const& input)
{
    if (input.length() != 2) 
    {
        cerr << "Input length is incorrect!" << 
        " Input must consist of 2 characters.\n";
        return INCORRECT_INPUT_LENGTH;
    }
    if (input[0] < 'A' || input[0] > 'H' ||
    input[1] < '1' || input[1] > '8')
    {
        cerr << "Input is not valid!" <<
        " Input must consist of a letter A-H and a number 1-8.\n";
        return INVALID_INPUT;
    }

    return NO_ERROR;
}

void ChessBoard::resetBoard()
{

}