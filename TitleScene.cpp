#include "TitleScene.h"

#include "TitleUIScreen.h"

TitleScene::TitleScene(Game* _game)
	:Scene(_game)
{
	AddUIScreen<TitleUIScreen>();
}

TitleScene::~TitleScene()
{
}

void TitleScene::PriorUniqueUpdate()
{
}

void TitleScene::PosteriorUniqueUpdate()
{
}

void TitleScene::PriorUniqueOutput()
{
}

void TitleScene::PosteriorUniqueOutput()
{
}
