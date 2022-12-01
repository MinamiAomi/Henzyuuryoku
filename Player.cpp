#include "Player.h"
#include "Game.h"
#include "Container.h"
#include "Key.h"
#include "Screen.h"
#include "DeltaTime.h"
#include "Line.h"
#include "Debug.h"
#include "Scene.h"
#include "ControllerInput.h"

Player::Player(class Game* game) :
	GameObject(game)
{}
Player::~Player() {}

void Player::LoadStage() {
	mRespawnPosition = game()->scene()->CurrentStageData().PlayerInitPosition;
	mRespawnTheta = game()->scene()->CurrentStageData().PlayerInitTheta;
	mData.mPosition = mRespawnPosition;
	mData.mTheta = mRespawnTheta;
	mData.mDirection = Vector2Math::MakeDirection(mData.mTheta);
	mGoalAnimation.SetParam(0.0f);
	mCurrentAnime = kWait;
	mAnimeFrameInterval = 0.0f;
}

void Player::Create() {

	mData = game()->container()->player();

	float halfWidth = mData.mWidth / 2.0f;
	float halfHeight = mData.mHeight / 2.0f;
	mVertices = { {
		{ -halfWidth, mData.mHeight },
		{ halfWidth, mData.mHeight },
		{ -halfWidth, 0.0f },
		{ halfWidth, 0.0f }
	} };
	mReversalVertices = {
		{
			{-halfWidth, mData.mHeight},
			{ halfWidth, mData.mHeight },
			{-halfWidth,-mData.mHeight - 4},
			{ halfWidth,-mData.mHeight - 4}
	} };
	mIsGround = false;
	mIsReversal = false;
	mIsRun = false;
	mIsRespawn = true;
	mCircleCollider.center = { 0,halfHeight };;
	mCircleCollider.radius = Vector2Math::Distance(mCircleCollider.center, mVertices[kLeftTop]);
	mColliderColor = Debug::kNotHitColor;
	mGoalAnimation.SetParam(0.0f);
	mAnimeCount = 0;
	mAnimeFrameInterval = 0.0f;
	mCurrentAnime = kWait;
}
void Player::Update() {

	this->Input();
	
	this->Reversal();

	if (mIsReversal == false && mIsRespawn == false) {
		this->Move();
	}
	
	mMatrix.SetAffine(1.0f, mData.mTheta, mData.mPosition);
}

void Player::Draw() {
	mMatrix.SetAffine(1.0f, mData.mTheta, mData.mPosition);
	std::array<Vector2, kVertexNum> drawPoint;
	
	if (mIsReversal == false) {
		for (int i = 0; i < kVertexNum; i++) {
			drawPoint[i] = mVertices[i] * mMatrix;
		}
		if (mCurrentAnime == kRun && mData.mRightInput < 0) {
			game()->screen()->DrawQuad(drawPoint[kRightTop], drawPoint[kLeftTop], drawPoint[kRightBottom], drawPoint[kLeftBottom], mData.mImages[mCurrentAnime].width * mAnimeCount, 0, mData.mImages[mCurrentAnime].width, mData.mImages[mCurrentAnime].height, mData.mImages[mCurrentAnime].handle);
		}
		else {
			game()->screen()->DrawQuad(drawPoint[kLeftTop], drawPoint[kRightTop], drawPoint[kLeftBottom], drawPoint[kRightBottom], mData.mImages[mCurrentAnime].width * mAnimeCount, 0, mData.mImages[mCurrentAnime].width, mData.mImages[mCurrentAnime].height, mData.mImages[mCurrentAnime].handle);
		}
	}
	else {
		for (int i = 0; i < kVertexNum; i++) {
			drawPoint[i] = mReversalVertices[i] * mMatrix;
		}
		game()->screen()->DrawQuad(drawPoint[kLeftTop], drawPoint[kRightTop], drawPoint[kLeftBottom], drawPoint[kRightBottom], mData.mImages[mCurrentAnime].width * mAnimeCount, 0, mData.mImages[mCurrentAnime].width, mData.mImages[mCurrentAnime].height, mData.mImages[mCurrentAnime].handle);
	}

	if (game()->debug()) {
		/////////////////////////　デバッグモード //////////////////////////////
		// 円とプレイヤーの向きのわかる三角形を描画
		constexpr unsigned int debugColor1 = 0x0000FF66;
		constexpr unsigned int debugColor2 = 0x00FF00FF;

		game()->screen()->DrawTriangle(Vector2Math::Magnituded(Vector2Math::Normal(mData.mDirection), mData.mHeight) + mData.mPosition, drawPoint[kLeftBottom], drawPoint[kRightBottom], debugColor1);
		game()->screen()->DrawCircle(CircleColliderCenter(), CirColliderRadius(), mColliderColor, kFrame);
		game()->screen()->DrawLine(drawPoint[kLeftTop], drawPoint[kLeftBottom], debugColor2);
		game()->screen()->DrawLine(drawPoint[kRightTop], drawPoint[kRightBottom], debugColor2);
		/////////////////////////////////////////////////////////////////////
	}
	Debug::Print(game()->debug(), "x : %f  |  y : %f", mData.mPosition.x, mData.mPosition.y);
}

