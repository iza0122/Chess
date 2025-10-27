#pragma once
#include "ChessDefinitons.h"
#include "Bitboard.h"
const std::vector<u64> knightAttackTable();

const std::array<std::vector<u64>, 2> pawnAttackTable();

const std::vector<u64> kingAttackTable();

namespace AttackTable{
    extern std::array<std::vector<u64>, 2> pawnAttack;
    extern std::vector<u64> kingAttack;
    extern std::vector<u64> knightAttack;
    extern std::vector<std::vector<u64>> rookAttack;
    extern std::vector<std::vector<u64>> bishopAttack;

    void initAllAttackTable();
}