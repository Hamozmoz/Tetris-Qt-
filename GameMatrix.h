#ifndef GAMEMATRIX_H
#define GAMEMATRIX_H
#include <QAbstractListModel>
#include <qtmetamacros.h>
#define Rows 20
#define Columns 10
class GameMatrix: public QAbstractListModel
{
    enum Color {Null,Red,Green,Blue,Purple };
    enum roles{ color = Qt::UserRole +1 };

    Q_OBJECT
    Q_PROPERTY(int Columns READ getColumns CONSTANT)
    Q_PROPERTY(int Rows READ getRows CONSTANT)
    Q_ENUM(Color)

public:
    GameMatrix();
   const int GetIndex(int row,int col)const;
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index,int role)const override;
    QHash<int,QByteArray> roleNames() const override;
    int getColumns() const;
    int getRows() const;
private:
    std::array<Color,Rows*Columns> Matrix;
};

#endif // GAMEMATRIX_H
