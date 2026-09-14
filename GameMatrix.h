#ifndef GAMEMATRIX_H
#define GAMEMATRIX_H
#include <QAbstractListModel>
#include <qqmlintegration.h>
#include <qtmetamacros.h>
#define Rows 22
#define Columns 10


struct Position{
    int8_t column;
    int8_t row;
    Position(int8_t Row = 0, int8_t Col = 0): row(Row),column(Col)
    {}
    Position& operator=(const Position other)
    {
        this->column = other.column;
        this->row = other.row;
        return *this;
    }
    bool operator==(const Position other){
        return(this->column == other.column && this->row == other.row);
    }
    bool operator!= (const Position other ){
        return (!(*this == other));
    }
};
class GameMatrix: public QAbstractListModel
{
    Q_OBJECT
    QML_NAMED_ELEMENT("GameMatrix")
    enum roles{ color = Qt::UserRole +1 };

    Q_PROPERTY(int columns READ getColumns CONSTANT)
    Q_PROPERTY(int rows READ getRows CONSTANT)
public:
    enum Color {Red,Green,Blue,Purple,Null,TetreRed,TetreGreen,TetreBlue,TetrePurple };
    Q_ENUM(Color)

    GameMatrix();
   const int GetIndex(int row,int col)const;
    const int GetIndex(Position position)const;
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index,int role)const override;
    QHash<int,QByteArray> roleNames() const override;
    int getColumns() const;
    int getRows() const;
    Color& operator[](int index);
   Color& operator[](Position Pos) ;
    Q_INVOKABLE void getColor(int index,Color);
    void DataChanged(Position FirstPosition,Position Lastposition);
    void PrintMatrix();
private:
    std::array<Color,Rows*Columns> Matrix;
};

#endif // GAMEMATRIX_H
