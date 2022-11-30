#pragma once
#include "GameObject.h"
#include "MyMath.h"
class LogoBase : 
	public GameObject 
{
public:
	struct Quad
	{
		Vector2 lt;
		Vector2 rt;
		Vector2 lb;
		Vector2 rb;

		Quad operator+(const Vector2& vec) const {
			return { lt + vec, rt + vec, lb + vec, rb + vec };
		}
	};

	struct Data
	{
		int imgHandle;
		int imgWidth;
		int imgHeight;

		Vector2 mPositin;
		Quad mQuad;
	};

private:
	Data mData;

public:
	LogoBase(class Game* game);
	virtual ~LogoBase();

	void Create(const Data& data);
	virtual void Update();
	void Draw();

	void setPos(const Vector2& p) { mData.mPositin = p; }
};

class SpaceMark :
	public LogoBase {

public:
	SpaceMark(class Game* game) : LogoBase(game){}
	void Update();
};