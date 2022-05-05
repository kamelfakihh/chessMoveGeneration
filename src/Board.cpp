#include <iostream>
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

bitboard Board::getPseudoLegalMoves(int pieceIndex){

    if((this->whitePawns & (((bitboard) 1) << pieceIndex )) != 0){
        return this->wPawnPseudoLegalMoves(pieceIndex);

    } else if((this->blackPawns & (((bitboard) 1) << pieceIndex )) != 0){
        return this->bPawnPseudoLegalMoves(pieceIndex);

    } else if((this->whiteKnights & (((bitboard) 1) << pieceIndex )) != 0){
        return this->wKnightPseudoLegalMoves(pieceIndex);

    } else if((this->blackKnights & (((bitboard) 1) << pieceIndex )) != 0){
        return this->bKnightPseudoLegalMoves(pieceIndex);

    } else if((this->whiteBishops & (((bitboard) 1) << pieceIndex )) != 0){
        return this->wBishopPseudoLegalMoves(pieceIndex);

    } else if((this->blackBishops & (((bitboard) 1) << pieceIndex )) != 0){
        return this->bBishopPseudoLegalMoves(pieceIndex);

    } else if((this->whiteRooks & (((bitboard) 1) << pieceIndex )) != 0){
        return this->wRookPseudoLegalMoves(pieceIndex);

    } else if((this->blackRooks & (((bitboard) 1) << pieceIndex )) != 0){
        return this->bRookPseudoLegalMoves(pieceIndex);

    } else if((this->whiteQueens & (((bitboard) 1) << pieceIndex )) != 0){
        return this->wQueenPseudoLegalMoves(pieceIndex);

    } else if((this->blackQueens & (((bitboard) 1) << pieceIndex )) != 0){
        return this->bQueenPseudoLegalMoves(pieceIndex);

    }else if((this->whiteKing & (((bitboard) 1) << pieceIndex )) != 0){
        return this->wKingPseudoLegalMoves();

    } else if((this->blackKing & (((bitboard) 1) << pieceIndex )) != 0){
        return this->bKingPseudoLegalMoves();        
    }else{
        return 0x0;
    }    
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
        checks if the knight can move to positions 1-8:

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

bitboard Board::wPawnPseudoLegalMoves(int pawnIndex){
    
    bitboard pawnLocation = this->whitePawns & (((bitboard) 1) << pawnIndex);
    bitboard emptySquares = ~this->allPieces;

    // check if pawn can be pushed one square foreward
    bitboard singlePushTarget = (pawnLocation << 8) & emptySquares;

    // if the pawn came from rank2, check if it can be pushed one more square (double push)
    bitboard doublePushTarget = (singlePushTarget << 8) & MaskRank[RANK_4] & emptySquares;

    // check left side attack (avoiding the underflow for pawn on file A)    
    bitboard leftAttack = (pawnLocation & ClearFile[FILE_A]) << 7;

    // check right side attack (avoiding the overflow for pawn on file H)    
    bitboard rightAttack = (pawnLocation & ClearFile[FILE_H]) << 9;

    bitboard validAttacks = (leftAttack | rightAttack) & this->allBlackPieces;

    return validAttacks | singlePushTarget | doublePushTarget;
}   

bitboard Board::bPawnPseudoLegalMoves(int pawnIndex){

    bitboard pawnLocation = this->blackPawns & (((bitboard) 1) << pawnIndex);
    bitboard emptySquares = ~this->allPieces;

    // check if pawn can be pushed one square foreward
    bitboard singlePushTarget = (pawnLocation >> 8) & emptySquares;

    // if the pawn came from rank2, check if it can be pushed one more square (double push)
    bitboard doublePushTarget = (singlePushTarget >> 8) & MaskRank[RANK_4] & emptySquares;

    // check left side attack (avoiding the underflow for pawn on file A)    
    bitboard leftAttack = (pawnLocation & ClearFile[FILE_A]) >> 9;

    // check right side attack (avoiding the overflow for pawn on file H)    
    bitboard rightAttack = (pawnLocation & ClearFile[FILE_A]) << 7;

    bitboard validAttacks = (leftAttack | rightAttack) & this->allWhitePieces;

    return validAttacks | singlePushTarget | doublePushTarget;
}

bitboard Board::flipVertical(bitboard x){
    return  (( x << 56 )                     |
            (( x << 40 ) & MaskRank[RANK_7]) |
            (( x << 24 ) & MaskRank[RANK_6]) |
            (( x <<  8 ) & MaskRank[RANK_5]) |
            (( x >>  8 ) & MaskRank[RANK_4]) |
            (( x >> 24 ) & MaskRank[RANK_3]) |
            (( x >> 40 ) & MaskRank[RANK_2]) |
            (  x >> 56 ));
}

bitboard Board::flipHorizontal(bitboard x){    
    bitboard k1 = 0x5555555555555555;
    bitboard k2 = 0x3333333333333333;
    bitboard k4 = 0x0f0f0f0f0f0f0f0f;
    x = ((x >> 1) & k1) | ((x & k1) << 1);
    x = ((x >> 2) & k2) | ((x & k2) << 2);
    x = ((x >> 4) & k4) | ((x & k4) << 4);
    return x;
}

bitboard Board::reverse(bitboard x){
    return this->flipHorizontal(this->flipVertical(x));
}

/*
    To generate sliding moves/attacks we use the Hyperbola Quintessence algorithm 

    we treat the arithmetical carry, or inverse, borrow propagation as a way to generate sliding pieces attacks 
    in one ray direction. As long there are zeros left (empty squares) between blocker and subtracting piecse, 
    the borrow walks through, similar as a sliding piece moves along the empty squares. (https://www.chessprogramming.org/Hyperbola_Quintessence)

    lineAttacks =   (o-2r) ^ reverse( o'-2r')
    where o is the occupied squares, and r is the concerned pieces (o' and r' are the inverses)        
*/

bitboard Board::diagonalAttacks(bitboard occupied, int index){

    int rankIndex = index/8;
    int fileIndex = index%8;
    int diagonalIndex = (rankIndex - fileIndex) & 15;
    
    // piece location
    bitboard location = (((bitboard) 1) << index);

    bitboard forward = occupied & MaskDiagonal[diagonalIndex];    
    bitboard reverse = this->reverse(forward);    

    forward -= (location << 1);
    reverse -= (this->reverse(location) << 1);    

    return (forward ^ this->reverse(reverse)) & MaskDiagonal[diagonalIndex];
}

bitboard Board::antiDiagonalAttacks(bitboard occupied, int index){

    int rankIndex = index/8;
    int fileIndex = index%8;
    int antiDiagonalIndex = (rankIndex + fileIndex) ^ 7;;
    
    // piece location
    bitboard location = (((bitboard) 1) << index);

    bitboard forward = occupied & MaskAntiDiagonal[antiDiagonalIndex];    
    bitboard reverse = this->reverse(forward);    

    forward -= (location << 1);
    reverse -= (this->reverse(location) << 1);    

    return (forward ^ this->reverse(reverse)) & MaskAntiDiagonal[antiDiagonalIndex];    
}

bitboard Board::fileAttacks(bitboard occupied, int index){
    
    int fileIndex = index%8;    
    
    // piece location
    bitboard location = (((bitboard) 1) << index);

    bitboard forward = occupied & MaskFile[fileIndex];    
    bitboard reverse = this->reverse(forward);    

    forward -= (location << 1);
    reverse -= (this->reverse(location) << 1);    

    return (forward ^ this->reverse(reverse)) & MaskFile[fileIndex];    
}

bitboard Board::rankAttacks(bitboard occupied, int index){

    int rankIndex = index/8;    
    
    // piece location
    bitboard location = (((bitboard) 1) << index);

    bitboard forward = occupied & MaskRank[rankIndex];    
    bitboard reverse = this->reverse(forward);    

    forward -= (location << 1);
    reverse -= (this->reverse(location) << 1);    

    return (forward ^ this->reverse(reverse)) & MaskRank[rankIndex];    
}

bitboard Board::wBishopPseudoLegalMoves(int bishopIndex){

    return (this->diagonalAttacks(this->allPieces, bishopIndex) | 
           this->antiDiagonalAttacks(this->allPieces, bishopIndex)) & ~this->allWhitePieces;
}

bitboard Board::bBishopPseudoLegalMoves(int bishopIndex){

    return (this->diagonalAttacks(this->allPieces, bishopIndex) | 
           this->antiDiagonalAttacks(this->allPieces, bishopIndex)) & ~this->allBlackPieces;
}

bitboard Board::wRookPseudoLegalMoves(int rookIndex){

    return (this->fileAttacks(this->allPieces, rookIndex) | 
           this->rankAttacks(this->allPieces, rookIndex)) & ~this->allWhitePieces;
}

bitboard Board::bRookPseudoLegalMoves(int rookIndex){

    return (this->fileAttacks(this->allPieces, rookIndex) | 
           this->rankAttacks(this->allPieces, rookIndex)) & ~this->allBlackPieces;
}

bitboard Board::wQueenPseudoLegalMoves(int queenIndex){

    return (this->diagonalAttacks(this->allPieces, queenIndex) | 
           this->antiDiagonalAttacks(this->allPieces, queenIndex) | 
           this->fileAttacks(this->allPieces, queenIndex) | 
           this->rankAttacks(this->allPieces, queenIndex)) & ~this->allWhitePieces;
}

bitboard Board::bQueenPseudoLegalMoves(int queenIndex){

    return (this->diagonalAttacks(this->allPieces, queenIndex) | 
           this->antiDiagonalAttacks(this->allPieces, queenIndex) | 
           this->fileAttacks(this->allPieces, queenIndex) | 
           this->rankAttacks(this->allPieces, queenIndex)) & ~this->allBlackPieces;
}

std::ostream &operator<<(std::ostream &os, const Board &b){
    
    for(int i=7; i>=0; i--){
        for(int j=0; j<8; j++){

            int pieceIndex = 8*i+j;

            if((b.whitePawns & (((bitboard) 1) << pieceIndex )) != 0){
                os << 'P';
            } else if((b.blackPawns & (((bitboard) 1) << pieceIndex )) != 0){
                os << 'p';
            } else if((b.whiteKnights & (((bitboard) 1) << pieceIndex )) != 0){
                os << 'N';            
            } else if((b.blackKnights & (((bitboard) 1) << pieceIndex )) != 0){
                os << 'n';
            } else if((b.whiteBishops & (((bitboard) 1) << pieceIndex )) != 0){
                os << 'B';
            } else if((b.blackBishops & (((bitboard) 1) << pieceIndex )) != 0){
                os << 'b';
            } else if((b.whiteRooks & (((bitboard) 1) << pieceIndex )) != 0){
                os << 'R';
            } else if((b.blackRooks & (((bitboard) 1) << pieceIndex )) != 0){
                os << 'r';
            } else if((b.whiteQueens & (((bitboard) 1) << pieceIndex )) != 0){
                os << 'Q';
            } else if((b.blackQueens & (((bitboard) 1) << pieceIndex )) != 0){
                os << 'q';
            }else if((b.whiteKing & (((bitboard) 1) << pieceIndex )) != 0){
                os << 'K';
            } else if((b.blackKing & (((bitboard) 1) << pieceIndex )) != 0){
                os << 'k';
            }else{
                os << '-';
            }
        }
        os << std::endl;
    }
    return os;
}