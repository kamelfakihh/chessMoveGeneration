#ifndef BOARD_H
#define BOARD_H

#include <string>
#include "Definitions.h"

class Board {

public:

    Board();
    Board(std::string fen);
    
    // Resets the board and sets its position to the one specified by FEN
    void setFEN(std::string fen);

    // Return a bitboard containing all the places the white/black king can move or attack
    bitboard wKingPseudoLegalMoves();    
    bitboard bKingPseudoLegalMoves();

    // Return a bitboard containing all the places a white/black knight can move or attack
    bitboard wKnightPseudoLegalMoves(int knightIndex);    
    bitboard bKnightPseudoLegalMoves(int knightIndex);

    // Return a bitboard containing all the places a white/black pawn can move or attack
    bitboard wPawnPseudoLegalMoves(int pawnIndex);    
    bitboard bPawnPseudoLegalMoves(int pawnIndex);

private:

    // removes all pieces off the board
    void clearPieces();

    // Returns a bitboard containing all the places a king can move or attack
    bitboard kingPseudoLegalMoves(bitboard kingLocation, bitboard ownSide);    

    // Returns a bitboard containing all the places a knight can move or attack
    bitboard knightPseudoLegalMoves(bitboard knightLocation, bitboard ownSide);

    bitboard whitePawns, whiteKnights, whiteRooks, whiteBishops, whiteQueens, whiteKing;
    bitboard blackPawns, blackKnights, blackRooks, blackBishops, blackQueens, blackKing;
    bitboard allWhitePieces, allBlackPieces, allPieces;
};

#endif