#include "Board.h"
//Starting FEN rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

Board::Board(std::string fen)
{
    for (int i = 0; i < 64; i++) {
        occupied[i] = NoPiece;
    }
    FENLoader t_FEN(fen);
    int index = 0;
    for (int i = 7; i >= 0; i--) {
        for (char x : t_FEN.board[i]) {
            if (isdigit(x)) {
                index += x - '0';
                continue;
            }
            bool isWhite = isupper(x);
            x = tolower(x);

            Piece p;
            switch (x) {
            case 'p': p = isWhite ? WhitePawn : BlackPawn;   break;
            case 'b': p = isWhite ? WhiteBishop : BlackBishop; break;
            case 'n': p = isWhite ? WhiteKnight : BlackKnight; break;
            case 'r': p = isWhite ? WhiteRook : BlackRook;   break;
            case 'q': p = isWhite ? WhiteQueen : BlackQueen;  break;
            case 'k': p = isWhite ? WhiteKing : BlackKing;   break;
            default:  p = NoPiece; break;
            }

            if (p != NoPiece) {
                setBit(pieces[p], index);
                occupied[index] = p;
            }

            index++;
        }
    }
}

void Board::move(const Piece& type, const Move& move)
{
    u64 fromBB = C64(1) << move.from;
    u64 toBB = C64(1) << move.to;
    u64 fromToBB = fromBB ^ toBB;

    pieces[type] ^= fromToBB;
    if (occupied[move.to] != NoPiece) {
        pieces[occupied[move.to]] ^= toBB;
    }

    occupied[move.from] = NoPiece;
    occupied[move.to] = type;
}

void Board::printBoard()
{
    for (int rank = 7; rank >= 0; rank--) { 
        std::cout << rank + 1 << " ";
        for (int file = 0; file < 8; file++) {
            int index = rank * 8 + file; 
            char c = '.';

            for (int p = 0; p < 12; p++) {
                if ((pieces[p] >> index) & 1ULL) {
                    switch (p) {
                    case WhitePawn:   c = 'P'; break;
                    case WhiteBishop: c = 'B'; break;
                    case WhiteKnight: c = 'N'; break;
                    case WhiteRook:   c = 'R'; break;
                    case WhiteQueen:  c = 'Q'; break;
                    case WhiteKing:   c = 'K'; break;
                    case BlackPawn:   c = 'p'; break;
                    case BlackBishop: c = 'b'; break;
                    case BlackKnight: c = 'n'; break;
                    case BlackRook:   c = 'r'; break;
                    case BlackQueen:  c = 'q'; break;
                    case BlackKing:   c = 'k'; break;
                    }
                    break;
                }
            }
            std::cout << c << " ";
        }
        std::cout << "\n";
    }
    std::cout << "  a b c d e f g h\n";
}
