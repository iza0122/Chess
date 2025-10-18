#include "AttackLookup.h"
#include "MagicBitboard.h"
#include <array>

vector2D knightDirection[8] = {
    {2, 1},
    {1, 2},
    {-1, 2},
    {-2, 1},
    {-2, -1},
    {-1, -2},
    {1, -2},
    {2, -1}};


vector2D whitePawnDir[2] = { 
    {-1, 1}, 
    {1, 1} 
};
vector2D blackPawnDir[2] = { 
    {-1, -1}, 
    {1, -1} 
};

vector2D pawnMove = {0, 1};

vector2D pawnFirstMove = {0, 2};

vector2D kingDirection[8] = {
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 1},
    {-1, 0},
    {-1, -1},
    {0, -1},
    {1, -1}};

/**
 * @brief Generate a lookup table of knight attack bitboards for all 64 squares.
 *
 * @return std::vector<u64> A vector of length 64 where element [s] is a bitboard
 *                           with bits set for every square a knight on square s
 *                           can legally move to (board-edge checked).
 */
const std::vector<u64> kinghtAttackTable()
{
    std::vector<u64> KnightAttack(64);
    for (int i = 0; i < 64; i++)
    {
        vector2D currentSquare(i % 8, i / 8);
        u64 currentBitboard = 0;
        for (int j = 0; j < 8; j++)
        {
            vector2D sum = currentSquare + knightDirection[j];
            if (sum.x >= 0 && sum.y >= 0 && sum.x < 8 && sum.y < 8)
            {
                setBit(currentBitboard, sum.x + 8 * sum.y);
            }
        }
        KnightAttack[i] = currentBitboard;
    }
    return KnightAttack;
}

/**
 * @brief Generates a lookup table for both white and black pawns.
 * 
 * This function creates a 2D array where:
 * - The first element PawnAttack[0][square] corresponds to the attack bitboards for white pawns.
 * - The second element PawnAttack[1][square] corresponds to the attack bitboards for black pawns.
 * 
 * @return A std::array containing two std::vector<u64>, where each vector represents the attack bitboards
 *         for all 64 squares on the chessboard for white and black pawns respectively.
 */
const std::array<std::vector<u64>, 2> pawnAttackTable()
{
    std::array<std::vector<u64>, 2> PawnAttack = {
        std::vector<u64>(64, 0ULL),
        std::vector<u64>(64, 0ULL)
    };

    for (int i = 0; i < 64; i++)
    {
        vector2D current(i % 8, i / 8);

        // WHITE
        for (auto& d : whitePawnDir)
        {
            vector2D sum = current + d;
            if (sum.x >= 0 && sum.y >= 0 && sum.x < 8 && sum.y < 8)
                setBit(PawnAttack[0][i], sum.x + 8 * sum.y);
        }

        // BLACK
        for (auto& d : blackPawnDir)
        {
            vector2D sum = current + d;
            if (sum.x >= 0 && sum.y >= 0 && sum.x < 8 && sum.y < 8)
                setBit(PawnAttack[1][i], sum.x + 8 * sum.y);
        }
    }

    return PawnAttack;
}

/**
 * @brief Generate king attack bitboards for all 64 squares.
 * @return std::vector<u64> A vector of 64 u64 bitboards where each element
 *         encodes the squares attacked by a king from the corresponding square index (0-63).
 */
const std::vector<u64> kingAttackTable()
{
    std::vector<u64> KingAttack(64);
    for (int i = 0; i < 64; i++)
    {
        vector2D currentSquare(i % 8, i / 8);
        u64 currentBitboard = 0;
        for (int j = 0; j < 8; j++)
        {
            vector2D sum = currentSquare + kingDirection[j];
            if (sum.x >= 0 && sum.y >= 0 && sum.x < 8 && sum.y < 8)
            {
                setBit(currentBitboard, sum.x + 8 * sum.y);
            }
        }
        KingAttack[i] = currentBitboard;
    }
    return KingAttack;
}
