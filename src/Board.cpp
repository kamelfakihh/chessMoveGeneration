#include "Definitions.h"
#include "Board.h"

Board::Board(){

    this->whitePawns    = whitePawnsInitial;
    this->whiteRooks    = whiteRooksInitial;
    this->whiteKnights  = whiteKnightsInitial;
    this->whiteBishops  = whiteBishopsInitial;
    this->whiteQueens   = whiteQueensInitial;
    this->whiteKing     = whiteKingInitial;
    this->blackPawns    = blackPawnsInitial;
    this->blackRooks    = blackRooksInitial;
    this->blackKnights  = blackKnightsInitial;
    this->blackBishops  = blackBishopsInitial;
    this->blackQueens   = blackQueensInitial;
    this->blackKing     = blackKingInitial;
    this->allWhitePieces= allWhitePiecesInitial;
    this->allBlackPieces= allBlackPiecesInitial;
    this->allPieces     = allPiecesInitial;
}

bitboard Board::kingPseudoLegalMoves(bitboard kingLocation, bitboard ownSide){

    /*
        checks if the king can move to positions 1-8:

        1 2 3       
        8 K 4
        7 6 5        

        for positions 1,8,7 and 3,4,5 the king can move to an illegal position when it belongs to the A or F file 
        and it is shifted in the Right or LEFT direction (ex: a king on the A file will move to the H file when shifted right),
        to avoid this issue the king is cleared from these files when shifted in those directions
    */

   bitboard kingClipFileA = kingLocation & ClearFile[FILE_A];
   bitboard kingClipFileH = kingLocation & ClearFile[FILE_H];

   bitboard spot1 = kingClipFileA << 7;
   bitboard spot2 = kingLocation << 8;
   bitboard spot3 = kingClipFileH << 9;
   bitboard spot4 = kingClipFileH << 1;
   bitboard spot5 = kingClipFileH >> 7;
   bitboard spot6 = kingLocation >> 8;
   bitboard spot7 = kingClipFileA >> 9;
   bitboard spot8 = kingClipFileA >> 1;

   bitboard kingMoves = spot1 | spot2 | spot3 | spot4 | spot5 | spot6 | spot7 | spot8;

   // ownSide is a bitboard containing all pieces that belong to the same side as the king
   // same result can be achieved by doing a logical OR between king moving spots and the bitboard of all valid moves
   bitboard kingValid = kingMoves & ~ownSide;

   return kingValid;
}