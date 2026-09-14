#include "Tetriminomanager.h"
#include <iostream>
#include "GameManager.h"
//#define DumbMode
TetriminoManager &TetriminoManager::Instance(){
    static TetriminoManager manager;
    std::cout << "Tetrimino Manager Instance Created " << std::endl;
    return manager;
}


void TetriminoManager::moveTetrimino(Direction dir){

if(dir == Direction::Left){
    Position PreviousPos = CurrentTetrimino.Positions[3];
    for(int i {0}; i< CurrentTetrimino.Positions.size();i++)
    {
    if(CurrentTetrimino.Positions[i].column - 1 == -1 || GameGrid[GameGrid.GetIndex(CurrentTetrimino.Positions[i].row,CurrentTetrimino.Positions[i].column-1)] <4){
        return;
    }}

    for(auto pos : CurrentTetrimino.Positions){
        GameGrid[GameGrid.GetIndex(pos)] = GameMatrix::Null;
    }
    for(auto& pos : CurrentTetrimino.Positions){
        --pos.column ;
        GameGrid[GameGrid.GetIndex(pos)] = CurrentTetrimino.Color;
    }
    Position CurrentPosition = CurrentTetrimino.Positions[0];
    if(CurrentPosition.row <2){
        CurrentPosition.row = 2;
        CurrentPosition.column = 0;
    }
    GameGrid.DataChanged(CurrentTetrimino.Positions[0],PreviousPos);
    RestartTetriminoTimer();
    }else if(dir == Direction::Right){
    Position PreviousPos = CurrentTetrimino.Positions[0];
    for(int i {0}; i< CurrentTetrimino.Positions.size();i++)
    {
    if(CurrentTetrimino.Positions[i].column + 1== Columns || GameGrid[GameGrid.GetIndex(CurrentTetrimino.Positions[i].row,CurrentTetrimino.Positions[i].column+1)] <4){
        return;
    }}
    for(auto pos : CurrentTetrimino.Positions){
        GameGrid[GameGrid.GetIndex(pos)] = GameMatrix::Null;
    }
    for(auto& pos : CurrentTetrimino.Positions){
        ++pos.column;
        GameGrid[GameGrid.GetIndex(pos)] = CurrentTetrimino.Color;
    }
    if(PreviousPos.row < 2){
        PreviousPos.row = 2;
        PreviousPos.column = 0;
    }
    GameGrid.DataChanged(PreviousPos,CurrentTetrimino.Positions[3]);
    RestartTetriminoTimer();
    }


}

void TetriminoManager::addTetriminoToGameGrid(){

    static std::mt19937 ColorGen(Seed);
    static std::uniform_int_distribution<uint8_t> RandomColorDistributer(5,8);
    TetriminoType CurrentType = TetriminoType::Null;
    bool BagEmpty{true};
    while (BagEmpty) {


    for(int i{0} ; i<TetriminoBag.size();i++){
        if(TetriminoBag[i] != TetriminoType::Null){
            CurrentType = TetriminoBag[i];
            TetriminoBag[i] = TetriminoType::Null;
            BagEmpty = false;
            break;
        }
}
        if(!BagEmpty){
            break;
        }
        InitTetriminoBag();
    }
    GameMatrix::Color RandomColor = static_cast<GameMatrix::Color>(RandomColorDistributer(ColorGen));
    CurrentTetrimino = Tetrimino{CurrentType,Position{1,5},RandomColor};

    for(int i {1} ; i< 4 ; ++i){
        GameGrid[GameGrid.GetIndex(CurrentTetrimino.Positions[i])] = CurrentTetrimino.Color;

    }
    Position PreviousPosition = CurrentTetrimino.Positions[0];
    if(PreviousPosition.row < 2){
        PreviousPosition.row = 2;
        PreviousPosition.column = 0;
    }
    GameGrid.DataChanged(PreviousPosition,CurrentTetrimino.Positions[3]);

}

