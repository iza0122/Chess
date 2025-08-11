#include "Board.h"
#include <sstream>
//Starting FEN rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

Board::Board(std::string fen)
{
    for (int i = 0; i < 64; i++) {
        occupied[i] = NoPiece;
    }
   
}

void Board::move(const Piece& type, const Move& move)
{
    u64 fromBB = C64(1) << move.from;
    u64 toBB = C64(1) << move.to;
    u64 fromToBB = fromBB ^ toBB;

    pieces[type] ^= fromToBB;
    if (occupied[move.to] != NoPiece) {
        pieces[occupied[move.to]] ^= toBB;
    }

    occupied[move.from] = NoPiece;
    occupied[move.to] = type;
}

void Board::printBoard()
{
}
