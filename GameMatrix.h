#ifndef GAMEMATRIX_H
#define GAMEMATRIX_H
#include <QAbstractListModel>
#include <qqmlintegration.h>
#include <qtmetamacros.h>
constexpr int Rows = 22;
constexpr int Columns = 10;
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
    enum roles{ color = Qt::UserRole +1
                ,transperancy
    };

    Q_PROPERTY(int columns READ getColumns CONSTANT)
    Q_PROPERTY(int rows READ getRows CONSTANT)
public:
    enum Transperancy :uint8_t{Opaque,Transperant};
    enum Color :uint8_t{Red,Green,Blue,Purple,Null,TetreRed,TetreGreen,TetreBlue,TetrePurple };
    Q_ENUM(Color)
    Q_ENUM(Transperancy)
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
    void DataChanged(int index , int index2 = -1);
    void PrintMatrix();
    void ResetMatrix();
    std::array<Transperancy,Rows*Columns> TransperancyMatrix;
private:
    std::array<Color,Rows*Columns> Matrix;

};
inline GameMatrix::Color& operator--(GameMatrix::Color& color){
    if(color != GameMatrix::Red){
        color =  static_cast<GameMatrix::Color>(static_cast<int>(color -1));
    }else{
        color = GameMatrix::Null;
    }
    return color;
}
#endif // GAMEMATRIX_H
