#pragma once
#include "Vector2.h"
#include <math.h>
#include <assert.h>

#pragma region ���Z�q

inline Vector2 operator+(const Vector2& v1, const Vector2& v2) {
	return { v1.x + v2.x, v1.y + v2.y };
}
inline Vector2 operator-(const Vector2& v1, const Vector2& v2) {
	return { v1.x - v2.x, v1.y - v2.y };
}
inline Vector2 operator*(const Vector2& v1, float s) {
	return { v1.x * s, v1.y * s };
}
inline Vector2 operator/(const Vector2& v1, float s) {
	assert(s != 0.0f); // 0���Z�m�F
	return { v1.x / s, v1.y / s };
}
inline Vector2 operator*(float s, const Vector2& v1) {
	return { s * v1.x, s * v1.y };
}
inline Vector2 operator*(const Vector2& v1, const Vector2& v2) {
	return { v1.x * v2.x, v1.y * v2.y };
}
inline bool operator==(const Vector2& v1, const Vector2& v2) {
	return v1.x == v2.x && v1.y == v2.y;
}
inline bool operator!=(const Vector2& v1, const Vector2& v2) {
	return v1.x != v2.x && v1.y != v2.y;
}
#pragma endregion


// Vector2�̌v�Z
namespace Vector2Math {
	// �[���ɂ���
	inline void SetZero(Vector2& v) {
		v.x = 0;
		v.y = 0;
	}
	// �[���ł��邩
	inline bool IsZero(const Vector2& v) {
		return { v.x == 0.0f && v.y == 0.0f };
	}
	// ����
	inline float Dot(const Vector2& v1, const Vector2& v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	// �O��
	inline float Cross(const Vector2& v1, const Vector2& v2) {
		return v1.x * v2.y - v1.y * v2.x;
	}
	// �����̓��
	inline float LengthSquare(const Vector2& v) {
		return Dot(v, v);
	}
	// ����
	inline float Length(const Vector2& v) {
		return sqrtf(LengthSquare(v));
	}
	// ���x�N�g���Ƃ̋���
	inline float Distance(const Vector2& v1, const Vector2& v2) {
		return Length(v2 - v1);
	}
	// �Ȃ��p
	inline float Angle(const Vector2& v) {
		return atan2f(v.y, v.x);
	}
	// ���K��
	inline Vector2 Normalized(const Vector2& v) {
		assert(!IsZero(v)); // ������0�o�Ȃ����m�F
		float len = Length(v);
		return v / len; 
	}
	// �x�N�g����90�����̑��@��
	inline Vector2 Normal(const Vector2& v) {
		return { -v.y, v.x };
	}
	// �x�N�g���́]90�����̑��@��
	inline Vector2 NegNormal(const Vector2& v) {
		return { v.y, -v.x };
	}
	// ���_
	inline Vector2 Mid(const Vector2& v1, const Vector2& v2) {
		return (v1 + v2) / 2.0f;
	}
	// ��]
	inline Vector2 Rotated(const Vector2& v, float theta) {
		float s = sinf(theta);
		float c = cosf(theta);
		return { v.x * c + v.y * -s, v.x * s + v.y * c };
	}
	// �g�k
	inline Vector2 Magnituded(const Vector2& v, float length) {
		return Normalized(v) * length;
	}
	// ���˃x�N�g��
	// �������͕ǂ̖@���𐳋K�������x�N�g��
	inline Vector2 Reflected(const Vector2& v, const Vector2& normal) {
		return Dot(normal, -v) * 2 * normal + v;
	}
	// �ǂ���x�N�g��
	// �������͕ǂ̖@���𐳋K�������x�N�g��
	inline Vector2 AlongWall(const Vector2& v, const Vector2& normal) {
		return Dot(normal, -v) * normal + v;
	}
	// ���`���
	inline Vector2 Lerp(float t, const Vector2& start, const Vector2& end) {
		return start + t * (end - start);
	}
	inline Vector2 MakeDirection(float theta) {
		return Rotated({ 1.0f, 0.0f }, theta);
	}
	// �x�W�F
	/// <summary>
	/// 3���x�W�F�Ȑ�
	/// </summary>
	/// <param name="t">�}��ϐ�</param>
	/// <param name="start">�n�_</param>
	/// <param name="control1">����_�P</param>
	/// <param name="control2">����_�Q</param>
	/// <param name="end">�I�_</param>
	/// <returns></returns>
	inline Vector2 CalcCubicBezierCurve(float t, const Vector2& start, const Vector2& control1, const Vector2& control2, const Vector2& end) {
		float s = 1.0f - t;
		return (powf(s, 3) * start) + (3 * powf(s, 2) * t * control1) + (3 * s * powf(t, 2) * control2) + powf(t, 3) * end;
	}

	/// <summary>
	/// ����3���x�W�F�Ȑ�
	/// </summary>
	/// <param name="t"></param>
	/// <param name="start"></param>
	/// <param name="control1"></param>
	/// <param name="control2"></param>
	/// <param name="end"></param>
	/// <returns></returns>
	inline Vector2 DiffCubicBezierCurve(float t, const Vector2& start, const Vector2& control1, const Vector2& control2, const Vector2& end) {
		return 3 * (-start + 3 * control1 - 3 * control2 + end) * powf(t, 2.0f) + 6 * (start - 2 * control1 + control2) * t + 3 * (-start + control1);
	}

}