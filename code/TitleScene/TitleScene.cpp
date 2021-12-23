#include "TitleScene.h"

#include "TitleUIScreen.h"

TitleScene::TitleScene(Game* _game)
	:Scene(_game)
{
	AddUIScreen<TitleUIScreen>();
	Log::OutputTrivial("start TitleScene;");
}

TitleScene::~TitleScene()
{
	Log::OutputTrivial("end TitleScene;");
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
