#include "CollisionUIScreen.h"

#include "PolygonGeometryDrawer.h"
#include "../Engine/Scene.h"

CollisionUIScreen::CollisionUIScreen(Scene* scene)
	:UIScreen(scene,true,true)
{
}

CollisionUIScreen::~CollisionUIScreen()
{
}

void CollisionUIScreen::Update()
{
#ifdef _DEBUG
	for (auto itr = polygon_drawers_.begin(); itr != polygon_drawers_.end(); itr++)
	{
		itr->second.Update();
	}
#endif
}

void CollisionUIScreen::Output()
{
#ifdef _DEBUG
	Game& game = mScene->mGame;
	game.OpenSwapChain(0);
	for (auto itr = polygon_drawers_.begin(); itr != polygon_drawers_.end(); itr++)
	{
		itr->second.Output(game);
	}
	game.CloseSwapChain();
#endif
}

void CollisionUIScreen::AddPolygonGeometry(PolygonGeometry* polygon, MatVec::Vector3 color)
{
	//DEBUGŽž‚Ì‚Ý“o˜^‚·‚é
#ifdef _DEBUG
	polygon_drawers_.emplace(
		std::piecewise_construct,std::forward_as_tuple(polygon),std::forward_as_tuple(polygon,color,mScene->mGame)
	);
#endif
}

void CollisionUIScreen::DeletePolygonGeometry(PolygonGeometry* polygon)
{
#ifdef _DEBUG
	auto itr = polygon_drawers_.find(polygon);
	if (itr != polygon_drawers_.end())
	{
		polygon_drawers_.erase(itr);
	}
#endif
}

