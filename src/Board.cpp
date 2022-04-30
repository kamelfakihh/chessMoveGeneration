#include <stdexcept>
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

Board::Board(std::string fen){

    this->clearPieces();
    this->setFEN(fen);
}

void Board::clearPieces(){

    this->whitePawns    = 0x0;
    this->whiteRooks    = 0x0;
    this->whiteKnights  = 0x0;
    this->whiteBishops  = 0x0;
    this->whiteQueens   = 0x0;
    this->whiteKing     = 0x0;
    this->blackPawns    = 0x0;
    this->blackRooks    = 0x0;
    this->blackKnights  = 0x0;
    this->blackBishops  = 0x0;
    this->blackQueens   = 0x0;
    this->blackKing     = 0x0;
    this->allWhitePieces= 0x0;
    this->allBlackPieces= 0x0;
    this->allPieces     = 0x0;    
}

void Board::setFEN(std::string afen){

    this->clearPieces();

    // extract piece placement information from the full fen
    std::string fen;
    size_t index = fen.find(" ");
    if(index > -1){
        fen = afen.substr(0, index);
    } else {
        fen = afen;
    }

    // files [A:H] are mapped to [0:7]    
    auto file{0};

    // ranks [1:8] are mapped to [0:7]
    auto rank{7};

    for( auto character : fen){

        switch (character)
        {
            case 'p':
                this->blackPawns = this->blackPawns | ((bitboard) 1) << (rank*8 + file);
                file += 1;
                break;
            case 'P':
                this->whitePawns = this->whitePawns | ((bitboard) 1) << (rank*8 + file);
                file += 1;
                break;
            case 'r':
                this->blackRooks = this->blackRooks | ((bitboard) 1) << (rank*8 + file);
                file += 1;
                break;
            case 'R':
                this->whiteRooks = this->whiteRooks | ((bitboard) 1) << (rank*8 + file);
                file += 1;
                break;
            case 'n':
                this->blackKnights = this->blackKnights | ((bitboard) 1) << (rank*8 + file);
                file += 1;
                break;
            case 'N':
                this->whiteKnights = this->whiteKnights | ((bitboard) 1) << (rank*8 + file);
                file += 1;
                break;
            case 'b':
                this->blackBishops = this->blackBishops | ((bitboard) 1) << (rank*8 + file);
                file += 1;
                break;
            case 'B':
                this->whiteBishops = this->whiteBishops | ((bitboard) 1) << (rank*8 + file);
                file += 1;
                break;
            case 'q':
                this->blackQueens = this->blackQueens | ((bitboard) 1) << (rank*8 + file);
                file += 1;
                break;
            case 'Q':
                this->whiteQueens = this->whiteQueens | ((bitboard) 1) << (rank*8 + file);
                file += 1;
                break;
            case 'k':
                this->blackKing = ((bitboard) 1) << (rank*8 + file);
                file += 1;
                break;
            case 'K':
                this->whiteKing = ((bitboard) 1) << (rank*8 + file);
                file += 1;
                break;                
            case '/':
                rank -= 1;
                file = 0;
                break;
            case '1': 
                file += 1; 
                break;
            case '2': 
                file += 2; 
                break;
            case '3': 
                file += 3; 
                break;
            case '4': 
                file += 4; 
                break;
            case '5': 
                file += 5; 
                break;
            case '6': 
                file += 6; 
                break;
            case '7': 
                file += 7; 
                break;
            case '8':
                break;            
            default : 
                throw std::runtime_error("invalid FEN string");
        }
    }

    this->allWhitePieces = this->whitePawns | this->whiteBishops | this->whiteKnights | this->whiteKnights | this->whiteRooks | this->whiteQueens;
    this->allBlackPieces = this->blackPawns | this->blackBishops | this->blackKnights | this->blackKnights | this->blackRooks | this->blackQueens;
    this->allPieces = this->allWhitePieces | this->allBlackPieces;
}

bitboard Board::kingPseudoLegalMoves(bitboard kingLocation, bitboard ownSide){

    /*
        checks if the king can move to positions 1-8:

        1 2 3       
        8 K 4
        7 6 5        

        for positions 1,8,7 and 3,4,5 the king can move to an illegal position when it belongs to the A or H file 
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

bitboard Board::wKingPseudoLegalMoves(){

    return this->kingPseudoLegalMoves(whiteKing, allWhitePieces);
}

bitboard Board::bKingPseudoLegalMoves(){

    return this->kingPseudoLegalMoves(blackKing, allBlackPieces);
}

bitboard Board::knightPseudoLegalMoves(bitboard knightLocation, bitboard ownSide){

    /*
        checks if the king can move to positions 1-8:

         2 3  
        1   4
          N  
        8   5
         7 6

        for positions 1,4,5,8 knight's position has two overflows, it can move to an illegal position when it belongs to the A/B or G/H files 
        and it is shifted in the Right or LEFT direction. The overflow in positions 2,3,6,7 is similar to the king's overflow. The knight is also
        cleared from the files that cause an overflow when shifting in a specific direction
    */

   bitboard knightClipFileA  = knightLocation & ClearFile[FILE_A];
   bitboard knightClipFileH  = knightLocation & ClearFile[FILE_H];
   bitboard knightClipFileAB = knightClipFileA & ClearFile[FILE_B];
   bitboard knightClipFileGH = knightClipFileH & ClearFile[FILE_G];

   bitboard spot1 = knightClipFileAB << 6;
   bitboard spot2 = knightClipFileA  << 15;
   bitboard spot3 = knightClipFileH  << 17;
   bitboard spot4 = knightClipFileGH << 10;
   bitboard spot5 = knightClipFileGH >> 6;
   bitboard spot6 = knightClipFileH  >> 15;
   bitboard spot7 = knightClipFileA  >> 17;
   bitboard spot8 = knightClipFileAB >> 10;   

   bitboard knightMoves = spot1 | spot2 | spot3 | spot4 | spot5 | spot6 | spot7 | spot8;
   bitboard knightValid = knightMoves & ~ownSide;

   return knightValid;
}

bitboard Board::wKnightPseudoLegalMoves(int knightIndex){
    bitboard knightLocation = this->whiteKnights & (((bitboard) 1) << knightIndex);
    return this->knightPseudoLegalMoves(knightLocation, this->allWhitePieces);
}

bitboard Board::bKnightPseudoLegalMoves(int knightIndex){
    bitboard knightLocation = this->blackKnights & (((bitboard) 1) << knightIndex);
    return this->knightPseudoLegalMoves(knightLocation, this->allBlackPieces);
}