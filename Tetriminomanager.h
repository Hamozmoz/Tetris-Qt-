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
    Q_PROPERTY(bool DebugMode READ readDebugMode NOTIFY DebugModeChanged)
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
    bool DebugMode{false};
    bool FastDrop{false};
    std::array<Position,4> FinalDropPosition;
    Tetrimino CurrentTetrimino ;
    QChronoTimer* FrameTimer ;
    QChronoTimer* TetriminoTimer ;
    static TetriminoManager& Instance();
    GameMatrix* getGameGrid();
    int readScore();
    const bool readDebugMode()const;
   Q_INVOKABLE  void moveTetrimino(Direction dir);
   Q_INVOKABLE   void addTetriminoToGameGrid();
   Q_INVOKABLE void moveDown();
   Q_INVOKABLE void startGame();
   Q_INVOKABLE void changeFastDropToTrue();
   Q_INVOKABLE void changeFastDropToFalse();
   Q_INVOKABLE void rotateTetrimino();
   Q_INVOKABLE void changeDebugMode();
   Q_INVOKABLE void checkLines();
   Q_INVOKABLE void changeTileColor(int index);
   Q_INVOKABLE void exitGame();
   Q_INVOKABLE void instantDrop();
   signals :
   void ScoreChanged();
   void DebugModeChanged();
 private:
   void ClearLine();
     void WallKick(Tetrimino &TetriminoToTest);
Rotation NextRotation();
     void reset();
void CalculateFinalDropPositon();
     const bool CheckCanMoveDown(const std::array<Position,4> Positions);
     const bool CheckCanMoveDown();
     bool CanMoveDown{false};
     void InitTetriminoBag();
     bool CanRotate(const Tetrimino& tetrimino);
    void GameLoop();
     void TurnCurPosOpaque();
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
