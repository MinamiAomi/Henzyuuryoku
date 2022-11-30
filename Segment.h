#pragma once
#include "MyMath.h"
class Segment
{
public:
	Vector2 start;
	Vector2 end;
public:
	Segment() : start(), end(){}
	Segment(const Vector2& s, const Vector2& e) : start(s), end(e){}
	inline void Set(const Vector2& s, const Vector2& e) {
		start = s;
		end = e;
	}
	inline Vector2 CalcVector() const {
		return end - start;
	}
	static inline bool Collision(const Segment& seg1, const Segment& seg2) {
		Vector2 AB = seg1.CalcVector();
		Vector2 CD = seg2.CalcVector();

		int crossAC = Math::GetSign<float>(Vector2Math::Cross(AB, seg2.start - seg1.start));
		int crossAD = Math::GetSign<float>(Vector2Math::Cross(AB, seg2.end - seg1.start));
		int crossCA = Math::GetSign<float>(Vector2Math::Cross(CD, seg1.start - seg2.start));
		int crossCB = Math::GetSign<float>(Vector2Math::Cross(CD, seg1.end - seg2.start));

		if (crossAC != crossAD && crossCA != crossCB) {
			return true;
		}
		return false;
	}
	static inline Vector2 Intersection(const Segment& seg1, const Segment& seg2) {
		float s, t, deno = Vector2Math::Cross(seg1.end - seg1.start, seg2.end - seg2.start);
		Vector2 error = { Math::Inf, Math::Inf };
		if (deno == 0.0) {
			// 線分が平行
			return error;
		}
		s = Vector2Math::Cross(seg2.start - seg1.start, seg2.end - seg2.start) / deno;
		t = Vector2Math::Cross(seg1.end - seg1.start, seg1.start - seg2.start) / deno;
		if (s < 0.0 || 1.0 < s || t < 0.0 || 1.0 < t) {
			// 線分が交差していない
			return error;
		}
		return { seg1.start.x + s * (seg1.end - seg1.start).x, seg1.start.y + s * (seg1.end - seg1.start).y };
	}
	static inline Vector2 NearPoint(const Vector2& point, const Segment& segment, float& t) {
		// 線分の始点から点へのベクトル	
		Vector2 PtoSeg = point - segment.start;
		// 内積	    // 線分のベクトルを正規化     // 線分のベクトルの長さ
		t = Vector2Math::Dot(PtoSeg,(Vector2Math::Normalized(segment.CalcVector()))) / Vector2Math::Length(segment.CalcVector());
		// tを0から1に収める
		t = Math::Clamp<float>(t, 0, 1);
		// 最近傍点（線形補間）
		return Vector2Math::Lerp(t, segment.start, segment.end);
	}
};