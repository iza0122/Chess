#include <Board.h>
#include "LoadGame.h"
#include <iostream>

int main() {
	Board game("4r3/3q3p/1Q6/p4p2/2k1bP2/P6P/1P4P1/4R1K1 w - - 0 36");
	game.printBoard();
	int n;
	Move a(e1, c1), b(e1, e4);

	while (1) {
		std::cout << "enter:";
		std::cin >> n;
		switch (n)
		{
		case 1:
			game.move(WhiteRook, a);
			game.printBoard();
			system("pause");
		case 2:
			game.move(WhiteRook, b);
			game.printBoard();
			system("pause");
		default:
			break;
		}
	}
	system("pause");
}