bool Player::GoalAnimation() {
	mAnimeCount = 0;
	mCurrentAnime = kWait;
	if (mGoalAnimation.IsStart()) {
		mGoalAnimation.Set(0.0f, 1 / game()->goal()->PlayerAnimationSecond() * DeltaTime::get(), mData.mPosition, game()->goal()->position());
	}
	mGoalAnimation.SetDeltaParam(1 / game()->goal()->PlayerAnimationSecond() * DeltaTime::get());
	++mGoalAnimation;
	mGoalAnimation.ParamClamp();
	mData.mPosition = mGoalAnimation.Calc();
	mData.mTheta = game()->goal()->theta();
	return mGoalAnimation.IsEnd();
}

void Player::CollisionLines() {
	int hitLineNum = 0;
	std::vector<int> lineDivision;
	std::vector<int> hitLineIndex;
	std::vector<bool> hitUpSide; // true : upper   false : lower
	for (int i = 0; i < game()->lineNum(); i++) {

		std::vector<int> hitDivision;
		for (int div = 0; div < game()->lines()[i].DivisionNum(); div++) {
			if (Circle::Collision(CircleCollider(), game()->lines()[i].CircleColliders()[div]) == true) {
				game()->lines()[i].ColliderColors()[div] = Debug::kHitColor;
				mColliderColor = Debug::kHitColor;
				hitDivision.emplace_back(div);
			}
			else {
				game()->lines()[i].ColliderColors()[div] = Debug::kNotHitColor;
				mColliderColor = Debug::kNotHitColor;
			}
		}
		for (auto& division : hitDivision) {
			bool upSide = true;
			// 分割された線のベクトルとプレイヤーの向きの外積
			float cross_DivVec_PlaDir = Vector2Math::Dot(Vector2Math::Normalized(game()->lines()[i].SectionUpperTilt(division)), mData.mDirection);

			if (cross_DivVec_PlaDir > 0) {
				upSide = true;
			}
			else if (cross_DivVec_PlaDir < 0) {
				upSide = false;
			}
			else {
				upSide = Vector2Math::Cross(Vector2Math::Normalized(game()->lines()[i].DividingSegment(division).CalcVector()), mData.mDirection) > 0 ? true : false;
			}

			// 線の上側と判定をとる
			if (upSide) {
				if (Segment::Collision(LeftSideSegment(), game()->lines()[i].UpperDividingSegment(division)) ||
					Segment::Collision(RightSideSegment(), game()->lines()[i].UpperDividingSegment(division))) {
					
					hitLineNum++;
					lineDivision.emplace_back(division);
					hitLineIndex.emplace_back(i);
					hitUpSide.emplace_back(true);
				}
			}
			// 線の下側と判定をとる
			else {
				if (Segment::Collision(LeftSideSegment(), game()->lines()[i].LowerDividingSegment(division)) ||
					Segment::Collision(RightSideSegment(), game()->lines()[i].LowerDividingSegment(division))) {
					hitLineNum++;
					lineDivision.emplace_back(division);
					hitLineIndex.emplace_back(i);
					hitUpSide.emplace_back(false);
				}
			}
		}
		

	}
	
	mIsGround = hitLineNum == 0 ? false : true;

	for (int i = 0; i < hitLineNum; i++) {

		if (hitUpSide[i]) {
			if (lineDivision.size() >= 2) {
				mData.mTheta = Vector2Math::Angle(game()->lines()[hitLineIndex[i]].UpperPoint(lineDivision[1] + 1) - game()->lines()[hitLineIndex[i]].UpperPoint(lineDivision[0]));
				
			}
			else {
				mData.mTheta = Vector2Math::Angle(game()->lines()[hitLineIndex[i]].SectionUpperTilt(lineDivision[i]));
			}//Segment lineNormal_curPos(mData.mPosition + Vector2Math::Normal(game()->lines()[hitLineIndex[i]].SectionUpperTilt(lineDivision[i])) * mData.mHeight, mData.mPosition);
			//Vector2 pushPosition = Segment::Intersection(lineNormal_curPos, game()->lines()[hitLineIndex[i]].UpperDividingSegment(lineDivision[i]));
			//if (pushPosition.x != Math::Inf && pushPosition.y != Math::Inf) {
			//	mData.mPosition = pushPosition;
			//}
			Segment upperLine = game()->lines()[hitLineIndex[i]].UpperDividingSegment(lineDivision[i]);
			float t = 0;
			Vector2 nearPos = Segment::NearPoint(mData.mPosition, upperLine, t);
			if (0.0f < t && t < 1.0f) {
				mData.mPosition = nearPos + Vector2Math::NegNormal(Vector2Math::MakeDirection(mData.mTheta));
			}

			Debug::Print(game()->debug(), "LineIndex : %d | Section : %d | Side : Upper | t : %f", hitLineIndex[i], lineDivision[i], t);
		}
		else {
			if (lineDivision.size() >= 2) {
				mData.mTheta = Vector2Math::Angle(game()->lines()[hitLineIndex[i]].LowerPoint(lineDivision[0]) - game()->lines()[hitLineIndex[i]].LowerPoint(lineDivision[1] + 1));

			}
			else {
				mData.mTheta = Vector2Math::Angle(game()->lines()[hitLineIndex[i]].SectionLowerTilt(lineDivision[i]));
			}
			//Segment lineNormal_curPos(mData.mPosition + Vector2Math::Normal(game()->lines()[hitLineIndex[i]].SectionLowerTilt(lineDivision[i])) * mData.mHeight, mData.mPosition);
			//Vector2 pushPosition = Segment::Intersection(lineNormal_curPos, game()->lines()[hitLineIndex[i]].LowerDividingSegment(lineDivision[i]));
			//if (pushPosition.x != Math::Inf && pushPosition.y != Math::Inf) {
			//	mData.mPosition = pushPosition;
			//}
			Segment lowerLine = game()->lines()[hitLineIndex[i]].LowerDividingSegment(lineDivision[i]);
			float t = 0;
			Vector2 nearPos = Segment::NearPoint(mData.mPosition, lowerLine, t);
			if (0.0f < t && t < 1.0f) {
 				mData.mPosition = nearPos + Vector2Math::NegNormal(Vector2Math::MakeDirection(mData.mTheta));
			}

			Debug::Print(game()->debug(), "LineIndex : %d | Section : %d | Side : Lower | t : %f", hitLineIndex[i], lineDivision[i], t);
		}
		mData.mDirection = Vector2Math::MakeDirection(mData.mTheta);
		break;
	}
	
}

