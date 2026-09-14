#ifndef TETRIMINOS_H
#define TETRIMINOS_H
#include <cstdint>
#include <array>
#include "GameMatrix.h"
enum TetriminoType:uint8_t{
    LPiece,
    IPiece,
    OPiece,
    SPiece,
    JPiece,
    TPiece,
    ZPiece,
    Null
};
enum Rotation:uint8_t{
    Up,
    Right,
    Down,
    Left,
    None
};
   inline Rotation& operator++(Rotation& rotation){
        if(rotation != Left){
        rotation = static_cast<Rotation>(rotation+1);
        }
        else{
            rotation = Up;
        }
        return rotation;
    }

struct Tetrimino{
    std::array<Position,4> Positions;
    TetriminoType Type = TetriminoType::Null;
    GameMatrix::Color Color = GameMatrix::Color::Null;
    Rotation Rotation = Up;
    Tetrimino(const TetriminoType& type = TetriminoType::Null,const Position& Baseposition = {} , GameMatrix::Color color = GameMatrix::Color::Null);

};


#endif // TETRIMINOS_H
