#include "Container.h"
#include "Game.h"
#include <Novice.h>
#include "Line.h"
Container::Container() :
	mWindowData({ "1126_辺重力", 1280, 720 })
{}

Container::~Container(){}

void Container::Load() {
	setData();
	setStageData();
	setImages();
}

void Container::setData() {
	mGameData.screen.mOrigin = { 0,720 };
	mGameData.screen.mScroll = { 0,0 };
	mGameData.screen.isCameraShake = false;
	mGameData.screen.mMatrix.SetIdentity();
	mGameData.screen.mColor = 0xFFFFFFFF;
	
	mGameData.titleLog.imgWidth = 1280;
	mGameData.titleLog.imgHeight = 720;
	mGameData.titleLog.mPositin = { 0,0 };
	mGameData.titleLog.mQuad = {
		{0,(float)mGameData.titleLog.imgHeight},
		{(float)mGameData.titleLog.imgWidth,(float)mGameData.titleLog.imgHeight},
		{0,0},
		{(float)mGameData.titleLog.imgWidth,0}
	};

	mGameData.nextMark.imgWidth = 128;
	mGameData.nextMark.imgHeight = 128;
	mGameData.nextMark.mPositin = { 830,202 };
	mGameData.nextMark.mQuad = {
		{-mGameData.nextMark.imgWidth / 4.0f,(float)mGameData.nextMark.imgHeight / 2.0f},
		{mGameData.nextMark.imgWidth / 4.0f,(float)mGameData.nextMark.imgHeight / 2.0f},
		{-mGameData.nextMark.imgWidth / 4.0f,0},
		{mGameData.nextMark.imgWidth / 4.0f,0}
	};

	mGameData.fallMark.imgWidth = 256;
	mGameData.fallMark.imgHeight = 256;
	mGameData.fallMark.mPositin = { 640,198 };
	mGameData.fallMark.mQuad = {
		{-mGameData.nextMark.imgWidth / 4.0f,0},
		{mGameData.nextMark.imgWidth / 4.0f,0},
		{-mGameData.nextMark.imgWidth / 4.0f,-(float)mGameData.nextMark.imgHeight / 2.0f},
		{mGameData.nextMark.imgWidth / 4.0f,-(float)mGameData.nextMark.imgHeight / 2.0f}
	};

	mGameData.space.imgWidth = 224;
	mGameData.space.imgHeight = 96;
	mGameData.space.mPositin = { 0,0 };
	mGameData.space.mQuad = {
		{-mGameData.space.imgWidth / 4.0f,(float)mGameData.space.imgHeight / 4.0f + 100},
		{mGameData.space.imgWidth / 4.0f,(float)mGameData.space.imgHeight / 4.0f + 100},
		{-mGameData.space.imgWidth / 4.0f, 90},
		{mGameData.space.imgWidth / 4.0f, 90}
	};

	mGameData.back.imgWidth = 128;
	mGameData.back.imgHeight = 128;

	mGameData.player.mPosition = { 1200,500 };
	mGameData.player.mTheta = 0.0f;
	mGameData.player.mVelocity = { 0,0 };
	mGameData.player.mDirection = Vector2Math::MakeDirection(mGameData.player.mTheta);
	mGameData.player.mMoveSpeed = 240.0f;
	mGameData.player.mGravitySpeed = 360.0f;
	mGameData.player.mRightInput = 0;
	mGameData.player.mSpaceInput = false;

	mGameData.player.mWidth = 30.0f;
	mGameData.player.mHeight = 60.0f;
	
	mGameData.goal.imgWidth = 96;
	mGameData.goal.imgHeight = 144;
	mGameData.goal.mPosition = { 900,200 };
	mGameData.goal.mTheta = 0.0f;
	mGameData.goal.mMaxScale = {
		{0,(float)mWindowData.kWindowHeight},
		{(float)mWindowData.kWindowWidth,(float)mWindowData.kWindowHeight},
		{0,0},
		{(float)mWindowData.kWindowWidth,0}
	};
	float goalWidth = mGameData.player.mWidth * 1.5;
	float goalHeight = mGameData.player.mHeight * 1.125;
	mGameData.goal.mQuad = {
		{ -goalWidth / 2, goalHeight},
		{ goalWidth / 2, goalHeight},
		{ -goalWidth / 2, 0},
		{ goalWidth / 2,0}
	};
	mGameData.goal.mGoalAnimationSecond = 0.1f;
	mGameData.goal.mTransitionSecond = 0.5f;
	mGameData.goal.mStartAnimationSecond = 0.5f;
	mGameData.goal.mCollisionCenter = { 0,goalHeight / 2.0f };
	mGameData.goal.mCollisionRadius = goalWidth / 2.0f;

	mGameData.scene.mStageNumber = Scene::kTitle;

	//mGameData.lines.emplace_back(Line::Data{ {200, 200}, {}, {}, {1080,200}, 1 });
	//mGameData.lines.emplace_back(Line::Data{ {600, 700}, {}, {}, {600,500}, 1 });
	//mGameData.lines.emplace_back(Line::Data{ {200, 200}, {0,600}, {700,400}, {700,100}, 30});
	//mGameData.lines.emplace_back(Line::Data{ {800, 100}, {}, {}, {800,500}, 1 });
}

