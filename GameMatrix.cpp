#include "GameMatrix.h"
#include <iostream>


GameMatrix::GameMatrix()
{
#ifndef NDEBUG
    connect(this,&QAbstractListModel::dataChanged,this,&GameMatrix::PrintMatrix);
#endif
    Matrix.fill(Color::Null);
}

const int GameMatrix::GetIndex(int row, int col) const {
    int index = row * Columns + col ;
#ifndef NDEBUG
    if(index >= Matrix.size() ){
        std::cout << "Index Greater Than GridSize ! Returning 0 ...\n";
        return 0;
    }
#endif
    return index;
}

const int GameMatrix::GetIndex(Position position) const {
    int index = position.row * Columns + position.column;
#ifndef NDEBUG
    if(index >= Matrix.size() ){
        std::cout << "Index Greater Than GridSize ! Returning 0 ...\n";
        return 0;
    }
#endif
    return index;
}

int GameMatrix::rowCount(const QModelIndex &parent) const{
    return Matrix.size();
}

QVariant GameMatrix::data(const QModelIndex &index, int role) const{
    if(index.row() >= Matrix.size() || index.row() < 0) {
        return QVariant();
    }
    if(role == roles::color) {return Matrix[index.row()+ 20];}
    return QVariant() ;
}

QHash<int, QByteArray> GameMatrix::roleNames() const{
    QHash<int,QByteArray> roles;
    roles[roles::color] ="Color";
    return roles;
}

int GameMatrix::getColumns() const{
    return Columns;
}

int GameMatrix::getRows() const{
    return Rows -2;
}

 GameMatrix::Color &GameMatrix::operator[](Position Pos)   {
    return Matrix[Pos.row * Columns + Pos.column];

}

GameMatrix::Color &GameMatrix::operator[](int index){
    return Matrix[index];
}

void GameMatrix::getColor(int index,Color col){
    Matrix[index] = col;
    QModelIndex Indice = createIndex(index,0);
    dataChanged(Indice,Indice);
}

//Notifies Qml That The Tiles Between The FirstPosition And The LastPosition Were Modified
void GameMatrix::DataChanged(Position FirstPosition, Position Lastposition){

    if(FirstPosition.row -2 < 0){
        FirstPosition.row = 0;
    }else{
        FirstPosition.row -=2;
    }
    if(Lastposition.row -2 < 0){
        Lastposition.row = 0;}
    else{
        Lastposition.row -=2;
    }
    QModelIndex First = createIndex(GetIndex(FirstPosition),0);
    QModelIndex Last = createIndex(GetIndex(Lastposition),0);
    dataChanged(First,Last);
}

void GameMatrix::PrintMatrix(){
    std::cout << "\033[2J\033[H";
    for(int row {0};row < Rows;row++){
        for(int col {0}; col <Columns; col++){
            if(Matrix[GetIndex(row,col)] != Color::Null){
                std::cout << "C ";
            }else {
                std::cout << "N ";
            }

        }

        std::cout <<std::endl ;
    }

}
