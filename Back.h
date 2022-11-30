#pragma once
#include "GameObject.h"
#include "MyMath.h"
#include <array>
#include "Lerp.h"
class Back :
    public GameObject
{
private:
    class Partical : public GameObject
    {
    private:
        Vector2 mPosition;
        float mSpeed;
        float mRadius;  

    public:
        Partical();
        void Create(const Vector2& pos, float spe, float rad);
        void Update();
        void Draw();
    };

public:
    struct Data
    {
        int imgHandle;
        int imgWidth;
        int imgHeight;

        Vector2 mGracityDirection;

    };

private:
    static constexpr int kParticalNumMax = 50;

    // パーティクルデータ
    std::array<Partical, kParticalNumMax> mParticals;

    Data mData;

public:
    Back(class Game* game);
    ~Back();

    void Create();
    void Update();
    void Draw();

private:
    const Vector2& GravityDrection() const { return mData.mGracityDirection; }
    int imgHandle() const { return mData.imgHandle; }
    int imgWidth() const { return mData.imgWidth; }
    int imgHeight() const { return mData.imgHeight; }
};