void Container::setImages() {
	mGameData.titleLog.imgHandle = Novice::LoadTexture("./resource/images/log/title.png");
	mGameData.nextMark.imgHandle = Novice::LoadTexture("./resource/images/next.png");
	mGameData.fallMark.imgHandle = Novice::LoadTexture("./resource/images/fallMark.png");
	mGameData.space.imgHandle = Novice::LoadTexture("./resource/images/space.png");
	mGameData.back.imgHandle = Novice::LoadTexture("./resource/images/partical.png");
	mGameData.goal.imgHandle = Novice::LoadTexture("./resource/images/goal.png");
	
	mBGMhandle = Novice::LoadAudio("./resource/audio/bgm.mp3");
	
	mGameData.player.mImages[Player::kWait].handle = Novice::LoadTexture("./resource/images/human/wait.png");
	mGameData.player.mImages[Player::kWait].width = 64;
	mGameData.player.mImages[Player::kWait].height = 128;
	mGameData.player.mImages[Player::kWait].frameNum = 1;
	mGameData.player.mImages[Player::kWait].time = 0;

	mGameData.player.mImages[Player::kRun].handle = Novice::LoadTexture("./resource/images/human/run.png");
	mGameData.player.mImages[Player::kRun].width = 64;
	mGameData.player.mImages[Player::kRun].height = 128;
	mGameData.player.mImages[Player::kRun].frameNum = 6;
	mGameData.player.mImages[Player::kRun].time = 0.1f;

	mGameData.player.mImages[Player::kFall].handle = Novice::LoadTexture("./resource/images/human/fall.png");
	mGameData.player.mImages[Player::kFall].width = 64;
	mGameData.player.mImages[Player::kFall].height = 128;
	mGameData.player.mImages[Player::kFall].frameNum = 1;
	mGameData.player.mImages[Player::kFall].time = 0;

	mGameData.player.mImages[Player::kReversal].handle = Novice::LoadTexture("./resource/images/human/reversal.png");
	mGameData.player.mImages[Player::kReversal].width = 64;
	mGameData.player.mImages[Player::kReversal].height = 276;
	mGameData.player.mImages[Player::kReversal].frameNum = 40;
	mGameData.player.mImages[Player::kReversal].time = 0.01f;

	mGameData.player.mImages[Player::kRespawn].handle = Novice::LoadTexture("./resource/images/human/respawn.png");
	mGameData.player.mImages[Player::kRespawn].width = 64;
	mGameData.player.mImages[Player::kRespawn].height = 128;
	mGameData.player.mImages[Player::kRespawn].frameNum = 30;
	mGameData.player.mImages[Player::kRespawn].time = 0.01f;
}

