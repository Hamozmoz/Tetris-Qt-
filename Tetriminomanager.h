#ifndef TETRIMINOMANAGER_H
#define TETRIMINOMANAGER_H
#include <QObject>
#include <random>
#include "GameMatrix.h"
#include "Tetriminos.h"
#include <QChronoTimer>
class TetriminoManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GameMatrix* GameGrid READ getGameGrid CONSTANT)
    Q_PROPERTY(int Score READ readScore NOTIFY ScoreChanged)
public:
    enum Direction: uint8_t{
    Null,
    Left,
    Right
    };
    enum LineState: uint8_t{
        LineCleared,
        LineUncleared,
        LineEmpty
    };

    Q_ENUM(Direction)
    int Score{0};
    bool FastDrop{false};
    bool InstantDrop{false};
    Tetrimino CurrentTetrimino ;
    static TetriminoManager& Instance();
    GameMatrix* getGameGrid();
    int readScore();
   Q_INVOKABLE  void moveTetrimino(Direction dir);
   Q_INVOKABLE   void addTetriminoToGameGrid();
   Q_INVOKABLE void moveDown();
   Q_INVOKABLE void startGame();
   Q_INVOKABLE void changeFastDropToTrue();
   Q_INVOKABLE void changeInstantDrop();
   Q_INVOKABLE void changeFastDropToFalse();
   Q_INVOKABLE void rotateTetrimino();
   signals :
   void ScoreChanged();
 private:
   void ClearLine();
     void WallKick(Tetrimino &TetriminoToTest);
Rotation NextRotation();
   void CheckLines();
     const bool CheckCanMoveDown(const Tetrimino& tetrimino );
     const bool CheckCanMoveDown();
     bool CanMoveDown{false};
     void InitTetriminoBag();
     bool CanRotate(const Tetrimino& tetrimino);
    void GameLoop();
    QChronoTimer* FrameTimer ;
    QChronoTimer* TetriminoTimer ;
     TetriminoManager();
 std::random_device SeedGen;
    uint32_t Seed = SeedGen();
 inline void RestartTetriminoTimer();
 void rotateTetrimino(Rotation GoalRotation);
void SetTetrimino();
std::array<TetriminoType,7> TetriminoBag;
std::array<LineState,Rows-2> LineStates;
    GameMatrix GameGrid;
};
Position max(Position pos1,Position pos2);
Position min(Position pos1,Position pos2);
#endif // TETRIMINOMANAGER_H
