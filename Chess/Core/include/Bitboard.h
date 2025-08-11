#pragma once
#include "ChessDefinitons.h"
#include <bitset>

void setBit(u64 &bitboard, ui index);
void toggleBit(u64 &bitboard, ui index);
void resetBit(u64 &bitboard, ui index);
bool testBit(const u64 &bitboard, ui index);


u64 upperBits(ui index);
u64 lowerBits(ui index);