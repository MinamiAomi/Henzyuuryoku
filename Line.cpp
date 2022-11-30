#include "Line.h"
#include "Game.h"
#include "Screen.h"
#include "Container.h"
#include "Debug.h"

Line::Line() : GameObject(nullptr) {
} 
Line::Line(Game* game) : GameObject(game) {
}
void Line::Create() {

	if (mData.mDivision == 1) {
		mData.mControlPos1 = mData.mEndPos;
		mData.mControlPos2 = mData.mStartPos;
	}
	

	for (int index = 0; index < mData.mDivision + 1; index++) {
		float t = static_cast<float>(index) / static_cast<float>(mData.mDivision);
		Vector2 bzierPoint = Vector2Math::CalcCubicBezierCurve(t, mData.mStartPos, mData.mControlPos1, mData.mControlPos2, mData.mEndPos);
		Vector2 diffBzier = Vector2Math::DiffCubicBezierCurve(t, mData.mStartPos, mData.mControlPos1, mData.mControlPos2, mData.mEndPos);
		Vector2 normal = Vector2Math::Magnituded(Vector2Math::Normal(diffBzier), mWidth);
		mDividingPoints.emplace_back(bzierPoint);
		mUpperDividingPoints.emplace_back(normal + bzierPoint);
		mLowerDividingPoints.emplace_back(-normal + bzierPoint);
	}
	for (int index = 0; index < mData.mDivision; index++) {
		Vector2 center = Vector2Math::Mid(mDividingPoints[index], mDividingPoints[index + 1]);
		mCircleColliders.emplace_back(Circle{ center, Vector2Math::Distance(center,mUpperDividingPoints[index]) });
		mColliderColors.emplace_back(Debug::kNotHitColor);
	}
}

void Line::Draw() {
	if (!game()->debug()) {
		for (int index = 0; index < mData.mDivision; index++) {
			int next = index + 1;
			game()->screen()->DrawBox(mUpperDividingPoints[index], mUpperDividingPoints[next], mLowerDividingPoints[index], mLowerDividingPoints[next]);
		}
	}
	else {
		/////////////////////////　デバッグモード //////////////////////////////
		// 始点、終点、制御点に点を表示
		// 始点と制御点１、終点と制御点２にそれぞれをつなぐ線を表示
		// 当たり判定の円を表示
		// 分割点を表示
		constexpr unsigned int kDebugColor1 = 0xFF0000FF;
		constexpr unsigned int kDebugColor2 = 0x0000FFFF;
		constexpr unsigned int kDebugColor3 = 0x00FF00FF;
		constexpr unsigned int kDebugColor4 = 0xFFFF00FF;
		constexpr unsigned int kDebugColor5 = 0xFF00FFFF;
		constexpr float kRaduis = 5.0f;

		if (mData.mDivision != 1) {
		//	for (auto& iter : mDividingPoints) {
		//		game()->screen()->DrawCircle(iter, kRaduis, kDebugColor1);
		//	}
			game()->screen()->DrawLine(mData.mStartPos, mData.mControlPos1, kDebugColor2);
			game()->screen()->DrawLine(mData.mEndPos, mData.mControlPos2, kDebugColor3);
			game()->screen()->DrawCircle(mData.mControlPos1, kRaduis, kDebugColor2);
			game()->screen()->DrawCircle(mData.mControlPos2, kRaduis, kDebugColor3);
		}
		for (int index = 0; index < mData.mDivision; index++) {
			game()->screen()->DrawLine(mUpperDividingPoints[index], mUpperDividingPoints[index + 1], kDebugColor4);
			game()->screen()->DrawLine(mLowerDividingPoints[index], mLowerDividingPoints[index + 1], kDebugColor5);
		//	game()->screen()->DrawCircle(mCircleColliders[index].center, mCircleColliders[index].radius, mColliderColors[index], kFrame);
		}
		//game()->screen()->DrawCircle(mData.mStartPos, kRaduis, kDebugColor2);
		//game()->screen()->DrawCircle(mData.mEndPos, kRaduis, kDebugColor3);
		//////////////////////////////////////////////////////////////////////
	}
}