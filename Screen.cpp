#include "Screen.h"
#include <Novice.h>
#include "Game.h"
#include "Container.h"

Screen::Screen(Game* game):
	GameObject(game)
{}
Screen::~Screen(){}

void Screen::Create(){
	mData = game()->container()->screen();
}

void Screen::Init(){
	mData = game()->container()->screen();
}

void Screen::Update(){}
void Screen::CalcMatrix(){
	mData.mMatrix.SetIdentity();
	mData.mMatrix.MultiplyTranslation({ -mData.mScroll.x,mData.mScroll.y });
	mData.mMatrix.MultiplyScaling(1.0f, -1.0f);
	mData.mMatrix.MultiplyTranslation(mData.mOrigin);
}

Vector2 Screen::MousePosition() {
	int x, y;
	Novice::GetMousePosition(&x, &y);
	Vector2 temp((float)x, (float)y);
	temp += -mData.mScroll;
	temp.y *= -1;
	return temp;
}

void Screen::DrawBox(const Vector2& vec, float width, float height, float theta, unsigned int color, ShapeFillMode fillmode) const{
	Vector2 scr = Conversion(vec);
	Novice::DrawBox((int)scr.x, (int)scr.y, (int)width, (int)height, -theta, color, static_cast<FillMode>(fillmode));
}
void Screen::DrawBox(const Vector2& vec1, const Vector2& vec2, const Vector2& vec3, const Vector2& vec4, unsigned int color, ShapeFillMode fillmode) const {
	Vector2 scrvec1 = Conversion(vec1);
	Vector2 scrvec2 = Conversion(vec2);
	Vector2 scrvec3 = Conversion(vec3);
	Vector2 scrvec4 = Conversion(vec4);
	Novice::DrawBox((int)scrvec1.x, (int)scrvec1.y, (int)scrvec2.x, (int)scrvec2.y, (int)scrvec3.x, (int)scrvec3.y, (int)scrvec4.x, (int)scrvec4.y, color, static_cast<FillMode>(fillmode));
}
void Screen::DrawTriangle(const Vector2& vec1, const Vector2& vec2, const Vector2& vec3, unsigned int color, ShapeFillMode fillmode) const{
	Vector2 scr_1 = Conversion(vec1);
	Vector2 scr_2 = Conversion(vec2);
	Vector2 scr_3 = Conversion(vec3);
	Novice::DrawTriangle((int)scr_1.x, (int)scr_1.y, (int)scr_2.x, (int)scr_2.y, (int)scr_3.x, (int)scr_3.y, color, static_cast<FillMode>(fillmode));
}
void Screen::DrawCircle(const Vector2& vec, float rad, unsigned int color, ShapeFillMode fillmode) const{
	Vector2 scr = Conversion(vec);
	Novice::DrawEllipse((int)scr.x, (int)scr.y, (int)rad, (int)rad, 0.0f, color, static_cast<FillMode>(fillmode));
}
void Screen::DrawLine(const Vector2& vec1, const Vector2& vec2, unsigned int color) const{
	Vector2 scrvec1 = Conversion(vec1);
	Vector2 scrvec2 = Conversion(vec2);
	Novice::DrawLine((int)scrvec1.x, (int)scrvec1.y, (int)scrvec2.x, (int)scrvec2.y, color);
}
void Screen::DrawLineWidth(const Vector2& vec1, const Vector2& vec2, float width, unsigned int color) const {
	Vector2 scrvec1 = Conversion(vec1);
	Vector2 scrvec2 = Conversion(vec2);

	Vector2 normal = Vector2Math::Normal(scrvec1 - scrvec2);
	Vector2 upper = Vector2Math::Magnituded(normal,width);
	Vector2 lower = Vector2Math::Magnituded(-normal,width);

	Vector2 starttop = scrvec1 + upper;
	Vector2 endtop = scrvec2 + upper;
	Vector2 startbottom = scrvec1 + lower;
	Vector2 endbottom = scrvec2 + lower;

	Novice::DrawBox((int)starttop.x, (int)starttop.y, (int)endtop.x, (int)endtop.y, (int)endbottom.x, (int)endbottom.y, (int)startbottom.x, (int)startbottom.y, color, kFillModeSolid);
}

void Screen::DrawSprite() const{
	
}
void Screen::DrawSpriteRect(const Vector2& leftTop, int srcX, int srcY, int srcW, int srcH, int textureHandle, float scaleX,
	float scaleY, float angle, unsigned int color) const{
	Vector2 scr = Conversion(leftTop);
	Novice::DrawSpriteRect((int)scr.x, (int)scr.y, srcX, srcY, srcW, srcH, textureHandle, scaleX, scaleY, -angle, color);
}
void Screen::DrawQuad(const Vector2& vec1, const Vector2& vec2, const Vector2& vec3, const Vector2& vec4, 
	int srcX, int srcY, int srcW,
	int srcH, int textureHandle, unsigned int color) const{
	Vector2 scrvec1 = Conversion(vec1);
	Vector2 scrvec2 = Conversion(vec2);
	Vector2 scrvec3 = Conversion(vec3);
	Vector2 scrvec4 = Conversion(vec4);
	Novice::DrawQuad((int)scrvec1.x, (int)scrvec1.y, (int)scrvec2.x, (int)scrvec2.y, (int)scrvec3.x, (int)scrvec3.y, (int)scrvec4.x, (int)scrvec4.y,
		srcX, srcY, srcW, srcH, textureHandle, color);
}

void Screen::DrawQuad(const Quad& q,
	int srcX, int srcY, int srcW,
	int srcH, int textureHandle, unsigned int color) const {
	DrawQuad(q.lt,q.rt,q.lb,q.rb,srcX, srcY, srcW, srcH, textureHandle, color);

}