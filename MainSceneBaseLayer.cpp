#include "MainSceneBaseLayer.h"

MainSceneBaseLayer::MainSceneBaseLayer(Scene* scene, boost::shared_ptr<std::set<void*>> hset)
	:Layer(scene,hset,Rect2(0,600,0,900),0,0)
{
}

MainSceneBaseLayer::~MainSceneBaseLayer()
{
}

void MainSceneBaseLayer::Draw()
{
	if (is_active_)
	{
		//ペラポリゴンの処理
		for (auto component : draw_components_)
		{
			component->Draw();
		}
		//ペラポリゴンをウィンドウに描画
		UniqueDraw();
		draw_components_.clear();
	}
}

void MainSceneBaseLayer::SetActive()
{
	is_active_ = true;
	layer_t_ = 0;
}

void MainSceneBaseLayer::SetUnActive()
{
	is_active_ = false;
}

void MainSceneBaseLayer::AddComponent(ComponentHandle<MainSceneDrawComponent> component)
{
	draw_components_.push_back(component);
}