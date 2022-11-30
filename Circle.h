#pragma once
#include "MyMath.h"
#include "Screen.h"

class Circle
{
public:
	Vector2 center;
	float radius;

public:
	Circle() : center(), radius(0) {}
	Circle(const Vector2& c, float r) : center(c), radius(r){}

	inline void Set(const Vector2& c, float r) {
		center = c;
		radius = r;
	}
	static inline bool Collision(const Circle& cir1, const Circle& cir2) {
		return Vector2Math::Distance(cir1.center, cir2.center) <= cir1.radius + cir2.radius;
	}
	// ”¼Œa‚Í•Ï‚í‚ç‚È‚¢
	static inline void Draw(const Circle& cir, const Matrix33& mat, const Screen& scr, unsigned int color = 0xFFFFFFFF, ShapeFillMode fm = kSolid) {
		scr.DrawCircle(cir.center * mat, cir.radius, color, fm);
	}
	static inline void Draw(const Circle& cir, const Screen& scr, unsigned int color = 0xFFFFFFFF, ShapeFillMode fm = kSolid) {
		scr.DrawCircle(cir.center, cir.radius, color, fm);
	}
};