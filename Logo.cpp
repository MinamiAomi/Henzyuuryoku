#include "Logo.h"
#include "Game.h"
#include "Screen.h"
#include "Container.h"
#include "Player.h"
#include "ControllerInput.h"

LogoBase::LogoBase(Game* game, bool spa) : GameObject(game),space(spa){}
LogoBase::~LogoBase(){}

void LogoBase::Create(const Data& data) {
	mData = data;
}
void LogoBase::Update() {

}
void LogoBase::Draw() {
	if (space == true) {
		Quad scr;
		int wid = 0;
		int hei = 0;
		int han = 0;
		if (game()->isController() == true) {
			scr = mData.mQuad2 + mData.mPositin;
			wid = mData.imgWidth2;
			hei = mData.imgHeight2;
			han = mData.imgHandle2;
		}
		else {
			scr = mData.mQuad + mData.mPositin;
			wid = mData.imgWidth;
			hei = mData.imgHeight;
			han = mData.imgHandle;
		}
		game()->screen()->DrawQuad(scr.lt, scr.rt, scr.lb, scr.rb, 0, 0, wid, hei, han);
	}
	else {
		Quad scr = mData.mQuad + mData.mPositin;
		game()->screen()->DrawQuad(scr.lt, scr.rt, scr.lb, scr.rb, 0, 0, mData.imgWidth, mData.imgHeight, mData.imgHandle);
	}
}


void SpaceMark::Update() {
	setPos(game()->player()->pos());
}