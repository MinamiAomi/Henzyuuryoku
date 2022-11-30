#include "Scene.h"
#include "Screen.h"
#include "Game.h"
#include <Novice.h>
#include "Player.h"
#include "Line.h"
#include "Back.h"
#include "Logo.h"
#include "Goal.h"
#include "Container.h"
#include "Key.h"

Scene::Scene(class Game* game) : 
	GameObject(game)
{

}
Scene::~Scene(){}

void Scene::Proc() {
	this->Update();
	game()->screen()->CalcMatrix();
	this->Draw();
}

void Scene::Create() {
	mData = game()->container()->scene();
	for (int i = 0; i < mData.mStageDatas.size(); i++) {
		for (int j = 0; j < mData.mStageDatas[i].Lines.size(); j++) {
			mLines[i].emplace_back(game());
			mLines[i][j].SetData(mData.mStageDatas[i].Lines[j]);
			mLines[i][j].Create();
		}
	}

}

void Scene::Init() {

}

void Scene::Update() {
	DebugLoad();
	if (game()->goal()->IsAnimation() == false) {
		game()->player()->Update();
		game()->player()->CollisionLines();
		game()->player()->Animation();
	}
	if (mData.mStageNumber == kStage1) {
		game()->spaceMark()->Update();
	}
	game()->back()->Update();
	game()->goal()->Update();
	
}

void Scene::Draw() {
	game()->back()->Draw();
	for (auto& iter : CurrentLines()) {
		iter.Draw();
	}
	if (!game()->goal()->IsFead()) {
		game()->player()->Draw();
	}
	if (mData.mStageNumber == kTitle) {
		game()->titleLog()->Draw();
		game()->nextMark()->Draw();
	}
	switch (mData.mStageNumber)
	{
	case kTitle:
		game()->titleLog()->Draw();
		game()->nextMark()->Draw();
		break;
	case kStage1:
		game()->fallMark()->Draw();
		game()->spaceMark()->Draw();
	default:
		break;
	}
	game()->goal()->Draw();
}

void Scene::LoadStageData() {
	if (mData.mStageNumber != kClear) {
		mData.mStageNumber = (Stage)(mData.mStageNumber + 1);
	}
	else {
		mData.mStageNumber = kTitle;
	}

	game()->player()->LoadStage();
	game()->goal()->LoadStage();
}

void Scene::DebugLoad() {
	Stage temp = mData.mStageNumber;
	if (Key::IsPressed(DIK_TAB) && Key::IsPressed(DIK_LSHIFT)) {
		if (Key::IsTrigger(DIK_T)) {
			mData.mStageNumber = kTitle;
		}
		else if (Key::IsTrigger(DIK_1)) {
			mData.mStageNumber = kStage1;
		}
		else if (Key::IsTrigger(DIK_2)) {
			mData.mStageNumber = kStage2;
		}
		else if (Key::IsTrigger(DIK_3)) {
			mData.mStageNumber = kStage3;
		}
		else if (Key::IsTrigger(DIK_4)) {
			mData.mStageNumber = kStage4;
		}
		else if (Key::IsTrigger(DIK_5)) {
			mData.mStageNumber = kStage5;
		}
		else if (Key::IsTrigger(DIK_6)) {
			mData.mStageNumber = kStage6;
		}
		else if (Key::IsTrigger(DIK_7)) {
			mData.mStageNumber = kStage7;
		}
		else if (Key::IsTrigger(DIK_C)) {
			mData.mStageNumber = kClear;
		}
	}

	if (temp != mData.mStageNumber) {
		game()->player()->LoadStage();
		game()->goal()->LoadStage();
	}
}