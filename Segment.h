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
			// ���������s
			return error;
		}
		s = Vector2Math::Cross(seg2.start - seg1.start, seg2.end - seg2.start) / deno;
		t = Vector2Math::Cross(seg1.end - seg1.start, seg1.start - seg2.start) / deno;
		if (s < 0.0 || 1.0 < s || t < 0.0 || 1.0 < t) {
			// �������������Ă��Ȃ�
			return error;
		}
		return { seg1.start.x + s * (seg1.end - seg1.start).x, seg1.start.y + s * (seg1.end - seg1.start).y };
	}
	static inline Vector2 NearPoint(const Vector2& point, const Segment& segment, float& t) {
		// �����̎n�_����_�ւ̃x�N�g��	
		Vector2 PtoSeg = point - segment.start;
		// ����	    // �����̃x�N�g���𐳋K��     // �����̃x�N�g���̒���
		t = Vector2Math::Dot(PtoSeg,(Vector2Math::Normalized(segment.CalcVector()))) / Vector2Math::Length(segment.CalcVector());
		// t��0����1�Ɏ��߂�
		t = Math::Clamp<float>(t, 0, 1);
		// �ŋߖT�_�i���`��ԁj
		return Vector2Math::Lerp(t, segment.start, segment.end);
	}
};