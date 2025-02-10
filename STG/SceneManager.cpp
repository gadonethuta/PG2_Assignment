#include "SceneManager.h"

#include "AudioMaster.h"
#include <Novice.h>

SceneManager::SceneManager() {
	currentScene_ = TITLE;
	title_ = new TitleScene;
	play_ = new PlayScene;
	over_ = new OverScene;
	triggerOnce_ = false;

	bgmTitle_ = Novice::LoadAudio("./Resources/Audio/bgm_title.mp3");
	bgmPlay_ = Novice::LoadAudio("./Resources/Audio/bgm_play.mp3");
	bgmOver_ = Novice::LoadAudio("./Resources/Audio/bgm_gameOver.mp3");
}


bool SceneManager::Update(char* pK, char* k) {
	AudioMaster* am = AudioMaster::GetInstance();

	switch (currentScene_) {
	case TITLE:
		if (!triggerOnce_) {
			triggerOnce_ = true;
			am->PlayBGM(bgmTitle_);
		}

		title_->Update(pK, k, currentScene_);
		title_->Draw();

		if (currentScene_ != TITLE) {
			delete title_;
			title_ = nullptr;
			triggerOnce_ = false;
			am->StopBGM();
			play_ = new PlayScene;
		}
		break;
	case PLAY:
		if (!triggerOnce_) {
			triggerOnce_ = true;
			am->PlayBGM(bgmPlay_);
		}

		play_->Update(pK, k, currentScene_);
		play_->Draw();

		if (currentScene_ != PLAY) {
			delete play_;
			play_ = nullptr;
			triggerOnce_ = false;
			am->StopBGM();
			over_ = new OverScene;
		}
		break;
	case OVER:
		if (!triggerOnce_) {
			triggerOnce_ = true;
			am->PlayBGM(bgmOver_);
		}

		over_->Update(pK, k, currentScene_);
		over_->Draw();

		if (currentScene_ != OVER) {
			delete over_;
			over_ = nullptr;
			triggerOnce_ = false;
			am->StopBGM();
			title_ = new TitleScene;
		}
		break;
	case EXIT:
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);
		return true;
		break;
	default:
		break;
	}
	return false;
}


SceneManager::~SceneManager() {
	delete title_;
	delete play_;
}