GameMatrix *TetriminoManager::getGameGrid(){
    return &GameGrid;
}

void TetriminoManager::startGame(){
    InitTetriminoBag();
    addTetriminoToGameGrid();
    GameManager::Instance().ChangeGameState(GameManager::GameRunning);
    FrameTimer->start();


}

void TetriminoManager::changeFastDropToTrue(){
    if(FastDrop || !CanMoveDown){
        return;
    }
    FastDrop = true;
}

void TetriminoManager::changeInstantDrop(){
    InstantDrop = !InstantDrop;
}

void TetriminoManager::changeFastDropToFalse(){
    FastDrop = false;
}

void TetriminoManager::ClearLine(){
    Position FirstPosition;
    Position LastPosition{Rows-1,Columns-1};
    int ClearedLines{0};
    bool MovedLines {false};
    for(int row =LineStates.size() -1;row > 1;--row){
        if(LineStates[row] != LineCleared){
            FirstPosition.row = row+2;
        }




            if(LineStates[row] == LineCleared){
                ++ClearedLines;
                if(MovedLines){
                    MovedLines = false;
                    ClearedLines = 0;
                }
                for(int col {0}; col < Columns; ++col ){
           GameGrid[GameGrid.GetIndex(row+2,col)] = GameMatrix::Null;
            }
            }else {
                if(ClearedLines >0){
                for(int col {0}; col <Columns; ++col){
                    std::swap(GameGrid[GameGrid.GetIndex(row+2,col)],GameGrid[GameGrid.GetIndex(row+ClearedLines+2,col)]);
                }
                MovedLines = true;
                }
            }
            }
    GameGrid.DataChanged(FirstPosition,LastPosition);

}

void TetriminoManager::WallKick(Tetrimino &TetriminoToTest, Position *PositionToMove , Position *PositionToMove2){
    bool OutOfHorizontalBounds{true};
    while(OutOfHorizontalBounds) {
    for(int i{0}; i< TetriminoToTest.Positions.size();i++){
            if(TetriminoToTest.Positions[i].column < 0)    {
            OutOfHorizontalBounds = true;
                break;
            }else if(OutOfHorizontalBounds){
            OutOfHorizontalBounds = false;
            }
    }
    if(!OutOfHorizontalBounds){
        break;
    }
    for(auto& Pos : TetriminoToTest.Positions){
        ++Pos.column;
    }
    if(PositionToMove ){
        ++PositionToMove->column;
    }
    if(PositionToMove2){
        ++PositionToMove2->column;
    }
    }
    OutOfHorizontalBounds = true;

    while(OutOfHorizontalBounds){
        for(int i {0} ; i< TetriminoToTest.Positions.size();i++){
            if(TetriminoToTest.Positions[i].column >= Columns){
                OutOfHorizontalBounds = true;
                break;
            }else if(OutOfHorizontalBounds){
                OutOfHorizontalBounds = false;
            }
    }
        if(!OutOfHorizontalBounds)    {
        break;
        }
        for(auto& Pos : TetriminoToTest.Positions){
            --Pos.column;
        }
        if(PositionToMove){
            --PositionToMove->column;
        }
        if(PositionToMove2){
            --PositionToMove2->column;
        }
    }

}
Rotation TetriminoManager::NextRotation(){
    Rotation Temp = CurrentTetrimino.Rotation;
    return ++Temp;
}

void TetriminoManager::CheckLines(){
        bool rowempty {true};
    for(int row {0}; row< Rows-2 ;row++){
        LineStates[row] = LineCleared;
        rowempty = true;
        for(int col{0}; col < Columns; col++){

             if(GameGrid[GameGrid.GetIndex(row+2,col)] >3){
                LineStates[row] = LineUncleared;
             }else{
                 rowempty = false;
             }
             }
        if(rowempty){
                 LineStates[row] = LineEmpty;
        }
        }
    ClearLine();
    }




