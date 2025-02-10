#pragma once
#include "Vector2.h"
#include "Quad.h"
#include <Novice.h>

//描画に便利なクラス
class EZDraw {
public:
	/// <summary>
	/// 丸を描く
	/// </summary>
	/// <param name="pos">描画したい座標</param>
	/// <param name="radius1">横半径</param>
	/// <param name="radius2">立半径</param>
	/// <param name="angle">回転</param>
	/// <param name="color">色</param>
	/// <param name="fillmode">kFillModeSolid / kFillModeWireFrame</param>
	/// <param name="shake">シェーキベクター</param>
	static void DrawEllipse(Vector2 pos, float radius1, float radius2, float angle, unsigned int color, FillMode fillmode, Vector2 shake = {0.0f, 0.0f});
	
	/// <summary>
	/// ポリゴンを描く
	/// </summary>
	/// <param name="points">点の座標</param>
	/// <param name="color">色</param>
	/// <param name="graph">画像</param>
	/// <param name="shake">シェーキベクター</param>
	static void DrawQuad(Quad points, unsigned int color, int graph = -1, Vector2 shake = { 0.0f, 0.0f });
};

