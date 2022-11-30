#pragma once
#include "GameObject.h"
#include "Quad.h"

enum ShapeFillMode {
	kSolid,
	kFrame
};

class Screen :
	public GameObject
{
public:
	struct Data {
		Vector2 mOrigin;
		Vector2 mScroll;
		Vector2 mCameraShake;

		Matrix33 mMatrix;

		unsigned int mColor;
		bool isCameraShake;
	};

private:
	Data mData;

public:
	Screen(class Game* game);
	~Screen();

	void Create();
	void Init();
	void Update();
	void CalcMatrix();

	Vector2 MousePosition();
	Vector2& scroll() { return mData.mScroll; }

	Vector2& cameraShake() { return mData.mCameraShake; }

	Vector2 Conversion(const Vector2& vec) const {
		return vec * mData.mMatrix;
	}

	void DrawBox(const Vector2& vec, float width, float height, float theta, unsigned int color = 0xFFFFFFFF, ShapeFillMode fillmode = kSolid) const;
	void DrawBox(const Vector2& vec1, const Vector2& vec2, const Vector2& vec3, const Vector2& vec4, unsigned int color = 0xFFFFFFFF, ShapeFillMode fillmode = kSolid) const;
	void DrawTriangle(const Vector2& vec1, const Vector2& vec2, const Vector2& vec3, unsigned int color = 0xFFFFFFFF, ShapeFillMode fillmode = kSolid) const;
	void DrawCircle(const Vector2& vec, float rad, unsigned int color = 0xFFFFFFFF, ShapeFillMode fillmode = kSolid) const;
	void DrawLine(const Vector2& vec1, const Vector2& vec2, unsigned int color = 0xFFFFFFFF) const;
	void DrawLineWidth(const Vector2& vec1, const Vector2& vec2, float width, unsigned int color = 0xFFFFFFFF) const;
	void DrawSprite() const;
	void DrawSpriteRect(const Vector2& leftTop, int srcX, int srcY, int srcW, int srcH, int textureHandle, float scaleX,
		float scaleY, float angle = 0.0f, unsigned int color = 0xFFFFFFFF) const;
	void DrawQuad(const Vector2& vec1, const Vector2& vec2, const Vector2& vec3, const Vector2& vec4,
		int srcX, int srcY, int srcW,
		int srcH, int textureHandle, unsigned int color = 0xFFFFFFFF) const;
	void DrawQuad(const Quad& q,
		int srcX, int srcY, int srcW,
		int srcH, int textureHandle, unsigned int color = 0xFFFFFFFF) const;
};