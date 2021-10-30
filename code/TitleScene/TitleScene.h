#pragma once
#include "../Scene.h"

class TitleScene :public Scene
{
public:
	TitleScene(Game* _game);
	~TitleScene();
	void PriorUniqueUpdate() override;
	void PosteriorUniqueUpdate() override;
	void PriorUniqueOutput() override;
	void PosteriorUniqueOutput() override;
};