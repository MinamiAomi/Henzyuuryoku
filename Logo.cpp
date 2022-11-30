#include "Logo.h"
#include "Game.h"
#include "Screen.h"
#include "Container.h"
#include "Player.h"

LogoBase::LogoBase(Game* game) : GameObject(game){}
LogoBase::~LogoBase(){}

void LogoBase::Create(const Data& data) {
	mData = data;
}
void LogoBase::Update() {

}
void LogoBase::Draw() {
	Quad scr = mData.mQuad + mData.mPositin;
	game()->screen()->DrawQuad(scr.lt, scr.rt, scr.lb, scr.rb, 0, 0, mData.imgWidth, mData.imgHeight, mData.imgHandle);
}


void SpaceMark::Update() {
	setPos(game()->player()->pos());
}