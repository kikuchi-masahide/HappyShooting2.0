#include "stdafx.h"
#include "CollisionUIScreen.h"

#include "PolygonGeometryDrawer.h"
#include "Scene.h"

CollisionUIScreen::CollisionUIScreen(Scene* scene)
	:UIScreen(scene,true,true)
{
}

CollisionUIScreen::~CollisionUIScreen()
{
}

void CollisionUIScreen::Update()
{
	for (auto itr = polygon_drawers_.begin(); itr != polygon_drawers_.end(); itr++)
	{
		itr->second.Update();
	}
}

void CollisionUIScreen::Output()
{
	Game& game = mScene->mGame;
	game.OpenSwapChain(0);
	for (auto itr = polygon_drawers_.begin(); itr != polygon_drawers_.end(); itr++)
	{
		itr->second.Output(game);
	}
	game.CloseSwapChain();
}

void CollisionUIScreen::AddPolygonGeometry(PolygonGeometry* polygon, MatVec::Vector3 color)
{
	polygon_drawers_.emplace(
		std::piecewise_construct,std::forward_as_tuple(polygon),std::forward_as_tuple(polygon,color,mScene->mGame)
	);
}

void CollisionUIScreen::DeletePolygonGeometry(PolygonGeometry* polygon)
{
	auto itr = polygon_drawers_.find(polygon);
	if (itr != polygon_drawers_.end())
	{
		polygon_drawers_.erase(itr);
	}
}

