#pragma once

enum Piece : uint8_t {
	WhitePawn, WhiteKnight, WhiteBishop, WhiteRook, WhiteQueen, WhiteKing,
	BlackPawn, BlackKnight, BlackBishop, BlackRook, BlackQueen, BlackKing,
	NoPiece
};

enum enumSquare {
	a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8
};
//Bitboard
using u64 = unsigned long long;
using ui = unsigned int;

#define C64(constantU64) constantU64##ULL

constexpr u64 AFile = C64(0x0101010101010101);
constexpr u64 HFile = C64(0x8080808080808080);
constexpr u64 Rank1 = C64(0x00000000000000ff);
constexpr u64 Rank8 = C64(0xff00000000000000);
constexpr u64 A1H8Diagonal = C64(0x8040201008040201);
constexpr u64 H1A8Antidiagonal = C64(0x0102040810204080);
constexpr u64 LightSquares = C64(0x55aa55aa55aa55aa);
constexpr u64 DarkSquares = C64(0xaa55aa55aa55aa55);
constexpr u64 Empty = C64(0x0000000000000000);
constexpr u64 Universe = C64(0xffffffffffffffff);