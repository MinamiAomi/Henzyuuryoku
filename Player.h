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
		int handle; // �n���h��
		int width; // ��
		int height; // ����
		int frameNum; // �R�}��
		float time; // ���̃R�}�܂ł̎���
	};
	struct Data	{
		ImgData mImages[kImgTypeNum];
		Vector2 mPosition; // ���ӂ̒���
		float mTheta; // ���W�A��
		Vector2 mVelocity; // ���x
		Vector2 mDirection; // ����
		float mMoveSpeed;
		float mGravitySpeed;
		int mRightInput; // �ړ�����
		bool mSpaceInput; // ���]����

		float mWidth; // ��
		float mHeight; // ����		
	};

	enum VertexId {
		kLeftTop, // ����
		kRightTop, // �E��
		kLeftBottom, // ����
		kRightBottom, // �E��

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

