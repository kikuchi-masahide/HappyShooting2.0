#pragma once
#include "Scene.h"

class TitleScene :public Scene
{
public:
	TitleScene(Game* _game);
	~TitleScene();
	void UniqueUpdate();
	void UniqueOutput();
};