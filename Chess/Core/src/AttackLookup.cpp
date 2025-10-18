#include "AttackLookup.h"
#include "MagicBitboard.h"

vector2D knightDirection[8] = {
    {2, 1},
    {1, 2},
    {-1, 2},
    {-2, 1},
    {-2, -1},
    {-1, -2},
    {1, -2},
    {2, -1}};

vector2D pawnDirection[2] = {
    {1, 1},
    {-1, 1}};

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
 * @brief Generate pawn attack bitboards for each square.
 * @return std::vector<u64> A vector of 64 u64 attack masks. Element [sq] is the
 *         64-bit mask of squares attacked by a pawn from square sq (bit set = attacked).
 */
const std::vector<u64> pawnAttackTable()
{
    std::vector<u64> PawnAttack(64);
    for (int i = 0; i < 56; i++)
    {
        vector2D currentSquare(i % 8, i / 8);
        u64 currentBitboard = 0;
        for (int j = 0; j < 2; j++)
        {
            vector2D sum = currentSquare + pawnDirection[j];
            if (sum.x >= 0 && sum.y >= 0 && sum.x < 8 && sum.y < 8)
            {
                setBit(currentBitboard, sum.x + 8 * sum.y);
            }
        }
        PawnAttack[i] = currentBitboard;
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
