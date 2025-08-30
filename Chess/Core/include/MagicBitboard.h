#pragma once
#include "ChessDefinitons.h"
u64 rookBlockerMask(ui index);

u64 rookMoveBoard(ui index, u64 blockerBoard);

u64 bishopBlockerMask(ui index);

u64 bishopMoveBoard(ui index, u64 blockerBoard);

std::vector<u64> blockerBoard(const u64 &blockerMask);