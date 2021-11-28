chess: main.o ChessBoard.o ChessPiece_Impl.o ChessPiece.o
	g++ -Wall main.o ChessBoard.o ChessPiece_Impl.o ChessPiece.o

main.o: main.cpp ChessBoard.h ChessPiece_Impl.h ChessPiece.h
	g++ -Wall -g -c main.cpp

ChessBoard.o: ChessBoard.cpp ChessBoard.hpp
	g++ -Wall -g -c ChessBoard.cpp ChessBoard.hpp

ChessPiece_Impl.o: ChessPiece_Impl.cpp ChessPiece_Impl.hpp
	g++ -Wall -g -c ChessPiece_Impl.cpp ChessPiece_Impl.hpp

ChessPiece.o: ChessPiece.hpp ChessPiece.hpp
	g++ -Wall -g -c ChessPiece.cpp ChessPiece.hpp

clean:
	rm -f *.o chess