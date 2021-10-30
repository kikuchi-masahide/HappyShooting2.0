#include "MainSceneBaseLayer.h"
#include "MainScene.h"
#include "MainSceneDrawComponent.h"

MainSceneBaseLayer::MainSceneBaseLayer(Scene* scene)
	:Layer(Rect2(0, 600, 0, 900), 0, 0), is_active_(false),layer_t_(0),scene_(scene)
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
		auto itr = draw_components_.begin();
		while (itr != draw_components_.end())
		{
			auto comp = itr->handle_;
			if (comp.IsValid())
			{
				comp->Draw();
				itr++;
			}
			else
			{
				itr = draw_components_.erase(itr);
			}
		}
		game.mdx12.SetResourceBarrier(pera_texture_,
			DX12Config::ResourceBarrierState::RENDER_TARGET,
			DX12Config::ResourceBarrierState::PIXEL_SHADER_RESOURCE);
		//ペラポリゴンをウィンドウに描画
		UniqueDraw();
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
	draw_components_.emplace(component);
}

unsigned int MainSceneBaseLayer::GetLayert()
{
	return layer_t_;
}

Game& MainSceneBaseLayer::GetGame()
{
	return scene_->mGame;
}

void MainSceneBaseLayer::GraphicsInit()
{
	Game& game = GetGame();
	pera_texture_ = game.mdx12.CreateClearTexture(600, 900, 1.0f, 1.0f, 1.0f, 1.0f, L"MainSceneBaseLayer pera_texture_");
	pera_rtv_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::RTV, DX12Config::DescriptorHeapShaderVisibility::NONE, 1, L"MainSceneBaseLayer::pera_rtv_");
	game.mdx12.CreateRenderTargetView(pera_texture_,pera_rtv_,0);
	pera_srv_ = game.mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1, L"MainSceneBaseLayer::pera_srv_");
	game.mdx12.CreateShaderResourceViewForClearTexture(pera_texture_, pera_srv_, 0);
}

DrawComponentUnit::DrawComponentUnit(ComponentHandle<MainSceneDrawComponent> handle)
	:handle_(handle)
{
	z_ = handle_->z_;
}