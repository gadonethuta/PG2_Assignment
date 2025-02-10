#pragma once
#include "Vector2.h"

class Basics {
public:
	/// <summary>
	/// ベクターを正規化する
	/// </summary>
	/// <param name="vec">ベクター</param>
	/// <returns>正規化したベクター</returns>
	static Vector2 Normalize(Vector2 vec);

	/// <summary>
	/// 値をリミットする
	/// </summary>
	/// <param name="value">値</param>
	/// <param name="min">最低限</param>
	/// <param name="max">最大限</param>
	/// <returns>リミットした値</returns>
	static float Clamp(float value, float min, float max);

	/// <summary>
	/// 値を少しずつ変わる
	/// </summary>
	/// <param name="from">から</param>
	/// <param name="to">まで</param>
	/// <param name="rate">変わるスピード（0.0f - 1.0f）</param>
	/// <returns>変わった値</returns>
	static float Lerp(float from, float to, float rate);

	/// <summary>
	/// 当たり判定チェック
	/// </summary>
	/// <param name="pos1">座標１</param>
	/// <param name="pos2">座標２</param>
	/// <param name="radius1">半径１</param>
	/// <param name="radius2">半径２</param>
	/// <returns>当たったらtrue、当たってないならfalse</returns>
	static bool Collision(Vector2 pos1, Vector2 pos2, float radius1, float radius2);
};

