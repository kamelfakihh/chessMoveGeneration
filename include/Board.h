#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <iostream>
#include "Definitions.h"

class Board {

    friend std::ostream &operator<<(std::ostream &os, const Board &b);

public:

    Board();
    Board(std::string fen);
    
    // Resets the board and sets its position to the one specified by FEN
    void setFEN(std::string fen);
    

    // Return bitboards containing all the places the white/black pieces can move or attack
    bitboard getPseudoLegalMoves(int index);

    bitboard wKingPseudoLegalMoves();    
    bitboard bKingPseudoLegalMoves();
    
    bitboard wKnightPseudoLegalMoves(int knightIndex);    
    bitboard bKnightPseudoLegalMoves(int knightIndex);
    
    bitboard wPawnPseudoLegalMoves(int pawnIndex);    
    bitboard bPawnPseudoLegalMoves(int pawnIndex);

    bitboard wBishopPseudoLegalMoves(int bishopIndex);
    bitboard bBishopPseudoLegalMoves(int bishopIndex);

    bitboard wRookPseudoLegalMoves(int rookIndex);
    bitboard bRookPseudoLegalMoves(int rookIndex);

    bitboard wQueenPseudoLegalMoves(int queenIndex);
    bitboard bQueenPseudoLegalMoves(int queenIndex);

private:

    // removes all pieces off the board
    void clearPieces();

    /*
        flips a board vertically around the central rank 
        rank 1 is mapped to rank 8, rank 2 is mapped to rank 7, ....

        @param x any bitboard
        @return bitboard x flipped vertically
    */
    bitboard flipVertical(bitboard x);

    /*
        flips a board horizontally around the central file 
        file A is mapped to file H, file B is mapped to file G, ....

        @param x any bitboard
        @return bitboard x flipped horizontally
    */
    bitboard flipHorizontal(bitboard x);

    /*
        reverses a board 
        square A1 is mapped to square G8 and vice versa

        @param x any bitboard
        @return bitboard x reversed
    */
    bitboard reverse(bitboard x);

    /*
        finds all diagonal attacks for a piece at a specified index         

        @param index piece square index
        @param occupied bitboard containing all occupied squares
        @return bitboard containing all target/attack sqaures
    */
    bitboard diagonalAttacks(bitboard occupied, int index);

    /*
        finds all antiDiagonal attacks for a piece at a specified index         

        @param index piece square index
        @param occupied bitboard containing all occupied squares
        @return bitboard containing all target/attack sqaures
    */
    bitboard antiDiagonalAttacks(bitboard occupied, int index);

    /*
        finds all file attacks for a piece at a specified index         

        @param index piece square index
        @param occupied bitboard containing all occupied squares
        @return bitboard containing all target/attack sqaures
    */
    bitboard fileAttacks(bitboard occupied, int index);

    /*
        finds all rank attacks for a piece at a specified index         

        @param index piece square index
        @param occupied bitboard containing all occupied squares
        @return bitboard containing all target/attack sqaures
    */
    bitboard rankAttacks(bitboard occupied, int index);

    // Returns a bitboard containing all the places a king can move or attack
    bitboard kingPseudoLegalMoves(bitboard kingLocation, bitboard ownSide);    

    // Returns a bitboard containing all the places a knight can move or attack
    bitboard knightPseudoLegalMoves(bitboard knightLocation, bitboard ownSide);

    bitboard whitePawns, whiteKnights, whiteRooks, whiteBishops, whiteQueens, whiteKing;
    bitboard blackPawns, blackKnights, blackRooks, blackBishops, blackQueens, blackKing;
    bitboard allWhitePieces, allBlackPieces, allPieces;
};

#endif