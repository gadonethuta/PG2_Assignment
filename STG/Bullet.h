#pragma once

#include "Vector2.h"
#include "Quad.h"

class Bullet {
private:
	Vector2 pos_;
	Quad points_;
	Quad screenPoints_;

	float speed_;
	float radius_;
	bool isShot_;

public:
	Bullet();
	void Update();
	void Draw();

	void SetBulletShot(bool value);
	void SetPos(Vector2 pos);

	bool GetBulletShot();
	Vector2 GetPos();
	float GetRadius();
};

