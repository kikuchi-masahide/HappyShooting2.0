#include "MainSceneBaseLayer.h"
#include "MainScene.h"
#include "MainSceneDrawComponent.h"
#include "AddOneComponent.h"

MainSceneBaseLayer::MainSceneBaseLayer(Scene* scene, DrawComponentsMultiset* draw_components)
	:Layer(Rect2(0, 600, 0, 900), 0, 0),
	is_active_(false),layer_t_(0),scene_(scene),draw_components_(draw_components)
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
		auto itr = draw_components_->begin();
		while (itr != draw_components_->end())
		{
			auto comp = itr->comp_;
			if (comp.IsValid())
			{
				comp->Draw();
				itr++;
			}
			else
			{
				itr = draw_components_->erase(itr);
			}
		}
		game.mdx12.SetResourceBarrier(pera_texture_,
			DX12Config::ResourceBarrierState::RENDER_TARGET,
			DX12Config::ResourceBarrierState::PIXEL_SHADER_RESOURCE);
		//�y���|���S�����E�B���h�E�ɕ`��
		UniqueDraw();
	}
}

void MainSceneBaseLayer::SetActive()
{
	is_active_ = true;
	//����Update��++����ƁCOutput�ł��傤��0�ɂȂ�
	layer_t_ = -1;
	addone_obj_ = scene_->AddObject(MatVec::Vector2(), 1.0, 0.0);
	addone_comp_ = addone_obj_->AddUpdateComponent<AddOneComponent<int>>(0, &layer_t_);
}

void MainSceneBaseLayer::SetUnActive()
{
	is_active_ = false;
	addone_obj_->SetDeleteFlag();
}

int MainSceneBaseLayer::GetLayert()
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