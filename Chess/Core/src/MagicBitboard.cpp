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

constexpr int rookShift[64] = {
	52, 53, 53, 53, 53, 53, 53, 52, 
	53, 54, 54, 54, 54, 54, 54, 53, 
	53, 54, 54, 54, 54, 54, 54, 53, 
	53, 54, 54, 54, 54, 54, 54, 53, 
	53, 54, 54, 54, 54, 54, 54, 53, 
	53, 54, 54, 54, 54, 54, 54, 53, 
	53, 54, 54, 54, 54, 54, 54, 53, 
	52, 53, 53, 53, 53, 53, 53, 52
};
constexpr u64 rookMask[64] = {
	0x101010101017e, 0x202020202027c, 0x404040404047a, 0x8080808080876, 0x1010101010106e, 0x2020202020205e, 0x4040404040403e, 0x8080808080807e, 
	0x1010101017e00, 0x2020202027c00, 0x4040404047a00, 0x8080808087600, 0x10101010106e00, 0x20202020205e00, 0x40404040403e00, 0x80808080807e00,
	0x10101017e0100, 0x20202027c0200, 0x40404047a0400, 0x8080808760800, 0x101010106e1000, 0x202020205e2000, 0x404040403e4000, 0x808080807e8000,
	0x101017e010100, 0x202027c020200, 0x404047a040400, 0x8080876080800, 0x1010106e101000, 0x2020205e202000, 0x4040403e404000, 0x8080807e808000,
	0x1017e01010100, 0x2027c02020200, 0x4047a04040400, 0x8087608080800, 0x10106e10101000, 0x20205e20202000, 0x40403e40404000, 0x80807e80808000,
	0x17e0101010100, 0x27c0202020200, 0x47a0404040400, 0x8760808080800, 0x106e1010101000, 0x205e2020202000, 0x403e4040404000, 0x807e8080808000,
	0x7e010101010100, 0x7c020202020200, 0x7a040404040400, 0x76080808080800, 0x6e101010101000, 0x5e202020202000, 0x3e404040404000, 0x7e808080808000,
	0x7e01010101010100, 0x7c02020202020200, 0x7a04040404040400, 0x7608080808080800, 0x6e10101010101000, 0x5e20202020202000, 0x3e40404040404000, 0x7e80808080808000
};

constexpr u64 rookMagic[64] = {
    0x2380004000201080, 0x2040100020004001, 0x180086002100080, 0x4080048008021000, 0xa00086004100200, 0x80018004004200, 0x400640810030082, 0x4280014100102080,
    0x80a002600450080, 0x4005004004802100, 0x81004104102000, 0x3441000921021000, 0x2002010460008, 0x806001004020008, 0x3541002100140200, 0x25000260810002,
    0x800040042002d2, 0x10104000442000, 0x50028010802000, 0xf0008028001080, 0x8008008040080, 0x10100080c0002, 0xa00040002010890, 0xa42020000670084,
    0xc80084040002000, 0x200640005006, 0x51410100200091, 0x101c900201000, 0x21080100050010, 0x242001200190410, 0x1a1400081011, 0x1204200140091,
    0x1000400020800088, 0x1100442000401000, 0x204102001004100, 0x4006102202004008, 0x28010400800881, 0x80100040100081e, 0x101100e24000148,
    0x44004412000981, 0x480094220084000, 0x10200050024002, 0x61002000110042, 0x5005001890021, 0x8010500090010, 0x9000864010002, 0x501100142440008,
    0x12a040040820001, 0xa44408209002200, 0x1010084000200040, 0x208012004200, 0x2243001001900, 0x1022000810042200, 0x1c22000830040600, 0x800100508220400, 
    0x1000a44820300, 0x81430110800021, 0x80401100260082, 0x2001010830c1, 0x200210049045001, 0x42060088209c3042, 0x700a604001811, 0x80201100084, 0x168004a21040086
};

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

bool checkMagic(ui square, u64 magic){
    int size = 1ULL << (64 - rookShift[square]);
    std::vector<u64> rookAttack(size, 0);
    std::vector<u64> occupancy = blockerBoard(rookMask[square]);
    int i = 0;
    while(true){
        if (i == size) break;
        u64 index = ((occupancy[i] * magic) >> rookShift[square]);
        if(rookAttack[index] != 0){
            return false;
        }
        rookAttack[index] = 1;
        i++;
    }
    return true;
}


int main(){
    // std::cout << findRookMagic(7) << "\n";
    for (int i = 0; i < 64; i++){
        // std::cout << "0x" << std::hex << findRookMagic(i) <<", ";
        std::cout << i << " ";
        if(!checkMagic(i, rookMagic[i])) std::cout << "Collision\n";
    }
    system("pause");
    return 0;
}