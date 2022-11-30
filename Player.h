#pragma once
#include "GameObject.h"
#include "MyMath.h"
#include <vector>
#include <array>
#include "Circle.h"
#include "Segment.h"
#include "Lerp.h"

class Player :
    public GameObject
{
public:
	enum ImgType {
		kWait,
		kRun,
		kFall,
		kReversal,
		kRespawn,

		kImgTypeNum
	};
	struct ImgData {
		int handle; // ハンドル
		int width; // 幅
		int height; // 高さ
		int frameNum; // コマ数
		float time; // 次のコマまでの時間
	};
	struct Data	{
		ImgData mImages[kImgTypeNum];
		Vector2 mPosition; // 下辺の中央
		float mTheta; // ラジアン
		Vector2 mVelocity; // 速度
		Vector2 mDirection; // 向き
		float mMoveSpeed;
		float mGravitySpeed;
		int mRightInput; // 移動入力
		bool mSpaceInput; // 反転入力

		float mWidth; // 幅
		float mHeight; // 高さ		
	};

	enum VertexId {
		kLeftTop, // 左上
		kRightTop, // 右上
		kLeftBottom, // 左下
		kRightBottom, // 右下

		kVertexNum
	};

private:
	Data mData;

	Vector2 mRespawnPosition;
	float mRespawnTheta;

	bool mIsGround;
	bool mIsReversal;
	bool mIsRun;
	bool mIsRespawn;

	int mAnimeCount;
	float mAnimeFrameInterval;

	ImgType mCurrentAnime;

	Lerp<Vector2> mGoalAnimation;

	std::array<Vector2, kVertexNum> mVertices;
	std::array<Vector2, kVertexNum> mReversalVertices;
	Circle mCircleCollider;
	Matrix33 mMatrix;

	unsigned int mColliderColor;



public:
	Player(class Game* game);
	~Player();

	void LoadStage();
	void Create();
	void Update();
	void Draw();
	void Animation();


	bool GoalAnimation();
	const Vector2& pos() const { return mData.mPosition; }
	void CollisionLines();

	const Circle CircleCollider() const { return { mCircleCollider.center * mMatrix, mCircleCollider.radius }; }
	const Vector2 CircleColliderCenter() const { return  mCircleCollider.center * mMatrix; }
	float CirColliderRadius() const { return mCircleCollider.radius; }
	Segment LeftSideSegment() const { return { mVertices[kLeftTop] * mMatrix,  mVertices[kLeftBottom] * mMatrix }; }
	Segment RightSideSegment() const { return { mVertices[kRightTop] * mMatrix,  mVertices[kRightBottom] * mMatrix }; }

	const Circle GoalCircleCollider() const { return { mCircleCollider.center * mMatrix, mData.mWidth / 2.0f}; }

	const Vector2& RespawnPosition() const { return mRespawnPosition; }
	float RespawnTheta() const { return mRespawnTheta; }

	const Vector2& Direction() const { return mData.mDirection; }
private:
	void Input();
	void Move();
	void Reversal();
	
	
};

