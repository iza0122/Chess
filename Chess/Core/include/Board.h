#pragma once
#include "ChessDefinitons.h"
#include "Bitboard.h"
#include <iostream>

struct Move {
	ui from;
	ui to;
	Move(ui f, ui t) : from(f), to(t) {}
};

class Board {
private:
	u64 pieces[12] = { 0ULL };
	Piece occupied[64];
	bool turn;
public:
	Board(std::string fen);
	void move(const Piece &type,const Move &move);
	void printBoard();
};

