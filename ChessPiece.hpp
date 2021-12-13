#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <iostream>
#include <string>

//#include "utilities.cpp"

enum PlayerColor{WHITE, BLACK};
enum PieceType{ EMPTY, NOTKING, KING};

//class King;
//abstract base class.
class ChessPiece {
    protected:
        /*position will be stored as integers internally for ease of calc. 
        displayed as chars externally for readability*/
        static int const NUM_TILE = 8;
        int m_col, m_row; //row = 'A'-'H', col = '1'-'8'
        const PlayerColor m_color;
        /*referenced to check state in ChessBoard.*/
        bool& m_inCheckCondition;

        void updatePosition(int const& destCol, int const& destRow, ChessPiece* board[8][8]);
        void captureEnemy(int const& destCol, int const& destRow, ChessPiece* board[8][8]);
        void commentSuccessfulMove(int const& dCol, int const& dRow) const;
        void commentSucessfulCapture(ChessPiece* capture) const;
    public:
        ChessPiece(PlayerColor c, bool& check) : m_color(c), m_inCheckCondition(check) {}
        virtual ~ChessPiece(){}

        virtual void move(int dCol, int dRow, ChessPiece* board[8][8]) = 0; //pure virtual function for abstract class
        virtual bool isInCheck(ChessPiece* board[NUM_TILE][NUM_TILE]) = 0;

        /*======================   WIN CONDITION  ============================*/
        /*only need to be implemented by king. but needs to be accessible through base.*/
        virtual bool kingScan(ChessPiece* board[NUM_TILE][NUM_TILE]) {return false;} 
        /*checks if index is within bounds. returns false if not. */
        bool isTileEnemyKing(int col, int row, ChessPiece* board[NUM_TILE][NUM_TILE]) const;
        /*returns type (empty, king or not king). No bounds checking*/
        PieceType isEnemyKing(ChessPiece const* piece) const;
                
        /*==========================   UTILITY  ==============================*/
        
        PlayerColor const& getColor() const { return m_color;}
        std::string getColorString() const;
        void setPosition(char col, char row);
        char const getCol() const { return char(m_col + 'A'); }
        char const getRow() const { return char(m_row + '1'); }
        char colChar(int const& col) const { return char(col + 'A'); } 
        char rowChar(int const& row) const { return char(row + '1'); }
        
        virtual std::string getType() const { return "base class"; }

        ChessPiece* getKing(ChessPiece* board[NUM_TILE][NUM_TILE]);
};
#endif