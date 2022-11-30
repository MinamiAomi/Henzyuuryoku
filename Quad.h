#pragma once
#include "MyMath.h"
struct Quad
{
	Vector2 lt; // ç∂è„
	Vector2 rt; // âEè„
	Vector2 lb; // ç∂â∫
	Vector2 rb; // âEâ∫
	Quad() {}
	Quad(const Vector2& lt, const Vector2& rt, const Vector2& lb, const Vector2& rb) : lt(lt), rt(rt), lb(lb), rb(rb) {}
	Quad(const Vector2& lt, float w, float h, float t) : lt(lt) {
		float left = 0;
		float top = 0;
		float right = w;
		float bottom = -h;

		Vector2 RT(right, top);
		Vector2 LB(left, bottom);
		Vector2 RB(right, bottom);

		Matrix33 mat;
		mat.MultiplyRotation(t);
		mat.MultiplyTranslation(lt);

		rt = RT * mat;
		lb = LB * mat;
		rb = RB * mat;
	}

	friend inline Quad operator+(const Quad& q1, const Quad& q2) {
		return { q1.lt + q2.lt,q1.rt + q2.rt, q1.lb + q2.lb,q1.rb + q2.rb };
	}
	friend inline Quad operator-(const Quad& q1, const Quad& q2) {
		return { q1.lt - q2.lt,q1.rt - q2.rt, q1.lb - q2.lb,q1.rb - q2.rb };
	}
	friend inline Quad operator*(float s, const Quad& q) {
		return { s * q.lt, s * q.rt, s * q.lb, s * q.rb };
	}
	friend inline Quad operator*(const Quad& q, float s) {
		return { q.lt * s, q.rt * s,q.lb * s,q.rb * s };
	}
	friend inline Quad operator*(const Quad& q, const Matrix33& mat) {
		return { q.lt * mat , q.rt * mat, q.lb * mat, q.rb * mat };
	}
};