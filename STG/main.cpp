#include <Novice.h>
#include "Matrix.h"
#include "AudioMaster.h"

#include "Quad.h"
#include "time.h"
#include "Camera.h"
#include "EZDraw.h"
#include "Basics.h"

#include "SceneManager.h"

const char kWindowTitle[] = "GC1A_07_テュウタ_エー_Polygon_Shooter";

Matrix* Matrix::instance = nullptr;
AudioMaster* AudioMaster::instance = nullptr;

bool exitGame = false;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Novice::Initialize(kWindowTitle, 1280, 720);

	SceneManager* sceneManager = new SceneManager;

	srand(static_cast<int>(time(nullptr)));

	char keys[256] = {0};
	char preKeys[256] = {0};

	while (Novice::ProcessMessage() == 0) {
		
		Novice::BeginFrame();
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		exitGame = sceneManager->Update(preKeys, keys);
		Novice::EndFrame();

		
		if ((preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) || exitGame) {
			break;
		}
	}

	Novice::Finalize();

#pragma region インスタンスを消す

	delete sceneManager;

#pragma endregion

	return 0;
}
