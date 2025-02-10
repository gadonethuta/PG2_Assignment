#pragma once
#include "Vector2.h"
#include "Quad.h"
#include "Bullet.h"
#include "Value.h"

class Player {
private:
	Vector2 pos_;
	Vector2 dir_;
	float speed_;
	int hp_;
	float radius_;

	Quad points_;
	Quad screenPoints_;

	Value shootTimer_;
	static const int kBulletCount_ = 10;
	Bullet* bullet_[kBulletCount_];

	int sfxShoot_;
public:
	Player();
	~Player();
	void Update(char* pK, char* k);
	void Draw();
	
	void TakeDamage();

	Bullet GetBullet(int no);
	int GetBulletCount();
	int GetHP();
	Vector2 GetPos();
	float GetRadius();

};

