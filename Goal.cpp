#include "Goal.h"
#include "Game.h"
#include "Player.h"
#include "Screen.h"
#include "DeltaTime.h"
#include "Container.h"
#include "Key.h"
#include "Easing.h"
#include "Scene.h"


Goal::Goal(class Game* game) :
	GameObject(game)
{

}
Goal::~Goal(){}

void Goal::Create() {
	mData = game()->container()->goal();
	mIsStartAnimation = false;
	mIsGoal = false;
	mIsStart = false;
	mIsGoalAnimation = false;
	mScale.SetParam(0.0f);
	mScale.SetDeltaParam(1 / mData.mTransitionSecond);
	mScale.SetStart(mData.mQuad * Matrix33::MakeAffine(1.0f, mData.mTheta, mData.mPosition));
	mScale.SetEnd(mData.mMaxScale);
	Load = 0.0f;
}
void Goal::Update(){
	if (Load >= 0.0f) {
		Load -= DeltaTime::get();
	}
	PlayerCollision();
	
	if (mIsGoalAnimation) {
		if (game()->player()->GoalAnimation() == true) {
			mIsGoalAnimation = false;
			mIsGoal = true;
			mScale.SetParam(0.0f);
		}
	}
	if (mIsGoal) {
		if (mScale.IsStart()) {
			mScale.SetStart(mData.mQuad * Matrix33::MakeAffine(1.0f, mTargetTheta, mTargetPosition));
			mScale.SetEnd(mData.mMaxScale);
			mScale.SetParam(0.0f);
		}
		mScale.SetDeltaParam(1 / mData.mTransitionSecond * DeltaTime::get());
		++mScale;
		mScale.ParamClamp();
		if (mScale.IsEnd()) {
			mIsGoal = false;
			mIsStart = true;
			Load = 1.0f;
		}
	}
	if (mIsStart && Load <= 0) {
		if (mScale.IsEnd()) {
			game()->scene()->LoadStageData();
			mScale.SetParam(1.0f);
			mScale.SetStart(mData.mQuad * Matrix33::MakeAffine(1.0f, game()->player()->RespawnTheta(), game()->player()->RespawnPosition()));
		}
		mScale.SetDeltaParam(1 / mData.mTransitionSecond * DeltaTime::get());
		--mScale;
		mScale.ParamClamp();
		if (mScale.IsStart()) {
			mIsStart = false;
			mIsStartAnimation = true;
		}
	}
	if (mIsStartAnimation) {
		if (mScale.IsStart()) {
			mScale.SetEnd(mData.mQuad * Matrix33::MakeAffine(1.0f, mTargetTheta, mTargetPosition));
			mScale.SetStart(mData.mQuad * Matrix33::MakeAffine(1.0f, game()->player()->RespawnTheta(), game()->player()->RespawnPosition()));
		}
		mScale.SetDeltaParam(1 / mData.mStartAnimationSecond * DeltaTime::get());
		++mScale;
		mScale.ParamClamp();
		if (mScale.IsEnd()) {
			mIsStartAnimation = false;
			mIsGoal = false;
			mIsStart = false;
			mIsGoalAnimation = false;
			mScale.SetStart(mData.mQuad * Matrix33::MakeAffine(1.0f, mTargetTheta, mTargetPosition));
			mScale.SetEnd(mData.mMaxScale);
			mScale.SetParam(0.0f);
		}
	}
}
void Goal::Draw(){
	Quad src;
	

	if (mIsGoal || mIsStart || mIsStartAnimation) {
		src = mScale.Calc(Easing::easeInQuint);
	}
	else {
		src = mData.mQuad * Matrix33::MakeAffine(1.0f, mTargetTheta, mTargetPosition);
	}
	game()->screen()->DrawQuad(src, mData.imgWidth * (mIsGoal || mIsStart), 0, mData.imgWidth, mData.imgHeight, mData.imgHandle);
}

void Goal::LoadStage() {
	mTargetPosition = game()->scene()->CurrentStageData().GoalPosition;
	mTargetTheta = game()->scene()->CurrentStageData().GoalTheta;
	mIsGoal = false;
	mScale.SetStart(mData.mQuad * Matrix33::MakeAffine(1.0f, mTargetTheta, mTargetPosition));
}

void Goal::PlayerCollision(){
	if (IsAnimation() == false) {
		Circle pla = game()->player()->GoalCircleCollider();
		if (Circle::Collision(pla, CircleCollider())) {
			mIsGoalAnimation = true;
		}
	}
}