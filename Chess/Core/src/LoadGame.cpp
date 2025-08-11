#include "LoadGame.h"

FENLoader::FENLoader(const std::string& FEN)
{
	std::istringstream FENStream(FEN);
	std::string t_board, t_turn;
	FENStream >> t_board >> t_turn >> castling >> enPassant >> halfMove >> fullMove;
	std::istringstream boardStream(t_board);
	for (int i = 0; i < 8; i++) {
		getline(boardStream, board[i], '/');
	}
	if (t_turn == "w") whiteTurn = true;
	else whiteTurn = false;
}