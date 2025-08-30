#include "MagicBitboard.h"
#include "Bitboard.h"

vector2D bishopDirection[4] = {
    {1,1},
    {-1,1},
    {1,-1},
    {-1,-1}
};


/// @brief all of the squares that can be occupied and block piece from moving further
u64 rookBlockerMask(ui index)
{
    u64 blockerMask = C64(0);
    int row = index / 8;
    int col = index % 8;
    for (int i = 1; i < 7 - row; i++){
        setBit(blockerMask, index + i * 8);
    }
    for (int i = row - 1; i > 0; i--){
        setBit(blockerMask, index - i * 8);
    }
    for (int i = 1; i < 7 - col; i++){
        setBit(blockerMask, index + i);
    }
    for (int i = col - 1; i > 0; i--){
        setBit(blockerMask, index - i);
    }
    return blockerMask;
}

/// @brief generate all possible occupied pieces from blocker mask
std::vector<u64> blockerBoard(const u64 &blockerMask)
{
    std::vector<int> squares;
    std::vector<u64> result;
    for (int sq = 0; sq < 64; sq++) {
        if (blockerMask & (1ULL << sq)) squares.push_back(sq);
    }
    int n = squares.size();
    int subsets = 1 << n;
    for (int index = 0; index < subsets; index++) {
        u64 blockers = 0ULL;
        for (int i = 0; i < n; i++) {
            if (index & (1 << i)) {
                blockers |= (1ULL << squares[i]);
            }
        }
        result.push_back(blockers);
    }
    return result;
}

u64 bishopBlockerMask(ui index)
{
    u64 blockerMask = C64(0);
    vector2D currentPosition(index % 8, index / 8);
    for (int i = 1; i < 7; i++){
        for (int j = 0; j < 4; j++){
            vector2D updatedDirection(bishopDirection[j].x * i, bishopDirection[j].y * i);
            vector2D sum = currentPosition + updatedDirection;
            if (sum.x > 0 && sum.y > 0 && sum.x < 7 && sum.y < 7){
                setBit(blockerMask, sum.x + 8*sum.y);
            }
        }
    }
    return blockerMask;
}




