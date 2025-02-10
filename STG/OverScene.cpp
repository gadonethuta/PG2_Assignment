#include "OverScene.h"

#include <Novice.h>

OverScene::OverScene() {
	timer_ = 0;
}

void OverScene::Update(char* pk, char* k, E_Scene& currentScene) {
	timer_++;
	if (timer_ >= 60) {
		if (k[DIK_SPACE] && !pk[DIK_SPACE]) {
			currentScene = TITLE;
		}
		if (k[DIK_X] && !pk[DIK_X]) {
			currentScene = EXIT;
		}
	}
}


void OverScene::Draw() {
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);
	Novice::ScreenPrintf(500, 200, "GAME OVER");
	if (timer_ >= 60) {
		if ((timer_ % 60) < 30) {
			Novice::ScreenPrintf(500, 240, "Press SPACE to restart");
			Novice::ScreenPrintf(500, 280, "Press X to exit");
		}
	}
}
