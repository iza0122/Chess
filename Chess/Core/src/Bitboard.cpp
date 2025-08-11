#include "Bitboard.h"

void setBit(u64& bitboard, ui index)
{
	bitboard |= C64(1) << index;
}

void toggleBit(u64& bitboard, ui index)
{
	bitboard ^= C64(1) << index;
}

void resetBit(u64& bitboard, ui index)
{
	bitboard &= ~(C64(1) << index);
}

bool testBit(const u64& bitboard, ui index)
{
	return (bitboard & (C64(1) << index));
}

u64 upperBits(ui index)
{
	return (C64(~1) << index);
}

u64 lowerBits(ui index)
{
	return ((C64(1) << index) - 1);
}
