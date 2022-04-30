#ifndef BOARD_H
#define BOARD_H

#include "Definitions.h"

class Board {

public:

    Board();
    
    // Return a bitboard containing all the places the white king can move or attack
    bitboard wKingPseudoLegalMoves();

    // Return a bitboard containing all the places the black king can move or attack
    bitboard bKingPseudoLegalMoves();

private:

    // Returns a bitboard containing all the places a king can move or attack
    bitboard kingPseudoLegalMoves(bitboard kingLocation, bitboard ownSide);    

    bitboard whitePawns, whiteKnights, whiteRooks, whiteBishops, whiteQueens, whiteKing;
    bitboard blackPawns, blackKnights, blackRooks, blackBishops, blackQueens, blackKing;
    bitboard allWhitePieces, allBlackPieces, allPieces;
};

#endif