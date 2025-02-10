#pragma once
#include "E_Scene.h"

#include "TitleScene.h"
#include "PlayScene.h"
#include "OverScene.h"

class SceneManager {
private:
	E_Scene currentScene_ = TITLE;
	TitleScene* title_;
	PlayScene* play_;
	OverScene* over_;
	bool triggerOnce_;

	int bgmTitle_;
	int bgmPlay_;
	int bgmOver_;

public:
	SceneManager();
	~SceneManager();
	bool Update(char* pK, char* k);//bool値リターンするのがEXITのため、trueならゲームを閉める
};

