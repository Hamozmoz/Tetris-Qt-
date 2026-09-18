#include "Tetriminomanager.h"
#include "GameManager.h"
//#define IMode

TetriminoManager &TetriminoManager::Instance(){
    static TetriminoManager manager;
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
    TurnCurPosOpaque();
    CalculateFinalDropPositon();
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
    TurnCurPosOpaque();
    CalculateFinalDropPositon();
    }
    RestartTetriminoTimer();



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
    CalculateFinalDropPositon();
}

GameMatrix *TetriminoManager::getGameGrid(){
    return &GameGrid;
}

int TetriminoManager::readScore(){
    return Score;
}

const bool TetriminoManager::readDebugMode() const {
    return DebugMode;
}

void TetriminoManager::startGame(){
    GameManager::Instance().ChangeGameState(GameManager::GameRunning);
    if(!DebugMode){
    InitTetriminoBag();
    addTetriminoToGameGrid();
    FrameTimer->start();
    }


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
    int ScoreToAdd{0};
   int LinesToClear = 0;
    bool LinesCleared {false};
    for(int row = LineStates.size() -1; row>1;--row){
       if(LineStates[row] == LineCleared){
            ++LinesToClear;
           for(int col = 0 ; col < Columns; ++col){
                GameGrid[GameGrid.GetIndex(row+2,col)] = GameMatrix::Null;
           }
           if(LinesCleared){
                LinesCleared = false;
               ScoreToAdd += LinesToClear * 100;
               LinesToClear = 0;
           }
       }else{
           if(LinesToClear > 0){
               if(LineStates[row] != LineEmpty){
               for(int col = 0;col < Columns ; ++col){
                   std::swap(GameGrid[GameGrid.GetIndex(row+2,col)],GameGrid[GameGrid.GetIndex(row+2+LinesToClear,col)]);

               }}
               LinesCleared = true;
           }
       }

    }
    ScoreToAdd += LinesToClear * 100;
    Score += ScoreToAdd;
    emit ScoreChanged();
    GameGrid.DataChanged({0,0},{Rows-1,Columns-1});
}

void TetriminoManager::WallKick(Tetrimino &TetriminoToTest){

    bool OutOfVerticalBounds{false};
    for(auto Pos: TetriminoToTest.Positions){

        if(Pos.row >= Rows || GameGrid[Pos] < GameMatrix::Null){
            OutOfVerticalBounds = true;
            break;
        }

    }
    if(OutOfVerticalBounds){
        for(auto& Pos : TetriminoToTest.Positions){
            --Pos.column;
        }
    }

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


    }




}
Rotation TetriminoManager::NextRotation(){
    Rotation Temp = CurrentTetrimino.Rotation;
    return ++Temp;
}

void TetriminoManager::reset(){
    FrameTimer->stop();
    TetriminoTimer->stop();
    DebugMode = false;
    emit DebugModeChanged();
    FastDrop = false;
    InstantDrop = false;
    Tetrimino Empty ;
    CurrentTetrimino = Empty;
    FinalDropPosition = Empty.Positions;
    CanMoveDown  = false;
    GameGrid.ResetMatrix();
}

void TetriminoManager::checkLines(){
    int ColoredTilesInLine {0};
    char ClearedLineFound {'n'};
    for(int row {0}; row< LineStates.size() ; ++row){
        ColoredTilesInLine = 0;
        for(int col{0}; col < Columns; ++col){
            if(GameGrid[GameGrid.GetIndex(row+2,col)] < GameMatrix::Null){
                ++ColoredTilesInLine;
            }
        }
        if(ColoredTilesInLine == 0){
            LineStates[row] = LineEmpty;
        }else if(ColoredTilesInLine < Columns){
            LineStates[row] = LineUncleared;
        }else {
            LineStates[row] = LineCleared;
            ClearedLineFound = 'y';
        }
    }
    if(ClearedLineFound == 'y'){
        ClearLine();
    }

}

void TetriminoManager::changeTileColor(int index){
    --GameGrid[index+20];
    GameGrid.DataChanged(index);
}

void TetriminoManager::exitGame(){
    GameManager::Instance().ChangeGameState(GameManager::OpeningScreen);
    reset();
}


