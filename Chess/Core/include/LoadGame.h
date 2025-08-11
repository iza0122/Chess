#pragma once
#include <sstream>
#include <string>
#include <iostream>
struct FENLoader
{
	std::string board[8];
	bool whiteTurn;
	std::string castling;
	std::string enPassant;
	int halfMove;
	int fullMove;
	FENLoader(const std::string& FEN);
};

