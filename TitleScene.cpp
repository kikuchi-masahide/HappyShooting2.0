#include "TitleScene.h"

TitleScene::TitleScene(Game* _game)
	:Scene(_game)
{
	Log::OutputTrivial("TitleScene constructor");
}

TitleScene::~TitleScene()
{
	Log::OutputTrivial("TitleScene destructor");
}

void TitleScene::UniqueUpdate()
{
	Log::OutputTrivial("TitleScene UniqueUpdate");
}

void TitleScene::UniqueOutput()
{
	Log::OutputTrivial("TitleScnene UniqueOutput");
}
