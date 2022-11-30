#include "Game.h"
#include <Novice.h>
#include "Key.h"
#include "Container.h"
#include "DeltaTime.h"
#include "Scene.h"
#include "Screen.h"
#include "Player.h"
#include "Line.h"
#include "Back.h"
#include "Key.h"
#include "Debug.h"
#include "Logo.h"
#include "Goal.h"

Game::Game() {
	Srand();
	mContainer = new Container();

	// ���C�u�����̏�����
	Novice::Initialize(container()->window().kWindowTitle, container()->window().kWindowWidth, container()->window().kWindowHeight);

	mIsFullScreen = false;
	Novice::SetWindowMode(kWindowed);

	mContainer->Load();

	mScene = new Scene(this);

	mScreen = new Screen(this);

	mBack = new Back(this);

	mTitleLog = new LogoBase(this);
	mNextMark = new LogoBase(this);
	mFallMark = new LogoBase(this);
	mSpaceMark = new SpaceMark(this);
	mPlayer = new Player(this);

	mGoal = new Goal(this);

}

Game::~Game() {

	delete mGoal;

	delete mPlayer;
	delete mSpaceMark;
	delete mFallMark;
	delete mNextMark;
	delete mTitleLog;

	delete mBack;

	delete mScreen;

	delete mScene;

	delete mContainer;

}


void Game::Run() {

	mScene->Create();

	mScreen->Create();

	mBack->Create();

	mTitleLog->Create(mContainer->titleLog());
	mNextMark->Create(mContainer->nextMark());
	mFallMark->Create(mContainer->fallMark());
	mSpaceMark->Create(mContainer->spaceMark());
	mPlayer->Create();

	mGoal->Create();

	mPlayer->LoadStage();
	mGoal->LoadStage();

	Novice::PlayAudio(mContainer->bgmHandle(), 1, 0.01f);

	// �E�B���h�E�́~�{�^�����������܂Ń��[�v
	while (Novice::ProcessMessage() == 0) {
		// �t���[���̊J�n
		Novice::BeginFrame();
		Debug::PrintNumReset();
		// �L�[���͂��󂯎��
		Key::SetState();
		DeltaTime::CalcDeltaTime();

		//if (Key::IsTrigger(DIK_TAB))
		//	mIsDebug ^= true;

		if (Key::IsTrigger(DIK_M)) {
			if (mIsFullScreen == false) {
				Novice::SetWindowMode(kFullscreen);
				mIsFullScreen = true;
			}
			else {
				Novice::SetWindowMode(kWindowed);
				mIsFullScreen = false;
			}

		}
		

		if (debug()) {
			/////////////////////////�@�f�o�b�O���[�h //////////////////////////////
			Debug::Print("DebugMode");
			/////////////////////////////////////////////////////////////////////
		}

		mScene->Proc();
		//Debug::PrintNum();

		// �t���[���̏I��
		Novice::EndFrame();

		// ESC�L�[�������ꂽ�烋�[�v�𔲂���
		if (Key::IsTrigger(DIK_ESCAPE)) {
			break;
		}
	}

	// ���C�u�����̏I��
	Novice::Finalize();

}

std::vector<Line>& Game::lines() { return mScene->CurrentLines(); }
int Game::lineNum() { return mScene->CurrentLines().size(); }
