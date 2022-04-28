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