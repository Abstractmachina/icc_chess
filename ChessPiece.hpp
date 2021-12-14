/*-------------------------------------------------------
Taole Chen 211214
The ChessPiece class is the abstract base class for all pieces. 
opponentIsChecked() and isValidMove() are pure virtual functions which need
to be implemented by all child classes.

---------------------------------------------------------*/

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <iostream>
#include <string>

#include "errors.hpp"

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

    public:
        ChessPiece(PlayerColor c) : m_color(c) {}
        virtual ~ChessPiece(){}
        
        // =============    Main Functions   ====================================
        /* will differ for each piece, thus pure virtual.*/
        virtual bool opponentIsChecked(ChessPiece* board[NUM_TILE][NUM_TILE]) = 0;
        virtual bool isValidMove(int dCol, int dRow, ChessPiece* board[8][8]) = 0; 

        /*======================   WIN CONDITION  ============================*/
        /*only need to be implemented by king. but needs to be accessible through base.*/
        virtual bool kingScan(ChessPiece* board[NUM_TILE][NUM_TILE]) {return false;} 
        /*checks if selected tile holds enemy king.
        also checks if index is within bounds. returns false if not. */
        bool isTileEnemyKing(int col, int row, ChessPiece* board[NUM_TILE][NUM_TILE]) const;
        /*returns type (empty, king or not king)*/
        PieceType isEnemyKing(ChessPiece const* piece) const;
                
        /*==========================   UTILITY  ==============================*/
        
        PlayerColor const& getColor() const { return m_color;}
        std::string getColorString() const;
        void setPosition(char col, char row);
        void setPosition(int pos[2]) { m_col = pos[0]; m_row = pos[1]; }
        char const getCol() const { return char(m_col + 'A'); }
        char const getRow() const { return char(m_row + '1'); }
        int getC() const { return m_col; }
        int getR() const { return m_row; }
        char colChar(int const& col) const { return char(col + 'A'); } 
        char rowChar(int const& row) const { return char(row + '1'); }
        virtual std::string getType() const { return "base class"; }

};
#endif