void TetriminoManager::moveDown(){
    if(CanMoveDown){

        Position PreviousPosition = CurrentTetrimino.Positions[0];
        if(PreviousPosition.row < 2){
            PreviousPosition.row = 2;
            PreviousPosition.column = 0;
        }
        for(auto Pos : CurrentTetrimino.Positions){
                GameGrid[Pos] = GameMatrix::Null;
            }

        for(int i {0}; i<CurrentTetrimino.Positions.size() ; i++){
            if(CurrentTetrimino.Positions[i].row +2 > Rows){
                return;
            }
            ++CurrentTetrimino.Positions[i].row;
            GameGrid[CurrentTetrimino.Positions[i]] = CurrentTetrimino.Color;

        }
        if(TetriminoTimer->isActive()){
            TetriminoTimer->stop();
        }
        GameGrid.DataChanged(PreviousPosition,CurrentTetrimino.Positions[3]);
    }



}
//Checks If Passed Tetrimino Can Move Down
const bool TetriminoManager::CheckCanMoveDown(const Tetrimino &tetrimino){
    for(auto Pos : tetrimino.Positions){

        if(GameGrid[GameGrid.GetIndex(Pos.row +1,Pos.column )] < 4 || Pos.row +1 >= Rows){
            return false;
        }
    }

    return true;
}
//Checks If The Currently Held Tetrimino Can Move Down
const bool TetriminoManager::CheckCanMoveDown(){
    for(auto Pos : CurrentTetrimino.Positions){
        if ( Pos.row +1 >= Rows||GameGrid[GameGrid.GetIndex(Pos.row+1,Pos.column)] <4){
            return false;
        }
    }
    return true;
}

void TetriminoManager::InitTetriminoBag()
{
    static std::mt19937 TetriminoBagGen(Seed);
    TetriminoBag = {TetriminoType::IPiece,TetriminoType::LPiece,TetriminoType::OPiece,
                    TetriminoType::JPiece,TetriminoType::SPiece,TetriminoType::TPiece,TetriminoType::ZPiece};

    std::shuffle(TetriminoBag.begin(),TetriminoBag.end(),TetriminoBagGen);
}

bool TetriminoManager::CanRotate(const Tetrimino &tetrimino){
    for(auto pos : tetrimino.Positions) {
        if(pos.row > Rows ||GameGrid[pos] < 4 ){
            return false;
        }
    }
    return true;
}

void TetriminoManager::GameLoop()
{
    static int CurrentFrame {0};

    ++CurrentFrame;
    CanMoveDown = CheckCanMoveDown();
    if(CurrentFrame % 3 == 0 && FastDrop){
        moveDown();

    }

    if(CurrentFrame % 60 == 0 && !FastDrop){
        moveDown();

    }
    if(InstantDrop){
        moveDown();
        InstantDrop = false;
    }
    if(CurrentFrame == 60 ){
        if(!CanMoveDown && !TetriminoTimer->isActive()){
            TetriminoTimer->start();
        }
        CurrentFrame = 0;
    }
}

TetriminoManager::TetriminoManager(){
    using namespace std::chrono_literals;
    FrameTimer = new QChronoTimer(this);
    TetriminoTimer = new QChronoTimer(this);
    TetriminoTimer->setInterval(1000ms);
    FrameTimer->setInterval(16ms);
    TetriminoTimer->setSingleShot(true);
    connect(FrameTimer,&QChronoTimer::timeout,this ,&TetriminoManager::GameLoop);
    connect(TetriminoTimer,&QChronoTimer::timeout,this,&TetriminoManager::SetTetrimino);
}

void TetriminoManager::RestartTetriminoTimer(){
    if(TetriminoTimer->isActive()){
        TetriminoTimer->start();
    }
}

