#include "Tetriminos.h"


Tetrimino::Tetrimino(const TetriminoType &type, const Position &Baseposition, GameMatrix::Color color)
    : Color(color) , Type(type)
{
    Positions[0] = Baseposition;
    if(Type == TetriminoType::IPiece){
        for(int i {1}; i< 4 ; i++){
            Positions[i].column = Baseposition.column;
            Positions[i].row = Baseposition.row + i;
        }
    }else if(Type == TetriminoType::LPiece){
        Positions[1].column = Baseposition.column;
        Positions[2].column = Baseposition.column;
        Positions[3].column = Baseposition.column +1;
        Positions[1].row = Baseposition.row +1;
        Positions[2].row = Baseposition.row +2;
        Positions[3].row = Baseposition.row +2;
    }else if (Type == TetriminoType::JPiece){
        Positions[1].column = Baseposition.column;
        Positions[2].column = Baseposition.column -1;
        Positions[3].column = Baseposition.column ;
        Positions[1].row = Baseposition.row +1;
        Positions[2].row = Baseposition.row +2;
        Positions[3].row = Baseposition.row +2;
    }else if(Type == TetriminoType::TPiece){
        Positions[1].column = Baseposition.column -1;
        Positions[2].column = Baseposition.column   ;
        Positions[3].column = Baseposition.column +1;
        Positions[1].row = Baseposition.row +1;
        Positions[2].row = Baseposition.row +1;
        Positions[3].row = Baseposition.row +1;
    }else if (Type == TetriminoType::OPiece){
        Positions[1].column = Baseposition.column +1;
        Positions[2].column = Baseposition.column;
        Positions[3].column = Baseposition.column +1;
        Positions[1].row = Baseposition.row;
        Positions[2].row = Baseposition.row +1 ;
        Positions[3].row = Baseposition.row +1;
    }else if (Type == TetriminoType::ZPiece){
        Positions[1].column = Baseposition.column -1;
        Positions[2].column = Baseposition.column;
        Positions[3].column = Baseposition.column-1;
        Positions[1].row = Baseposition.row +1;
        Positions[2].row = Baseposition.row +1;
        Positions[3].row = Baseposition.row +2;
    }else if (Type == TetriminoType::SPiece){
        Positions[1].column = Baseposition.column;
        Positions[2].column = Baseposition.column+1;
        Positions[3].column = Baseposition.column+1;
        Positions[1].row = Baseposition.row+1;
        Positions[2].row = Baseposition.row+1;
        Positions[3].row = Baseposition.row+2;
    }
}
TetriminoType &operator++(TetriminoType &TetType){
    if(TetType != ZPiece){
        TetType = static_cast<TetriminoType>(static_cast<int>(TetType) +1);
    }else {
        TetType =LPiece;
    }
    return TetType;
}

Rotation &operator++(Rotation &rotation){
    if(rotation != Left){
        rotation = static_cast<Rotation>(rotation+1);
    }
    else{
        rotation = Up;
    }
    return rotation;
}
