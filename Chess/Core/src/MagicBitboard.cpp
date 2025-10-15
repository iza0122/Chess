#include "MagicBitboard.h"
#include "Bitboard.h"
#include <random>
#include <iomanip>
#include <iostream>

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

/// @brief all of the squares that can be occupied and block piece from moving further
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

uint64_t random_uint64() {
  uint64_t u1, u2, u3, u4;
  u1 = (uint64_t)(rand()) & 0xFFFF; u2 = (uint64_t)(rand()) & 0xFFFF;
  u3 = (uint64_t)(rand()) & 0xFFFF; u4 = (uint64_t)(rand()) & 0xFFFF;
  return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}

uint64_t random_uint64_fewbits() {
  return random_uint64() & random_uint64() & random_uint64();
}

u64 findRookMagic(ui square){
    u64 magic = random_uint64_fewbits();
    int size = 1ULL << (64 - rookShift[square]);
    std::vector<u64> rookAttack(size, 0);
    std::vector<u64> occupancy = blockerBoard(rookMask[square]);
    int i = 0;
    while(true){
        if (i == size) break;
        u64 index = ((occupancy[i] * magic) >> rookShift[square]);
        if(rookAttack[index] != 0){
            std::fill(rookAttack.begin(), rookAttack.end(), 0);
            magic = random_uint64_fewbits();
            i = 0;
            continue;
        }
        rookAttack[index] = 1;
        i++;
    }
    return magic;
}

u64 findBishopMagic(ui square){
    u64 magic = random_uint64_fewbits();
    int size = 1ULL << (64 - bishopShift[square]);
    std::vector<u64> bishopAttack(size, 0);
    std::vector<u64> occupancy = blockerBoard(bishopMask[square]);
    int i = 0;
    while(true){
        if (i == size) break;
        u64 index = ((occupancy[i] * magic) >> bishopShift[square]);
        if(bishopAttack[index] != 0){
            std::fill(bishopAttack.begin(), bishopAttack.end(), 0);
            magic = random_uint64_fewbits();
            i = 0;
            continue;
        }
        bishopAttack[index] = 1;
        i++;
    }
    return magic;
}

u64 getRookAttack(int square, u64 occupancy) {
    u64 attacks = 0ULL;
    int rank = square / 8;
    int file = square % 8;

    // Đi lên (north)
    for (int r = rank + 1; r <= 7; r++) {
        int sq = r * 8 + file;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break; // dừng khi gặp chặn
    }

    // Đi xuống (south)
    for (int r = rank - 1; r >= 0; r--) {
        int sq = r * 8 + file;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break;
    }

    // Đi phải (east)
    for (int f = file + 1; f <= 7; f++) {
        int sq = rank * 8 + f;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break;
    }

    // Đi trái (west)
    for (int f = file - 1; f >= 0; f--) {
        int sq = rank * 8 + f;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break;
    }

    return attacks;
}

u64 getBishopAttack(int square, u64 occupancy) {
    u64 attacks = 0ULL;
    int rank = square / 8;
    int file = square % 8;

    // Đường chéo lên phải (NE)
    for (int r = rank + 1, f = file + 1; r <= 7 && f <= 7; r++, f++) {
        int sq = r * 8 + f;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break;
    }

    // Đường chéo lên trái (NW)
    for (int r = rank + 1, f = file - 1; r <= 7 && f >= 0; r++, f--) {
        int sq = r * 8 + f;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break;
    }

    // Đường chéo xuống phải (SE)
    for (int r = rank - 1, f = file + 1; r >= 0 && f <= 7; r--, f++) {
        int sq = r * 8 + f;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break;
    }

    // Đường chéo xuống trái (SW)
    for (int r = rank - 1, f = file - 1; r >= 0 && f >= 0; r--, f--) {
        int sq = r * 8 + f;
        attacks |= (1ULL << sq);
        if (occupancy & (1ULL << sq)) break;
    }

    return attacks;
}