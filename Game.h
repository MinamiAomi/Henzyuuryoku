#pragma once
#include <vector>
#include "Line.h"

class Game
{
// コンテナ
private:
	class Container* mContainer;

public:
	const class Container* container() { return mContainer; }

private:
	// シーンポインタ
	class Scene* mScene;

public:
	class Scene* scene() { return mScene; }

private:
	class Screen* mScreen;

public:
	class Screen* screen() { return mScreen; }

private:
	class Back* mBack;

public:
	class Back* back() { return mBack; }

private:
	class LogoBase* mTitleLog;
	class LogoBase* mNextMark;
	class LogoBase* mFallMark;
	class SpaceMark* mSpaceMark;
public:
	class LogoBase* titleLog() { return mTitleLog; }
	class LogoBase* nextMark() { return mNextMark; }
	class LogoBase* fallMark() { return mFallMark; }
	class SpaceMark* spaceMark() { return mSpaceMark; }
private:
	class Player* mPlayer;

public:
	class Player* player() { return mPlayer; }

private:
	class Goal* mGoal;

public:
	class Goal* goal() { return mGoal; }

public:
	std::vector<Line>& lines();
	int lineNum();

public:
	Game();
	~Game();

	void Run();

private:
	bool mIsDebug;
	bool mIsFullScreen;
public:
	bool debug() const { return mIsDebug; }

};

