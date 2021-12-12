chess: ChessMain.o ChessBoard.o ChessPiece_Impl.o ChessPiece.o
	g++ -Wall ChessMain.o ChessBoard.o ChessPiece_Impl.o ChessPiece.o -o chess

ChessMain.o: ChessMain.cpp ChessBoard.hpp ChessPiece_Impl.hpp ChessPiece.hpp errors.hpp
	g++ -Wall -g -c ChessMain.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.hpp
	g++ -Wall -g -c ChessBoard.cpp ChessBoard.hpp

ChessPiece_Impl.o: ChessPiece_Impl.cpp ChessPiece_Impl.hpp
	g++ -Wall -g -c ChessPiece_Impl.cpp ChessPiece_Impl.hpp

ChessPiece.o: ChessPiece.hpp ChessPiece.hpp
	g++ -Wall -g -c ChessPiece.cpp ChessPiece.hpp

clean:
	rm -f *.o chess