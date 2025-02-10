#pragma once

#include "Vector2.h"
#include "Quad.h"

class Enemy {
private:
	Vector2 pos_;
	Quad points_;
	Quad screenPoints_;

	float speed_;
	float radius_;
public:
	Enemy(Vector2 pos);
	void Update();
	void Draw();

	
	Vector2 GetPos();
	float GetRadius();
};