void Player::Input() {

	if (Controller::isInput() == true) {

		Vector2 controller;
		Controller::getLeftStick(0, &controller.x, &controller.y);

		mData.mRightInput = Math::GetSign(Vector2Math::Dot(mData.mDirection, controller));

	}
	else {

		mData.mRightInput = 0;
		if (Key::IsPressed(DIK_D)) {
			mData.mRightInput += 1;
		}
		if (Key::IsPressed(DIK_A)) {
			mData.mRightInput += -1;
		}

	}
	mData.mSpaceInput = Key::IsTrigger(DIK_SPACE) || Controller::isTrigger(0,kControllerButtonA) ? true : false;

	//if (Key::IsTrigger(DIK_T)) {
	//	mData.mPosition = { 100, 500 };
	//	mData.mDirection = { 1,0 };
	//	Vector2Math::SetZero(game()->screen()->scroll());
	//}

	
	//if (Key::IsPressed(DIK_K)) {
	//	game()->screen()->scroll().x += 200 * DeltaTime::get();
	//}
	//if (Key::IsPressed(DIK_H)) {
	//	game()->screen()->scroll().x += -200 * DeltaTime::get();
	//}
}

void Player::Move() {
	if (game()->debug() == false) {
		Vector2Math::SetZero(mData.mVelocity);
		mData.mDirection = Vector2Math::MakeDirection(mData.mTheta);
		if (mIsGround == true) {
			mData.mVelocity += Vector2Math::Magnituded(mData.mDirection, mData.mMoveSpeed * mData.mRightInput);
		}
		else {
			mData.mVelocity += Vector2Math::Magnituded(Vector2Math::NegNormal(mData.mDirection), mData.mGravitySpeed);
		
		}
		mData.mPosition += mData.mVelocity * DeltaTime::get();

		if (mData.mPosition.x < -(mData.mHeight + mData.mWidth) ||
			game()->container()->window().kWindowWidth + (mData.mHeight + mData.mWidth) < mData.mPosition.x ||
			mData.mPosition.y < -(mData.mHeight + mData.mWidth) ||
			game()->container()->window().kWindowHeight + (mData.mHeight + mData.mWidth) < mData.mPosition.y) {
			mIsRespawn = true;
			mAnimeFrameInterval = mData.mImages[kRespawn].time;
			mData.mPosition = mRespawnPosition;
			mData.mTheta = mRespawnTheta;
			mData.mDirection = Vector2Math::MakeDirection(mData.mTheta);
		}
	}


	else {
		/////////////////////////　デバッグモード //////////////////////////////
		// WSで飛べる LSHIFTで回転
		constexpr float kThetaSpeed = Math::ToRadians(90.0f);
		if (Key::IsPressed(DIK_LSHIFT)) {
			mData.mTheta += kThetaSpeed * DeltaTime::get();
			mData.mTheta = Math::Loop(mData.mTheta, Math::TwoPi);
			Debug::Print("%f", mData.mTheta);

		}
		int UpInput = 0;
		if (Key::IsPressed(DIK_W)) {
			UpInput += 1;
		}
		if (Key::IsPressed(DIK_S)) {
			UpInput += -1;
		}
		Vector2Math::SetZero(mData.mVelocity);
		mData.mDirection = Vector2Math::MakeDirection(mData.mTheta);
		mData.mVelocity += Vector2Math::Magnituded(Vector2Math::Normal(mData.mDirection), mData.mGravitySpeed * UpInput);
		mData.mVelocity += Vector2Math::Magnituded(mData.mDirection, mData.mMoveSpeed * mData.mRightInput);
		mData.mPosition += mData.mVelocity * DeltaTime::get();
		///////////////////////////////////////////////////////////////////////////
	}
}

