#pragma once
#include "E_Scene.h"

class TitleScene {
private:
	int frames_;
public:
	TitleScene();
	void Update(char* pK, char* k, E_Scene &currentScene);
	void Draw();
};

