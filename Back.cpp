#include "Back.h"
#include <Novice.h>
#include "Game.h"
#include "DeltaTime.h"
#include "Player.h"
#include "Container.h"
#include "Screen.h"
#include "Key.h"
#include "Debug.h"

Back::Partical::Partical() :GameObject(nullptr){}

void Back::Partical::Create(const Vector2& pos, float spe, float rad) {
	mPosition = pos;
	mSpeed = spe;
	mRadius = rad;
}
void Back::Partical::Update() {
	
	mPosition += game()->back()->GravityDrection() * mSpeed * DeltaTime::get();
	if (mPosition.x < -mRadius) {
		mPosition.x = game()->container()->window().kWindowWidth + mRadius;
	}
	if (mPosition.x > game()->container()->window().kWindowWidth + mRadius) {
		mPosition.x = -mRadius;
	}
	if (mPosition.y < -mRadius) {
		mPosition.y = game()->container()->window().kWindowHeight + mRadius;
	}
	if (mPosition.y > game()->container()->window().kWindowHeight + mRadius) {
		mPosition.y = -mRadius;
	}
	

}
void Back::Partical::Draw() {
	//game()->screen()->DrawCircle(mPosition, mRadius);
	float scale = mRadius / game()->back()->imgWidth();
	game()->screen()->DrawSpriteRect(Vector2{ -mRadius,mRadius } + mPosition, 0, 0, game()->back()->imgWidth(), game()->back()->imgHeight(), game()->back()->imgHandle(), scale, scale,0.0f,0xFFFFFF88);
}

Back::Back(Game* game):
	GameObject(game)
{
	for (auto& iter : mParticals) {
		iter.SetGame(game);
	}
}

Back::~Back()
{
}

void Back::Create()
{
	mData = game()->container()->back();
	int width = game()->container()->window().kWindowWidth;
	int height = game()->container()->window().kWindowHeight;
	for (auto& iter : mParticals) {
		float t = Random();
		float r = Math::Lerp(t, 50, 100);
		float s = Math::Lerp(t, 30, 60);
		iter.Create({ (float)Random(0,width),(float)Random(0,height) }, s, r / 10.0f);
	}
}

void Back::Update()
{
	mData.mGracityDirection = Vector2Math::NegNormal(game()->player()->Direction());
	for (auto& iter : mParticals) {
			iter.Update();
	}
}

void Back::Draw()
{
	// îwåiçïìhÇË
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x000000FF, kFillModeSolid);

	for (auto& iter : mParticals) {
		iter.Draw();
	}
}