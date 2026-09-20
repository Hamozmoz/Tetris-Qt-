#ifndef TETRIMINOS_H
#define TETRIMINOS_H
#include <cstdint>
#include <array>
#include "GameMatrix.h"
enum TetriminoType:uint8_t{
    IPiece,
    TPiece,
    LPiece,
    JPiece,
    SPiece,
    ZPiece,
    OPiece,
    Null
};
enum Rotation:uint8_t{
    Up,
    Right,
    Down,
    Left,
    None
};
   Rotation& operator++(Rotation& rotation);
   TetriminoType& operator++(TetriminoType& TetType);

struct Tetrimino{
    std::array<Position,4> Positions;
    TetriminoType Type = TetriminoType::Null;
    GameMatrix::Color Color = GameMatrix::Color::Null;
    Rotation Rotation = Up;
    Tetrimino(const TetriminoType& type = TetriminoType::Null,const Position& Baseposition = {} , GameMatrix::Color color = GameMatrix::Color::Null);

};


#endif // TETRIMINOS_H