void TetriminoManager::DoDumbStuff(){
    for(int line {0} ; line < LineStates.size() ; line ++){
        if(LineStates[line] == LineEmpty){
            int LinesToMove{1};
            int RowToStartMoving{0};
            for(int row {line+1};LineStates[row] == LineEmpty; row++){
                LinesToMove++;
                RowToStartMoving = row;
            }
            for(;RowToStartMoving<Rows-2;RowToStartMoving++){
                for(int col{0}; col< Columns;col++) {
                    std::swap(GameGrid[GameGrid.GetIndex(RowToStartMoving,col)],GameGrid[GameGrid.GetIndex(line,col)]);

                }
            }
        }
    }

}
void TetriminoManager::rotateTetrimino(Rotation GoalRotation= Rotation::None)
{


    if(GoalRotation == Rotation::None)
    {
        GoalRotation = NextRotation();
    }
    Tetrimino TestTetrimino {CurrentTetrimino};
    if(TestTetrimino.Type == OPiece){
        return;
    }
    do{
    ++TestTetrimino.Rotation;
    if(TestTetrimino.Type == IPiece){
        if( TestTetrimino.Rotation == Rotation::Right) {
            --TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[0].row +=2;
            for(int i{1} ; i< TestTetrimino.Positions.size();i++ ){
                TestTetrimino.Positions[i].row = TestTetrimino.Positions[0].row;
                TestTetrimino.Positions[i].column = TestTetrimino.Positions[0].column +i;
            }
        }else if (TestTetrimino.Rotation == Rotation::Down ){
            TestTetrimino.Positions[0].column +=2;
            TestTetrimino.Positions[0].row-=2;
            for(int i {1}; i< TestTetrimino.Positions.size();++i){
                TestTetrimino.Positions[i].column = TestTetrimino.Positions[0].column;
                TestTetrimino.Positions[i].row = TestTetrimino.Positions[0].row + i;
            }
        }else if(TestTetrimino.Rotation == Rotation::Left){
            TestTetrimino.Positions[0].column -=2;
            TestTetrimino.Positions[0].row +=2;
            for(int i{1} ; i< TestTetrimino.Positions.size();i++ ){
                TestTetrimino.Positions[i].row = TestTetrimino.Positions[0].row;
                TestTetrimino.Positions[i].column = TestTetrimino.Positions[0].column +i;
        }
        }else if(TestTetrimino.Rotation == Rotation::Up){
            ++TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[0].row -=2;
            for(int i {1}; i< TestTetrimino.Positions.size();++i){
                TestTetrimino.Positions[i].column = TestTetrimino.Positions[0].column;
                TestTetrimino.Positions[i].row = TestTetrimino.Positions[0].row + i;
            }
        }
    }else if(TestTetrimino.Type == TPiece){
        if(TestTetrimino.Rotation == Rotation::Right){
            TestTetrimino.Positions[1].column = TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[2].column = TestTetrimino.Positions[0].column +1;
            TestTetrimino.Positions[3].column = TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[1].row = TestTetrimino.Positions[0].row +1;
            TestTetrimino.Positions[2].row = TestTetrimino.Positions[0].row +1;
            TestTetrimino.Positions[3].row = TestTetrimino.Positions[0].row +2;
        }else if(TestTetrimino.Rotation == Rotation::Down){
            --TestTetrimino.Positions[0].column ;
            ++TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[1].column = TestTetrimino.Positions[0].column +1;
            TestTetrimino.Positions[2].column = TestTetrimino.Positions[0].column +2;
            TestTetrimino.Positions[3].column = TestTetrimino.Positions[0].column +1;
            TestTetrimino.Positions[1].row = TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[2].row = TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[3].row = TestTetrimino.Positions[0].row +1;
        }else if (TestTetrimino.Rotation == Rotation::Left){
            ++TestTetrimino.Positions[0].column;
            --TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[1].column = TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[2].column = TestTetrimino.Positions[0].column -1;
            TestTetrimino.Positions[3].column = TestTetrimino.Positions[0].column ;
            TestTetrimino.Positions[1].row = TestTetrimino.Positions[0].row +1;
            TestTetrimino.Positions[2].row = TestTetrimino.Positions[0].row +1;
            TestTetrimino.Positions[3].row = TestTetrimino.Positions[0].row +2;
        }else if (TestTetrimino.Rotation == Rotation::Up){
            TestTetrimino.Positions[1].column = TestTetrimino.Positions[0].column -1;
            TestTetrimino.Positions[2].column = TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[3].column = TestTetrimino.Positions[0].column +1;
            for(int i {1}; i< TestTetrimino.Positions.size();++i){
                TestTetrimino.Positions[i].row = TestTetrimino.Positions[0].row +1;
            }
        }
    }else if(TestTetrimino.Type == LPiece){
        if(TestTetrimino.Rotation == Rotation::Right){
            --TestTetrimino.Positions[0].column;
            ++TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[1].column = TestTetrimino.Positions[0].column +1;
            TestTetrimino.Positions[2].column = TestTetrimino.Positions[0].column +2;
            TestTetrimino.Positions[3].column = TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[1].row = TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[2].row = TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[3].row = TestTetrimino.Positions[0].row + 1;

        }else if(TestTetrimino.Rotation == Rotation::Down){
            --TestTetrimino.Positions[0].row;
            for(int i {1} ; i< TestTetrimino.Positions.size();++i){
                TestTetrimino.Positions[i].column = TestTetrimino.Positions[0].column +1;
                TestTetrimino.Positions[i].row = TestTetrimino.Positions[0].row +i -1;
            }
        }else if (TestTetrimino.Rotation == Rotation::Left){
            TestTetrimino.Positions[0].column +=2;
            ++TestTetrimino.Positions[0].row;
            for(int i{1}; i<TestTetrimino.Positions.size();++i){
                TestTetrimino.Positions[i].row = TestTetrimino.Positions[0].row +1;
                TestTetrimino.Positions[i].column = TestTetrimino.Positions[0].column -3 +i;
            }
        }else if (TestTetrimino.Rotation == Rotation::Up){
            --TestTetrimino.Positions[0].column;
            --TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[1].column = TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[2].column = TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[3].column = TestTetrimino.Positions[0].column +1;
            TestTetrimino.Positions[1].row = TestTetrimino.Positions[0].row +1;
            TestTetrimino.Positions[2].row = TestTetrimino.Positions[0].row +2;
            TestTetrimino.Positions[3].row = TestTetrimino.Positions[0].row +2;
        }
    }else if(TestTetrimino.Type == JPiece){
        if(TestTetrimino.Rotation == Rotation::Right){
            --TestTetrimino.Positions[0].column;
            ++TestTetrimino.Positions[0].row;
            for(int i {1} ; i< TestTetrimino.Positions.size();++i){
                TestTetrimino.Positions[i].column = TestTetrimino.Positions[0].column +i-1;
                TestTetrimino.Positions[i].row = TestTetrimino.Positions[0].row +1;
            }
        }else if(TestTetrimino.Rotation == Rotation::Down){
            --TestTetrimino.Positions[0].row;
            ++TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[1].column = TestTetrimino.Positions[0].column +1;
            TestTetrimino.Positions[2].column = TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[3].column = TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[1].row = TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[2].row = TestTetrimino.Positions[0].row +1;
            TestTetrimino.Positions[3].row = TestTetrimino.Positions[0].row +2;
        }else if (TestTetrimino.Rotation == Rotation::Left){
            ++TestTetrimino.Positions[0].row;
            --TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[1].column = TestTetrimino.Positions[0].column +1;
            TestTetrimino.Positions[2].column = TestTetrimino.Positions[0].column +2;
            TestTetrimino.Positions[3].column = TestTetrimino.Positions[0].column +2;
            TestTetrimino.Positions[1].row = TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[2].row = TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[3].row = TestTetrimino.Positions[0].row +1;
        }else if(TestTetrimino.Rotation == Rotation::Up){
            --TestTetrimino.Positions[0].row;
            ++TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[1].column = TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[2].column = TestTetrimino.Positions[0].column-1;
            TestTetrimino.Positions[3].column = TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[1].row = TestTetrimino.Positions[0].row +1;
            TestTetrimino.Positions[2].row = TestTetrimino.Positions[0].row +2;
            TestTetrimino.Positions[2].row = TestTetrimino.Positions[0].row +2;
        }
    }else if(TestTetrimino.Type == SPiece){
        if(TestTetrimino.Rotation == Rotation::Right){
            ++TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[1].column =  TestTetrimino.Positions[0].column +1;
            TestTetrimino.Positions[2].column =  TestTetrimino.Positions[0].column -1;
            TestTetrimino.Positions[3].column =  TestTetrimino.Positions[0].column ;
            TestTetrimino.Positions[1].row =  TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[2].row =  TestTetrimino.Positions[0].row +1;
            TestTetrimino.Positions[3].row =  TestTetrimino.Positions[0].row +1;
        }else if(TestTetrimino.Rotation == Rotation::Down){
            --TestTetrimino.Positions[0].column;
            --TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[1].column =  TestTetrimino.Positions[0].column ;
            TestTetrimino.Positions[2].column =  TestTetrimino.Positions[0].column +1;
            TestTetrimino.Positions[3].column =  TestTetrimino.Positions[0].column +1;
            TestTetrimino.Positions[1].row =  TestTetrimino.Positions[0].row +1;
            TestTetrimino.Positions[2].row =  TestTetrimino.Positions[0].row +1;
            TestTetrimino.Positions[3].row =  TestTetrimino.Positions[0].row +2;
        }else if(TestTetrimino.Rotation == Rotation::Left){
            ++TestTetrimino.Positions[0].column;
            ++TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[1].column = TestTetrimino.Positions[0].column +1;
            TestTetrimino.Positions[2].column = TestTetrimino.Positions[0].column -1;
            TestTetrimino.Positions[3].column = TestTetrimino.Positions[0].column;
            TestTetrimino.Positions[1].row = TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[2].row = TestTetrimino.Positions[0].row +1;
            TestTetrimino.Positions[3].row = TestTetrimino.Positions[0].row +1;
        }else if(TestTetrimino.Rotation == Rotation::Up){
            --TestTetrimino.Positions[0].row;
            TestTetrimino.Positions[1].column =  TestTetrimino.Positions[0].column ;
            TestTetrimino.Positions[2].column =  TestTetrimino.Positions[0].column +1;
            TestTetrimino.Positions[3].column =  TestTetrimino.Positions[0].column +1;
            TestTetrimino.Positions[1].row =  TestTetrimino.Positions[0].row +1;
            TestTetrimino.Positions[2].row =  TestTetrimino.Positions[0].row +1;
            TestTetrimino.Positions[3].row =  TestTetrimino.Positions[0].row +2;
        }


    }else if(TestTetrimino.Type == ZPiece){
        if(TestTetrimino.Rotation == Rotation::Right){
         TestTetrimino.Positions[0].column -=2;
         ++TestTetrimino.Positions[0].row;
         TestTetrimino.Positions[1].column = TestTetrimino.Positions[0].column +1;
         TestTetrimino.Positions[2].column = TestTetrimino.Positions[0].column +1;
         TestTetrimino.Positions[3].column = TestTetrimino.Positions[0].column +2;
         TestTetrimino.Positions[1].row = TestTetrimino.Positions[0].row;
         TestTetrimino.Positions[2].row = TestTetrimino.Positions[0].row +1;
         TestTetrimino.Positions[3].row = TestTetrimino.Positions[0].row +1;

    }else if (TestTetrimino.Rotation == Rotation::Down){
        ++TestTetrimino.Positions[0].column;
        --TestTetrimino.Positions[0].row;
         TestTetrimino.Positions[1].column = TestTetrimino.Positions[0].column -1;
         TestTetrimino.Positions[2].column = TestTetrimino.Positions[0].column ;
         TestTetrimino.Positions[3].column = TestTetrimino.Positions[0].column -1;
         TestTetrimino.Positions[1].row = TestTetrimino.Positions[0].row +1;
         TestTetrimino.Positions[2].row = TestTetrimino.Positions[0].row +1;
         TestTetrimino.Positions[3].row = TestTetrimino.Positions[0].row +2;
    }else if (TestTetrimino.Rotation == Rotation::Left){
        --TestTetrimino.Positions[0].column;
        ++TestTetrimino.Positions[0].row;
         TestTetrimino.Positions[1].column = TestTetrimino.Positions[0].column +1;
         TestTetrimino.Positions[2].column = TestTetrimino.Positions[0].column +1;
         TestTetrimino.Positions[3].column = TestTetrimino.Positions[0].column +2;
         TestTetrimino.Positions[1].row = TestTetrimino.Positions[0].row;
         TestTetrimino.Positions[2].row = TestTetrimino.Positions[0].row +1;
         TestTetrimino.Positions[3].row = TestTetrimino.Positions[0].row +1;
    }else if(TestTetrimino.Rotation == Rotation::Up){
        TestTetrimino.Positions[0].column +=2;
        --TestTetrimino.Positions[0].row;
         TestTetrimino.Positions[1].column = TestTetrimino.Positions[0].column -1;
         TestTetrimino.Positions[2].column = TestTetrimino.Positions[0].column ;
         TestTetrimino.Positions[3].column = TestTetrimino.Positions[0].column -1;
         TestTetrimino.Positions[1].row = TestTetrimino.Positions[0].row +1;
         TestTetrimino.Positions[2].row = TestTetrimino.Positions[0].row +1;
         TestTetrimino.Positions[3].row = TestTetrimino.Positions[0].row +2;
    }
    } }while(TestTetrimino.Rotation != GoalRotation);


    WallKick(TestTetrimino);

if(CanRotate(TestTetrimino)){
        Position FirstPosition = min(CurrentTetrimino.Positions[0],TestTetrimino.Positions[0]);
        Position LastPosition  = max(CurrentTetrimino.Positions[3],TestTetrimino.Positions[3]);

        for(auto Pos : CurrentTetrimino.Positions){
            GameGrid[Pos] = GameMatrix::Null;
        }
        CurrentTetrimino = TestTetrimino;
        for(auto Pos : CurrentTetrimino.Positions){
            GameGrid[Pos] = CurrentTetrimino.Color;
        }
    GameGrid.DataChanged(FirstPosition,LastPosition);
        if(TetriminoTimer->isActive()){
            TetriminoTimer->stop();
        }
    }
}
void TetriminoManager::rotateTetrimino(){
    rotateTetrimino(Rotation::None);
}
void TetriminoManager::SetTetrimino(){
    GameMatrix::Color TileColor = CurrentTetrimino.Color == GameMatrix::TetreBlue? GameMatrix::Blue:
                                      CurrentTetrimino.Color == GameMatrix::TetreGreen? GameMatrix::Green:
                                      CurrentTetrimino.Color == GameMatrix::TetreRed? GameMatrix::Red:
                                      CurrentTetrimino.Color == GameMatrix::TetrePurple?GameMatrix::Purple:
                                      GameMatrix::Null;

    for(auto pos : CurrentTetrimino.Positions){
        GameGrid[pos]= TileColor;

    }
    CheckLines();
    addTetriminoToGameGrid();

}
//Checks Which Position Is Last In The Matrix
Position max(Position pos1, Position pos2){
    if((pos1.row *Columns + pos1.column) >(pos2.row * Columns + pos2.column)){
        return pos1;
    }else{
        return pos2;
    }
}
//Checks Which Position Is First In The Matrix
Position min(Position pos1, Position pos2) {
    if((pos1.row  * Columns + pos1.column) < (pos2.row * Columns + pos2.column)){
        return pos1;
    }else {
        return pos2;
    }
}
