#include "EZDraw.h"

void EZDraw::DrawEllipse(Vector2 pos, float radius1, float radius2, float angle, unsigned int color, FillMode fillmode, Vector2 shake) {
	Novice::DrawEllipse(static_cast<int>(pos.x + shake.x), static_cast<int>(pos.y + shake.y), static_cast<int>(radius1), static_cast<int>(radius2), angle, color, fillmode);
}

void EZDraw::DrawQuad(Quad points, unsigned int color, int graph, Vector2 shake) {
	if (graph == -1) {
		graph = Novice::LoadTexture("./NoviceResources/white1x1.png");
	}
	Novice::DrawQuad(static_cast<int>(points.p[0].x + shake.x), static_cast<int>(points.p[0].y + shake.y),
		static_cast<int>(points.p[1].x + shake.x), static_cast<int>(points.p[1].y + shake.y),
		static_cast<int>(points.p[2].x + shake.x), static_cast<int>(points.p[2].y + shake.y),
		static_cast<int>(points.p[3].x + shake.x), static_cast<int>(points.p[3].y + shake.y),
		0, 0, 1, 1, graph, color);
}

