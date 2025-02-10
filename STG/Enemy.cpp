#include "Enemy.h"

#include "Matrix.h"
#include "EZDraw.h"

Enemy::Enemy(Vector2 pos) {
	pos_ = pos;
	points_.p[0] = { pos_.x - 20.0f, pos_.y + 20.0f };
	points_.p[1] = { pos_.x + 20.0f, pos_.y + 20.0f };
	points_.p[2] = { pos_.x - 20.0f, pos_.y - 20.0f };
	points_.p[3] = { pos_.x + 20.0f, pos_.y - 20.0f };
	for (int i = 0; i < 4; i++) {
		screenPoints_.p[i] = { 0.0f, 0.0f };
	}

	speed_ = -5.0f;
	radius_ = 22.0f;
}

void Enemy::Update() {
	Matrix* mat = Matrix::GetInstance();

	pos_.x += speed_;


	//レンダリングのため
	points_.p[0] = { pos_.x - 20.0f, pos_.y + 20.0f };
	points_.p[1] = { pos_.x + 20.0f, pos_.y + 20.0f };
	points_.p[2] = { pos_.x - 20.0f, pos_.y - 20.0f };
	points_.p[3] = { pos_.x + 20.0f, pos_.y - 20.0f };

	//レンダリングパイプライン
	for (int i = 0; i < 4; i++) {
		screenPoints_.p[i] = mat->Transform(points_.p[i]);
	}
}

void Enemy::Draw() {
	EZDraw::DrawQuad(screenPoints_, RED);
}


Vector2 Enemy::GetPos() {
	return pos_;
}


float Enemy::GetRadius() {
	return radius_;
}
