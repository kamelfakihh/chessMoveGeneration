#include<iostream>
#include "Board.h"

void displayBitboard(bitboard b);

int main(){    
    
    std::string fen;
    char crank, cfile;
    int rank, file;

    std::cout << "Enter FEN string: "; // ex: 8/Pp2p1Q1/1p3n2/1pP2K1P/1r4RP/4PP2/Pb3q2/2Bk4
    std::cin >> fen;

    Board b = Board(fen);

    std::cout << b;

    while(true){
        
        std::cout << "Enter piece position (e.g A3) to get its psuedo legal moves: ";
        std::cin >> cfile >> crank;

        rank = (int) crank - '1';
        file = (int) cfile - 'A';

        std::cout << std::endl << "moves for piece at index: " << rank*8+file << std::endl;
        displayBitboard( b.getPseudoLegalMoves(rank*8+file) );        
        std::cout << std::endl;
    }

    return 0;
}

void displayBitboard(bitboard b){
    
    for(int i=7; i>=0; i--){
        for(int j=0; j<8; j++){
            if((b & (((bitboard) 1) << (i*8+j) )) != 0){
                std::cout << "* ";
            }else{
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }        
}