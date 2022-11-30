#pragma once
#include "Vector2.h"
#include <math.h>
#include <assert.h>

#pragma region 演算子

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
	assert(s != 0.0f); // 0除算確認
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


// Vector2の計算
namespace Vector2Math {
	// ゼロにする
	inline void SetZero(Vector2& v) {
		v.x = 0;
		v.y = 0;
	}
	// ゼロであるか
	inline bool IsZero(const Vector2& v) {
		return { v.x == 0.0f && v.y == 0.0f };
	}
	// 内積
	inline float Dot(const Vector2& v1, const Vector2& v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	// 外積
	inline float Cross(const Vector2& v1, const Vector2& v2) {
		return v1.x * v2.y - v1.y * v2.x;
	}
	// 長さの二乗
	inline float LengthSquare(const Vector2& v) {
		return Dot(v, v);
	}
	// 長さ
	inline float Length(const Vector2& v) {
		return sqrtf(LengthSquare(v));
	}
	// 他ベクトルとの距離
	inline float Distance(const Vector2& v1, const Vector2& v2) {
		return Length(v2 - v1);
	}
	// なす角
	inline float Angle(const Vector2& v) {
		return atan2f(v.y, v.x);
	}
	// 正規化
	inline Vector2 Normalized(const Vector2& v) {
		assert(!IsZero(v)); // 長さが0出ないか確認
		float len = Length(v);
		return v / len; 
	}
	// ベクトルの90°側の側法線
	inline Vector2 Normal(const Vector2& v) {
		return { -v.y, v.x };
	}
	// ベクトルの‐90°側の側法線
	inline Vector2 NegNormal(const Vector2& v) {
		return { v.y, -v.x };
	}
	// 中点
	inline Vector2 Mid(const Vector2& v1, const Vector2& v2) {
		return (v1 + v2) / 2.0f;
	}
	// 回転
	inline Vector2 Rotated(const Vector2& v, float theta) {
		float s = sinf(theta);
		float c = cosf(theta);
		return { v.x * c + v.y * -s, v.x * s + v.y * c };
	}
	// 拡縮
	inline Vector2 Magnituded(const Vector2& v, float length) {
		return Normalized(v) * length;
	}
	// 反射ベクトル
	// 第二引数は壁の法線を正規化したベクトル
	inline Vector2 Reflected(const Vector2& v, const Vector2& normal) {
		return Dot(normal, -v) * 2 * normal + v;
	}
	// 壁ずりベクトル
	// 第二引数は壁の法線を正規化したベクトル
	inline Vector2 AlongWall(const Vector2& v, const Vector2& normal) {
		return Dot(normal, -v) * normal + v;
	}
	// 線形補間
	inline Vector2 Lerp(float t, const Vector2& start, const Vector2& end) {
		return start + t * (end - start);
	}
	inline Vector2 MakeDirection(float theta) {
		return Rotated({ 1.0f, 0.0f }, theta);
	}
	// ベジェ
	/// <summary>
	/// 3次ベジェ曲線
	/// </summary>
	/// <param name="t">媒介変数</param>
	/// <param name="start">始点</param>
	/// <param name="control1">制御点１</param>
	/// <param name="control2">制御点２</param>
	/// <param name="end">終点</param>
	/// <returns></returns>
	inline Vector2 CalcCubicBezierCurve(float t, const Vector2& start, const Vector2& control1, const Vector2& control2, const Vector2& end) {
		float s = 1.0f - t;
		return (powf(s, 3) * start) + (3 * powf(s, 2) * t * control1) + (3 * s * powf(t, 2) * control2) + powf(t, 3) * end;
	}

	/// <summary>
	/// 微分3次ベジェ曲線
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