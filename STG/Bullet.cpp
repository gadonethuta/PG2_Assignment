#include "Bullet.h"

#include "EZDraw.h"
#include "Matrix.h"


Bullet::Bullet() {
	pos_ = {0.0f, 0.0f};
	points_.p[0] = { pos_.x - 10.0f, pos_.y + 10.0f };
	points_.p[1] = { pos_.x + 10.0f, pos_.y + 5.0f };
	points_.p[2] = { pos_.x - 10.0f, pos_.y - 10.0f };
	points_.p[3] = { pos_.x + 10.0f, pos_.y - 5.0f };
	for (int i = 0; i < 4; i++) {
		screenPoints_.p[i] = { 0.0f, 0.0f };
	}

	speed_ = 15.0f;
	radius_ = 10.0f;
	isShot_ = false;
}

void Bullet::Update() {
	Matrix* mat = Matrix::GetInstance();

	pos_.x += speed_;

	if (pos_.x >= 1300.0f) {
		isShot_ = false;
	}

	//レンダリングのため
	points_.p[0] = { pos_.x - 10.0f, pos_.y + 10.0f };
	points_.p[1] = { pos_.x + 10.0f, pos_.y + 5.0f };
	points_.p[2] = { pos_.x - 10.0f, pos_.y - 10.0f };
	points_.p[3] = { pos_.x + 10.0f, pos_.y - 5.0f };

	//レンダリングパイプライン
	for (int i = 0; i < 4; i++) {
		screenPoints_.p[i] = mat->Transform(points_.p[i]);
	}


}

void Bullet::Draw() {
	if (isShot_) {
		EZDraw::DrawQuad(screenPoints_, WHITE);
	}
}

void Bullet::SetBulletShot(bool value) {
	isShot_ = value;
}

void Bullet::SetPos(Vector2 pos) {
	pos_ = pos;
}

bool Bullet::GetBulletShot() {
	return isShot_;
}

Vector2 Bullet::GetPos() {
	return pos_;
}

float Bullet::GetRadius() {
	return radius_;
}
