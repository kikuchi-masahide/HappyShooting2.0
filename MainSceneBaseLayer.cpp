#include "MainSceneBaseLayer.h"

#include "Game.h"

MainSceneBaseLayer::MainSceneBaseLayer(Scene* scene, boost::shared_ptr<std::set<void*>> hset)
	:Layer(scene,hset,Rect2(0,600,0,900),0,0)
{
	GraphicsInit();
}

MainSceneBaseLayer::~MainSceneBaseLayer()
{
}

void MainSceneBaseLayer::Draw()
{
	if (is_active_)
	{
		Game& game = GetGame();
		game.mdx12.SetResourceBarrier(pera_texture_,
			DX12Config::ResourceBarrierState::PIXEL_SHADER_RESOURCE,
			DX12Config::ResourceBarrierState::RENDER_TARGET);
		game.mdx12.OpenRenderTarget(pera_rtv_,0);
		game.mdx12.ClearRenderTarget(pera_rtv_, 0, 1.0f, 1.0f, 1.0f, 1.0f);
		for (auto component : draw_components_)
		{
			component->Draw();
		}
		game.mdx12.SetResourceBarrier(pera_texture_,
			DX12Config::ResourceBarrierState::RENDER_TARGET,
			DX12Config::ResourceBarrierState::PIXEL_SHADER_RESOURCE);
		//ペラポリゴンをウィンドウに描画
		UniqueDraw();
		draw_components_.clear();
		layer_t_++;
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

unsigned int MainSceneBaseLayer::GetLayert()
{
	return layer_t_;
}

void MainSceneBaseLayer::GraphicsInit()
{
	Game& game = GetGame();
	pera_texture_ = game.mdx12.CreateClearTexture(600, 900, 1.0f, 1.0f, 1.0f, 1.0f);
	pera_rtv_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::RTV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1);
	game.mdx12.CreateRenderTargetView(pera_texture_,pera_rtv_,0);
	pera_srv_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1);
	game.mdx12.CreateShaderResourceView(pera_texture_, pera_srv_, 0);
}