void TetriminoManager::CalculateFinalDropPositon(){


    for(int i {0};i< FinalDropPosition.size();++i){
        GameGrid.TransperancyMatrix[GameGrid.GetIndex(FinalDropPosition[i])] = GameMatrix::Opaque;
        GameGrid[FinalDropPosition[i]] = GameMatrix::Null;
    };
    GameGrid.DataChanged(FinalDropPosition[0],FinalDropPosition[3]);

    FinalDropPosition = CurrentTetrimino.Positions;
    while(CheckCanMoveDown(FinalDropPosition)){
        for(int i {0};i<FinalDropPosition.size();++i){
            ++FinalDropPosition[i].row;
        }


    }
    for(auto Pos : CurrentTetrimino.Positions){
        for(int i{0}; i<FinalDropPosition.size();++i)
        if(FinalDropPosition[i] == Pos){
            FinalDropPosition[i].row = 0;
            FinalDropPosition[i].column =0;
            break;
        }

    }
for(int i {0};i<FinalDropPosition.size();++i){
        GameGrid.TransperancyMatrix[GameGrid.GetIndex(FinalDropPosition[i])]= GameMatrix::Transperant;
        GameGrid[FinalDropPosition[i]] = CurrentTetrimino.Color;
    }
    GameGrid.DataChanged(FinalDropPosition[0],FinalDropPosition[3]);


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
            ++CurrentTetrimino.Positions[i].row;
            GameGrid[CurrentTetrimino.Positions[i]] = CurrentTetrimino.Color;
        }
        TurnCurPosOpaque();

        if(TetriminoTimer->isActive()){
            TetriminoTimer->stop();
        }
        GameGrid.DataChanged(PreviousPosition,CurrentTetrimino.Positions[3]);
    }



}
//Checks If Passed Tetrimino Can Move Down
const bool TetriminoManager::CheckCanMoveDown(const std::array<Position,4> Positions){
    for(auto Pos : Positions){
        if(Pos.row +1 >= Rows ||GameGrid[GameGrid.GetIndex(Pos.row +1,Pos.column)] < GameMatrix::Null){
            return false;
        }
    }

    return true;
}
//Checks If The Currently Held Tetrimino Can Move Down
const bool TetriminoManager::CheckCanMoveDown(){
    for(auto Pos : CurrentTetrimino.Positions){
        if ( Pos.row +1 >= Rows||GameGrid[GameGrid.GetIndex(Pos.row+1,Pos.column)] <4){
            CanMoveDown = false;
            return false;
        }
    }
    CanMoveDown = true;
    return true;
}

void TetriminoManager::InitTetriminoBag()
{
    static std::mt19937 TetriminoBagGen(Seed);
#ifdef IMode
    TetriminoBag =     {TetriminoType::IPiece,TetriminoType::IPiece,TetriminoType::IPiece,
                    TetriminoType::IPiece,TetriminoType::IPiece,TetriminoType::IPiece,TetriminoType::IPiece};
#else
    TetriminoBag =     {TetriminoType::IPiece,TetriminoType::LPiece,TetriminoType::OPiece,
                    TetriminoType::JPiece,TetriminoType::SPiece,TetriminoType::TPiece,TetriminoType::ZPiece};
#endif
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
    CheckCanMoveDown();
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

void TetriminoManager::TurnCurPosOpaque(){
    Position FirstPos = min(FinalDropPosition[0],CurrentTetrimino.Positions[0]);
    Position LastPos = max(FinalDropPosition[3],CurrentTetrimino.Positions[3]);
    for(auto Pos : CurrentTetrimino.Positions){
        if(GameGrid.TransperancyMatrix[GameGrid.GetIndex(Pos)] == GameMatrix::Transperant){
        GameGrid.TransperancyMatrix[GameGrid.GetIndex(Pos)] = GameMatrix::Opaque;
            for(int i {0} ; i< FinalDropPosition.size();++i){
            if(FinalDropPosition[i] == Pos){
                FinalDropPosition[i].column = 0;
                FinalDropPosition[i].row = 0;
                break;
            }
            }

        }
        }
    GameGrid.DataChanged(FirstPos,LastPos);
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
TurnCurPosOpaque();
CalculateFinalDropPositon();

}
void TetriminoManager::rotateTetrimino(){
    rotateTetrimino(Rotation::None);
}

void TetriminoManager::changeDebugMode(){
    DebugMode = !DebugMode;
    emit DebugModeChanged();
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
    FinalDropPosition.fill({0,0});
    checkLines();
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
