#include "TitleScene.h"


#include "EZDraw.h"
#include <Novice.h>

TitleScene::TitleScene() {
	frames_ = 0;
}

void TitleScene::Update(char* pK, char* k, E_Scene& currentScene) {
	frames_++;
	if (k[DIK_SPACE] && !pK[DIK_SPACE]) {
		currentScene = PLAY;
	} else if (k[DIK_X] && !pK[DIK_X]) {
		currentScene = EXIT;
	}
}

void TitleScene::Draw() {
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);
	Novice::ScreenPrintf(500, 200, "Polygon Shooter");
	if (frames_ % 60 < 30) {
		Novice::ScreenPrintf(500, 240, "Press SPACE to start");
		Novice::ScreenPrintf(500, 280, "Press X to exit");
	}
}
