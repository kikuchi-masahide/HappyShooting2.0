#include "MainSceneBaseLayer.h"
#include "MainScene.h"
#include "Game.h"
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
		for (auto component : draw_components_)
		{
			component->Draw();
		}
		game.mdx12.SetResourceBarrier(pera_texture_,
			DX12Config::ResourceBarrierState::RENDER_TARGET,
			DX12Config::ResourceBarrierState::PIXEL_SHADER_RESOURCE);
		//�y���|���S�����E�B���h�E�ɕ`��
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
