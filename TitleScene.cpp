#include "TitleScene.h"

#include "TitleUIScreen.h"

TitleScene::TitleScene(Game* _game)
	:Scene(_game)
{
	AddUIScreen<TitleUIScreen>(this);
}

TitleScene::~TitleScene()
{
}

void TitleScene::UniqueUpdate()
{
}

void TitleScene::UniqueOutput()
{
}