void Container::setStageData() {
	
	constexpr float dg0 = Math::ToRadians(0.0f);
	constexpr float dg180 = Math::ToRadians(180.0f);
	// タイトル

	mGameData.scene.mStageDatas[Scene::kTitle].PlayerInitPosition = { 640,202 };
	mGameData.scene.mStageDatas[Scene::kTitle].PlayerInitTheta = 0.0f;
	mGameData.scene.mStageDatas[Scene::kTitle].GoalPosition = { 900,202 };
	mGameData.scene.mStageDatas[Scene::kTitle].GoalTheta = 0.0f;
	mGameData.scene.mStageDatas[Scene::kTitle].Lines.emplace_back(Line::Data{ {200, 200}, {}, {}, {1080,200}, 1 });

	// ステージ１ 

	mGameData.scene.mStageDatas[Scene::kStage1].PlayerInitPosition = { 200,202 };
	mGameData.scene.mStageDatas[Scene::kStage1].PlayerInitTheta = 0.0f;
	mGameData.scene.mStageDatas[Scene::kStage1].GoalPosition = { 900,500 + 2 };
	mGameData.scene.mStageDatas[Scene::kStage1].GoalTheta = dg0;
	mGameData.scene.mStageDatas[Scene::kStage1].Lines.emplace_back(Line::Data{ {100, 200}, {}, {}, {640,200}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage1].Lines.emplace_back(Line::Data{ {640, 500}, {}, {}, {1180,500}, 1 });

	// ステージ２

	mGameData.scene.mStageDatas[Scene::kStage2].PlayerInitPosition = { 75,362 };
	mGameData.scene.mStageDatas[Scene::kStage2].PlayerInitTheta = 0.0f;
	mGameData.scene.mStageDatas[Scene::kStage2].GoalPosition = { 1130,362 };
	mGameData.scene.mStageDatas[Scene::kStage2].GoalTheta = dg0;
	mGameData.scene.mStageDatas[Scene::kStage2].Lines.emplace_back(Line::Data{ {50, 360}, {}, {}, {200,360}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage2].Lines.emplace_back(Line::Data{ {200, 500}, {}, {}, {500,500}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage2].Lines.emplace_back(Line::Data{ {40, 100}, {}, {}, {600,100}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage2].Lines.emplace_back(Line::Data{ {50, 700}, {}, {}, {1180,700}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage2].Lines.emplace_back(Line::Data{ {500, 200}, {}, {}, {700,200}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage2].Lines.emplace_back(Line::Data{ {640, 360}, {}, {}, {800,360}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage2].Lines.emplace_back(Line::Data{ {840, 600}, {}, {}, {1080,600}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage2].Lines.emplace_back(Line::Data{ {750, 150}, {}, {}, {900,150}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage2].Lines.emplace_back(Line::Data{ {880, 50}, {}, {}, {1140,50}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage2].Lines.emplace_back(Line::Data{ {1080, 360}, {}, {}, {1180,360}, 1 });
	// ステージ３

	mGameData.scene.mStageDatas[Scene::kStage3].PlayerInitPosition = { 225,362 };
	mGameData.scene.mStageDatas[Scene::kStage3].PlayerInitTheta = 0.0f;
	mGameData.scene.mStageDatas[Scene::kStage3].GoalPosition = { 460,498 };
	mGameData.scene.mStageDatas[Scene::kStage3].GoalTheta = Math::ToRadians(180.0f);
	mGameData.scene.mStageDatas[Scene::kStage3].Lines.emplace_back(Line::Data{ {150, 360}, {}, {}, {300,360}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage3].Lines.emplace_back(Line::Data{ {200, 100}, {}, {}, {400,300}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage3].Lines.emplace_back(Line::Data{ {500, 300}, {}, {}, {500,100}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage3].Lines.emplace_back(Line::Data{ {70, 200}, {}, {}, {70,600}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage3].Lines.emplace_back(Line::Data{ {220, 550}, {}, {}, {290,650}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage3].Lines.emplace_back(Line::Data{ {640, 220}, {}, {}, {750,220}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage3].Lines.emplace_back(Line::Data{ {500, 300}, {}, {}, {500,100}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage3].Lines.emplace_back(Line::Data{ {700, 150}, {}, {}, {820,20}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage3].Lines.emplace_back(Line::Data{ {500, 700}, {}, {}, {700,600}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage3].Lines.emplace_back(Line::Data{ {1230, 450}, {}, {}, {1230,350}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage3].Lines.emplace_back(Line::Data{ {1180, 50}, {}, {}, {1230,150}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage3].Lines.emplace_back(Line::Data{ {1180, 700}, {}, {}, {1230,600}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage3].Lines.emplace_back(Line::Data{ {420, 500}, {}, {}, {500,500}, 1 });
	// ステージ４

	mGameData.scene.mStageDatas[Scene::kStage4].PlayerInitPosition = { 150,202 };
	mGameData.scene.mStageDatas[Scene::kStage4].PlayerInitTheta = Math::ToRadians(60.0f);
	mGameData.scene.mStageDatas[Scene::kStage4].GoalPosition = { 1180 - 3,300 };
	mGameData.scene.mStageDatas[Scene::kStage4].GoalTheta = Math::ToRadians(90.0f);
	mGameData.scene.mStageDatas[Scene::kStage4].Lines.emplace_back(Line::Data{ {100, 100}, {300, 700}, {1100, 700}, {950,300}, 30 });
	mGameData.scene.mStageDatas[Scene::kStage4].Lines.emplace_back(Line::Data{ {1180, 400}, {}, {}, {1180,200}, 1 });

	// ステージ５

	mGameData.scene.mStageDatas[Scene::kStage5].PlayerInitPosition = { 640,14 };
	mGameData.scene.mStageDatas[Scene::kStage5].PlayerInitTheta = 0.0f;
	mGameData.scene.mStageDatas[Scene::kStage5].GoalPosition = { 640,333 };
	mGameData.scene.mStageDatas[Scene::kStage5].GoalTheta = Math::ToRadians(0.0f);
	mGameData.scene.mStageDatas[Scene::kStage5].Lines.emplace_back(Line::Data{ {540, 400}, {140,200}, {1140,200}, {740,400}, 20 });
	mGameData.scene.mStageDatas[Scene::kStage5].Lines.emplace_back(Line::Data{ {540, 150}, {-460,600}, {1740,600}, {740,150}, 30 });
	mGameData.scene.mStageDatas[Scene::kStage5].Lines.emplace_back(Line::Data{ {540, 650}, {-1060,-200}, {2340,-200}, {740,650}, 30 });
	mGameData.scene.mStageDatas[Scene::kStage5].Lines.emplace_back(Line::Data{ {580, 330}, {}, {}, {700,330}, 1 });
	
	// ステージ６

	mGameData.scene.mStageDatas[Scene::kStage6].PlayerInitPosition = { 1210,648 };
	mGameData.scene.mStageDatas[Scene::kStage6].PlayerInitTheta = Math::ToRadians(180.0f);
	mGameData.scene.mStageDatas[Scene::kStage6].GoalPosition = { 1210,72 };
	mGameData.scene.mStageDatas[Scene::kStage6].GoalTheta = Math::ToRadians(0.0f);
	mGameData.scene.mStageDatas[Scene::kStage6].Lines.emplace_back(Line::Data{ {1180, 650}, {}, {}, {1240,650}, 1 });

	mGameData.scene.mStageDatas[Scene::kStage6].Lines.emplace_back(Line::Data{ {600, 550}, {720,720}, {950,720}, {850, 550}, 20 });
	mGameData.scene.mStageDatas[Scene::kStage6].Lines.emplace_back(Line::Data{ {900, 380}, {1030,380}, {1270,200}, {1230, 400}, 20 });
	mGameData.scene.mStageDatas[Scene::kStage6].Lines.emplace_back(Line::Data{ {400, 250}, {}, {}, {910, 250}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage6].Lines.emplace_back(Line::Data{ {300, 200}, {200,450}, {430,550}, {500, 360}, 20 });
	mGameData.scene.mStageDatas[Scene::kStage6].Lines.emplace_back(Line::Data{ {75, 70}, {75, 500}, {200, 800}, {300, 500}, 30 });
	mGameData.scene.mStageDatas[Scene::kStage6].Lines.emplace_back(Line::Data{ {1180, 70}, {}, {}, {1240,70}, 1 });

	// ステージ７

	mGameData.scene.mStageDatas[Scene::kStage7].PlayerInitPosition = { 350,362 };
	mGameData.scene.mStageDatas[Scene::kStage7].PlayerInitTheta = 0.0f;
	mGameData.scene.mStageDatas[Scene::kStage7].GoalPosition = { 930,363 };
	mGameData.scene.mStageDatas[Scene::kStage7].GoalTheta = Math::ToRadians(0.0f);
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {320, 360}, {}, {}, {380,360}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {270, 460}, {}, {}, {430,460}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {270, 260}, {}, {}, {430,260}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {270, 360}, {0,360}, {100, 550}, {120,650}, 20 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {140,260}, {140,200}, {200,100}, {270,50}, 10 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {400, 680}, {}, {}, {460,700}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {430, 360}, {550, 360}, {550, 400}, {510,500}, 10 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {640, 700}, {}, {}, {850,700}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {585, 150}, {590,70}, {600,60}, {700,20}, 10 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {1130, 180}, {}, {}, {1200,300}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {930, 650}, {}, {}, {930,800}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {1000, 700}, {}, {}, {1210,700}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {1180, 70}, {}, {}, {1250,100}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {0, 650}, {}, {}, {25,720}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {1280, 650}, {}, {}, {1280 - 25,720}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {1280, 70}, {}, {}, {1280 - 25,0}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {0, 70}, {}, {}, {25,0}, 1 });
	mGameData.scene.mStageDatas[Scene::kStage7].Lines.emplace_back(Line::Data{ {900, 360}, {}, {}, {960,360}, 1 });

	// クリア

	mGameData.scene.mStageDatas[Scene::kClear].PlayerInitPosition = { 640,202 };
	mGameData.scene.mStageDatas[Scene::kClear].PlayerInitTheta = 0.0f;
	mGameData.scene.mStageDatas[Scene::kClear].GoalPosition = { 900,202 };
	mGameData.scene.mStageDatas[Scene::kClear].GoalTheta = 0.0f;
	mGameData.scene.mStageDatas[Scene::kClear].Lines.emplace_back(Line::Data{ {200, 200}, {}, {}, {1080,200}, 1 });
	
}


