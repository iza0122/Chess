#include "MoveGeneration.h"

vector2D knightDirection[8] = {
    {2, 1},
    {1, 2},
    {-1, 2},
    {-2, 1},
    {-2, -1},
    {-1, -2},
    {1, -2},
    {2, -1}
};

std::vector<u64> createKinghtAttack(){
    std::vector<u64> KnightAttack(64);
    for(int i = 0; i < 64; i++){
        vector2D currentSquare(i % 8, i / 8);
        u64 currentBitboard = 0;
        for (int j = 0; j < 8; j++){
            vector2D sum = currentSquare + knightDirection[j];
            if (sum.x >= 0 && sum.y >= 0 && sum.x < 8 && sum.y < 8){
                setBit(currentBitboard, sum.x + 8*sum.y);
            }
        }
        KnightAttack[i] = currentBitboard;
    }
    return KnightAttack;
}
