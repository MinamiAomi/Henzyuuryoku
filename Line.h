#pragma once
#include "GameObject.h"
#include "MyMath.h"
#include <vector>
#include "Circle.h"
#include "Segment.h"

class Line :
    public GameObject
{
public:
    struct Data{
        Vector2 mStartPos; // �n�_
        Vector2 mControlPos1; // ����_�P
        Vector2 mControlPos2; // ����_�Q
        Vector2 mEndPos; // �I�_
        int mDivision; // ������
    };

private:
    static constexpr float mWidth = 3; // ��

    Data mData; // �f�[�^

    std::vector<Vector2> mDividingPoints; // �����_

    std::vector<Vector2> mUpperDividingPoints; // ���
    std::vector<Vector2> mLowerDividingPoints; // ����

    std::vector<Circle> mCircleColliders;
    std::vector<unsigned int> mColliderColors;

public:
    Line();
    Line(class Game* game);
    void Create();
    void Draw();

    void SetData(const Line::Data& data) { mData = data; }

    const std::vector<Circle>& CircleColliders() const { return mCircleColliders; }
    std::vector<unsigned int>& ColliderColors() { return mColliderColors; }
    int DivisionNum() const { return mData.mDivision; }
    Segment DividingSegment(int division) const { return { mDividingPoints[division], mDividingPoints[division + 1] }; }
    const Vector2& DividingPoint(int division) const { return mDividingPoints[division]; }
    Segment UpperDividingSegment(int division) const { return { mUpperDividingPoints[division], mUpperDividingPoints[division + 1] }; }
    Segment LowerDividingSegment(int division) const { return { mLowerDividingPoints[division], mLowerDividingPoints[division + 1] }; }
    Vector2 SectionUpperTilt(int division) const { return mDividingPoints[division + 1] - mDividingPoints[division]; }
    Vector2 SectionLowerTilt(int division) const { return mDividingPoints[division] - mDividingPoints[division + 1]; }
    Vector2 UpperPoint(int division) const { return mUpperDividingPoints[division]; }
    Vector2 LowerPoint(int division) const { return mLowerDividingPoints[division]; }
    static float Width() { return mWidth; }
   
};

