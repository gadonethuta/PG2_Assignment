#include "PlayScene.h"

#include "Quad.h"
#include "Matrix.h"
#include "Vector2.h"
#include "EZDraw.h"
#include "Basics.h"
#include "AudioMaster.h"

#include <Novice.h>

PlayScene::PlayScene() {
	frames_ = 0;
	isPaused_ = false;
	
	player_ = new Player();
	camera_ = new Camera();

	for (int i = 0; i < kEnemyCount_; i++) {
		enemy_[i] = nullptr;
	}
	spawnTimer_ = { 0, 60 };

	boundaryPoints_.p[0] = { 0.0f, 0.0f };
	boundaryPoints_.p[1] = { 1280.0f, 0.0f };
	boundaryPoints_.p[2] = { 0.0f, 720.0f };
	boundaryPoints_.p[3] = { 1280.0f, 720.0f };
	for (int i = 0; i < 4; i++) {
		screenBoundaryPoints_.p[i] = { 0.0f, 0.0f };
	}

	sfxBoom_ = Novice::LoadAudio("./Resources/Audio/boom.wav");
	sfxPlayerBoom_ = Novice::LoadAudio("./Resources/Audio/playerBoom.wav");
}

PlayScene::~PlayScene() {
	delete player_;
	delete camera_;
}

void PlayScene::Update(char* pK, char* k, E_Scene &currentScene) {
	AudioMaster* am = AudioMaster::GetInstance();

	if (k[DIK_L] && !pK[DIK_L]) {
		isPaused_ = !isPaused_;
	}
	if (isPaused_) {
		return;
	}

	Matrix* mat = Matrix::GetInstance();

	frames_++;
	if (k[DIK_P] && !pK[DIK_P]) {
		currentScene = EXIT;
	}

	camera_->CameraControls(pK, k);
	mat->CalculateMatrix(*camera_);

	spawnTimer_.now++;
	if (spawnTimer_.now > spawnTimer_.max) {
		for (int i = 0; i < kEnemyCount_; i++) {
			if (enemy_[i] == nullptr) {
				enemy_[i] = new Enemy({ 1300.0f, (rand() % 701) + 10.0f});

				spawnTimer_.now = 0;
				break;
			}
		}
	}

	for (int i = 0; i < kEnemyCount_; i++) {
		if (enemy_[i] != nullptr) {
			enemy_[i]->Update();
			if (enemy_[i]->GetPos().x <= -20.0f) {
				delete enemy_[i];
				enemy_[i] = nullptr;
			}
		}
	}

	player_->Update(pK, k);

	//当たり判定
	for (int i = 0; i < player_->GetBulletCount(); i++) {
		if (player_->GetBullet(i).GetBulletShot() == true) {
			for (int j = 0; j < kEnemyCount_; j++) {
				if (enemy_[j] != nullptr) {
					if (Basics::Collision(player_->GetBullet(i).GetPos(), enemy_[j]->GetPos(),
						player_->GetBullet(i).GetRadius(), enemy_[j]->GetRadius())) {
						delete enemy_[j];
						enemy_[j] = nullptr;
						am->PlaySFX(sfxBoom_);
					}
				}
			}
		}
	}
	for (int i = 0; i < kEnemyCount_; i++) {
		if (enemy_[i] != nullptr) {
			if (Basics::Collision(player_->GetPos(), enemy_[i]->GetPos(),
				player_->GetRadius(), enemy_[i]->GetRadius())) {
				delete enemy_[i];
				enemy_[i] = nullptr;
				player_->TakeDamage();
				am->PlaySFX(sfxPlayerBoom_);
			}
		}
	}


	//HPチェック
	if (player_->GetHP() <= 0) {
		currentScene = OVER;
	}

	for (int i = 0; i < 4; i++) {
		screenBoundaryPoints_.p[i] = mat->Transform(boundaryPoints_.p[i]);
	}
}

void PlayScene::Draw() {
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0x0F0F5FFF, kFillModeSolid);

	EZDraw::DrawQuad(screenBoundaryPoints_, BLACK);

	for (int i = 0; i < kEnemyCount_; i++) {
		if (enemy_[i] != nullptr) {
			enemy_[i]->Draw();
		}
	}
	player_->Draw();

	Novice::ScreenPrintf(20, 680, "Camera Controls : WASD movement, QE rotate, ZC zoom, R reset");
	Novice::ScreenPrintf(20, 700, "Player Controls : ArrowKeys movement, SPACE shoot");
}
