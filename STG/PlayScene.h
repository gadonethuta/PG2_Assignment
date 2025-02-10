#pragma once
#include "E_Scene.h"
#include "Camera.h"
#include "Value.h"
#include "Vector2.h"
#include "stdlib.h"
#include "Quad.h"

#include "Player.h"
#include "Enemy.h"


class PlayScene {
private:
	int frames_;
	bool isPaused_;

	Player* player_;
	static const int kEnemyCount_ = 5;
	Enemy* enemy_[kEnemyCount_];

	Quad boundaryPoints_;
	Quad screenBoundaryPoints_;

	//Vector2 
	Value spawnTimer_;
	Camera *camera_;

	int sfxBoom_;
	int sfxPlayerBoom_;
public:
	PlayScene();
	~PlayScene();
	void Update(char* pK, char* k, E_Scene &currentScene);
	void Draw();
};

