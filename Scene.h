#pragma once
#include "GameObject.h"
#include <array>
#include "MyMath.h"
#include "Line.h"
class Scene :
    public GameObject
{
public:
    enum Stage {
        kTitle,
        kStage1,
        kStage2,
        kStage3,
        kStage4,
        kStage5,
        kStage6,
        kStage7,
        kClear,

        kStageNum
    };

    struct StageData
    {
        Vector2 PlayerInitPosition;
        float PlayerInitTheta;

        Vector2 GoalPosition;
        float GoalTheta;

        std::vector<Line::Data> Lines;
    };

    struct Data
    {
        std::array<StageData, kStageNum> mStageDatas;
        Stage mStageNumber;
    };

private:
    
    Data mData;

    std::array<std::vector<Line>,kStageNum> mLines;

public:
    Scene(class Game* game);
    ~Scene();

    void Proc();

    void Create();
    void Init();
    void Update();
    void Draw();

    void LoadStageData();
    std::vector<Line>& CurrentLines() { return mLines[mData.mStageNumber]; }

    int StageNumber() const { return (int)mData.mStageNumber; }
    const StageData& CurrentStageData() const { return mData.mStageDatas[mData.mStageNumber]; }
private:
    void DebugLoad();
};

