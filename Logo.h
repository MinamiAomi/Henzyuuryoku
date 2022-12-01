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
		int imgHandle = 0;
		int imgHandle2 = 0;
		int imgWidth = 0;;
		int imgHeight = 0l;
		int imgWidth2 = 0;
		int imgHeight2 = 0;

		Vector2 mPositin;
		Quad mQuad;
		Quad mQuad2;
	};

private:
	Data mData;
	bool space = false;

public:
	LogoBase(class Game* game, bool spa = false);
	virtual ~LogoBase();

	void Create(const Data& data);
	virtual void Update();
	void Draw();

	void setPos(const Vector2& p) { mData.mPositin = p; }
};

class SpaceMark :
	public LogoBase {

public:
	SpaceMark(class Game* game, bool spa = true) : LogoBase(game,spa){}
	void Update();
};