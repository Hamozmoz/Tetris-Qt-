#include "GameMatrix.h"
#include <iostream>

GameMatrix::GameMatrix() {}

const int GameMatrix::GetIndex(int row, int col) const {
    int index = row * Columns + col ;
    if(index >= Matrix.size() ){
        std::cout << "Index Greater Than GridSize ! Returning 1 ...\n";
        return 0;
    }
    return index;
}

int GameMatrix::rowCount(const QModelIndex &parent) const{
    return Matrix.size();
}

QVariant GameMatrix::data(const QModelIndex &index, int role) const{
    if(index.row() >= Matrix.size() || index.row() < 0) {
        return QVariant();
    }
    if(role == roles::color) {return Matrix[index.row()];}
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
    return Rows;
}
