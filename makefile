chess: ChessMain.o ChessBoard.o ChessPiece.o Bishop.o King.o Knight.o Pawn.o Queen.o Rook.o
	g++ -Wall ChessMain.o ChessBoard.o ChessPiece.o Bishop.o King.o Knight.o Pawn.o Queen.o Rook.o -o chess

ChessMain.o: ChessMain.cpp
	g++ -Wall -g -c ChessMain.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.h
	g++ -Wall -g -c ChessBoard.cpp ChessBoard.h

ChessPiece.o: ChessPiece.cpp ChessPiece.hpp
	g++ -Wall -g -c ChessPiece.cpp ChessPiece.hpp

Bishop.o: Bishop.cpp Bishop.hpp
	g++ -Wall -g -c Bishop.cpp Bishop.hpp

King.o: King.cpp King.hpp
	g++ -Wall -g -c King.cpp King.hpp

Knight.o: Knight.cpp Knight.hpp
	g++ -Wall -g -c Knight.cpp Knight.hpp

Pawn.o: Pawn.cpp Pawn.hpp
	g++ -Wall -g -c Pawn.cpp Pawn.hpp

Queen.o: Queen.cpp Queen.hpp
	g++ -Wall -g -c Queen.cpp Queen.hpp

Rook.o: Rook.cpp Rook.hpp
	g++ -Wall -g -c Rook.cpp Rook.hpp

clean:
	rm -f *.o *.gch chess