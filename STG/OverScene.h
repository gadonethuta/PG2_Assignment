#pragma once
#include "E_Scene.h"

class OverScene {
private:
	int timer_;
public:
	OverScene();
	void Update(char* pk, char* k, E_Scene &currentScene);
	void Draw();
};