void Player::Reversal() {
	if (mData.mSpaceInput) {
		if (mIsReversal == false && mIsGround == true && mIsRespawn == false) {
			mIsReversal = true;
			mAnimeFrameInterval = mData.mImages[kReversal].time;
		}
	} 
}

void Player::Animation() {
	mCurrentAnime = kWait;
	if (mIsGround == true) { // 地面にいる
		if (mData.mRightInput != 0) {
			mCurrentAnime = kRun;
		}
	}
	else {
			mCurrentAnime = kFall;
	}
	if (mIsReversal == true) {
		mCurrentAnime = kReversal;
	}
	if (mIsRespawn == true) {
		mCurrentAnime = kRespawn;
	}
	mAnimeFrameInterval += -DeltaTime::get();
	if (mAnimeFrameInterval <= 0.0f) {
		mAnimeFrameInterval = 0.0f;
	}

	switch (mCurrentAnime)
	{
	case Player::kRun:
		if (mAnimeFrameInterval <= 0.0f) {
			mAnimeFrameInterval = mData.mImages[kRun].time;
			mAnimeCount++;
			if (mAnimeCount >= mData.mImages[kRun].frameNum) {
				mAnimeCount = 0;
			}
		}
		break;
	case Player::kFall:
		mAnimeCount = 0;
		break;
	case Player::kReversal:
		if (mAnimeFrameInterval <= 0.0f) {
			mAnimeFrameInterval = mData.mImages[kReversal].time;
			mAnimeCount++;
			if (mAnimeCount >= mData.mImages[kReversal].frameNum) {
				mIsReversal = false;
				mData.mDirection = -mData.mDirection;
				mData.mTheta = Vector2Math::Angle(mData.mDirection);
				mData.mPosition += Vector2Math::Normal(mData.mDirection) * ((Line::Width() - 1) * 2);
				mIsGround = true;
				mCurrentAnime = kWait; 
				mAnimeCount = 0;
			}
		}
		break;
	case Player::kRespawn:
		if (mAnimeFrameInterval <= 0.0f) {
			mAnimeFrameInterval = mData.mImages[kRespawn].time;
			mAnimeCount++;
			if (mAnimeCount >= mData.mImages[kRespawn].frameNum) {
				mIsRespawn = false;
				mIsGround = true;
				mCurrentAnime = kWait;
				mAnimeCount = 0;
			}
		}
		break;
	case Player::kWait:
		mAnimeCount = 0;
	default:

		break;
	}
}