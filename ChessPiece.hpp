#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <iostream>
#include <string>

enum PlayerColor{WHITE, BLACK};

//abstract base class.
class ChessPiece {
    protected:
        /*position will be stored as integers internally for ease of calc. 
        displayed as chars externally for readability*/
        static int const NUM_TILE = 8;
        int m_col, m_row; //row = 'A'-'H', col = '1'-'8'
        PlayerColor m_color;

        void updatePosition(int const& destCol, int const& destRow, ChessPiece* board[8][8]);
        void captureEnemy(int const& destCol, int const& destRow, ChessPiece* board[8][8]);
        void commentSuccessfulMove(int const& dCol, int const& dRow) const;
        void commentSucessfulCapture(ChessPiece* capture) const;
    public:
        ChessPiece() {}
        ChessPiece(PlayerColor c) : m_color(c) {}

        virtual void move(int dCol, int dRow, ChessPiece* tiles[8][8]) = 0; //pure virtual function for abstract class
        virtual bool isInCheck(ChessPiece* board[NUM_TILE][NUM_TILE]) = 0;
                
        char* getPosition() const;
        void setPosition(char col, char row);
        
        PlayerColor const& getColor() const { return m_color;}
        std::string getColorString() const;
        void setColor(PlayerColor c) { m_color = c; }
        char const& getCol() const { return char(m_col + 'A'); }
        char const& getRow() const { return char(m_row + '1'); }
        char colChar(int const& col) const { return char(col + 'A'); } 
        char rowChar(int const& row) const { return char(row + '1'); }
        
        virtual std::string getType() const { return "base class"; }
};
#endif