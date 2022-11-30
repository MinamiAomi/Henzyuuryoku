#pragma once
#include "GameObject.h"
#include "Quad.h"
#include "Lerp.h"
#include "Circle.h"
class Goal :
    public GameObject
{

public:
	

	struct Data
	{
		int imgHandle;
		int imgWidth;
		int imgHeight;

		Vector2 mPosition;
		float mTheta;

		Quad mMaxScale;
		Quad mQuad;

		float mGoalAnimationSecond;
		float mStartAnimationSecond;
		float mTransitionSecond;

		Vector2 mCollisionCenter;
		float mCollisionRadius;
	};

private:
	Data mData;

	Vector2 mTargetPosition;
	float mTargetTheta;

	Lerp<Quad> mScale;

	bool mIsGoalAnimation;
	bool mIsStartAnimation;
	bool mIsGoal;
	bool mIsStart;
	float Load;

public:
	Goal(class Game* game);
	~Goal();

	void Create();
	void Update();
	void Draw();
	void LoadStage();

	void PlayerCollision();

	bool IsAnimation() { return mIsGoalAnimation || mIsGoal || mIsStart || mIsStartAnimation; }
	bool IsFead() { return  mIsGoal || mIsStart; }

	const Vector2& position() const { return mTargetPosition; }
	float theta() const { return mTargetTheta; }

	float PlayerAnimationSecond() const { return mData.mGoalAnimationSecond; }
private:
	Circle CircleCollider() const { return { mData.mCollisionCenter * Matrix33::MakeAffine(1.0f, mTargetTheta,mTargetPosition), mData.mCollisionRadius }; }
};

