#pragma once
#include "Screen.h"
#include "Logo.h"
#include "Player.h"
#include "Back.h"
#include "Goal.h"
#include "Scene.h"
class Container
{

private:
	// ウィンドウデータ
	struct WindowData {
		const char* kWindowTitle;	// タイトル
		const int kWindowWidth;		// 幅
		const int kWindowHeight;	// 高さ
	};

	// ゲームデータ
	struct GameData	{
		Screen::Data screen;
		Scene::Data scene;
		LogoBase::Data titleLog;
		LogoBase::Data nextMark;
		LogoBase::Data fallMark;
		LogoBase::Data space;
		Back::Data back;
		Player::Data player;
		Goal::Data goal;
	};

	
	

private:
	WindowData mWindowData;
	GameData mGameData;
	int mBGMhandle;

// ゲッター
public:
	const WindowData& window() const { return mWindowData; }

	const Screen::Data& screen() const { return mGameData.screen; }
	const Scene::Data& scene() const { return mGameData.scene; }
	const LogoBase::Data& titleLog() const { return mGameData.titleLog; }
	const LogoBase::Data& nextMark() const { return mGameData.nextMark; }
	const LogoBase::Data& fallMark() const { return mGameData.fallMark; }
	const LogoBase::Data& spaceMark() const { return mGameData.space; }
	const Back::Data back() const { return mGameData.back; }
	const Player::Data& player() const { return mGameData.player; }
	const Goal::Data& goal() const { return mGameData.goal; }
	int bgmHandle() const { return mBGMhandle; }

public:
	Container();
	~Container();

	void Load();

private:
	void setData();
	void setImages();
	void setStageData();
};

