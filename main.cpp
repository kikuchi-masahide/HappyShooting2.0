#include "window.h"
#include "Game.h"
#include "TitleScene.h"

LRESULT WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void LoadTextures(Game* _game);
void LoadShaders(Game* _game);

#ifdef _DEBUG
int main() {
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
#endif // _DEBUG
	Game* game = new Game();
	game->Initialize();
	LoadTextures(game);
	LoadShaders(game);
	game->AddWindow(WindowProcedure, TEXT("WndClass"), 900, 900, TEXT("HAPPY Shooting"), 0);
	game->ChangeScene<TitleScene>();
	game->RunLoop();
	game->Shutdown();
	delete game;
	return 0;
}

LRESULT WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (msg == WM_DESTROY) {
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void LoadTextures(Game* _game)
{
	auto heap = _game->mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 2, L"ButtonMouseAway.png");
	_game->mTexManager.LoadTexture(L"Resources/TitlePage/ButtonMouseAway.png", heap, 0, 0);
	_game->mTexManager.LoadTexture(L"Resources/TitlePage/ButtonMouseOn.png", heap, 1, 1);
	heap = _game->mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1, L"Title.png");
	_game->mTexManager.LoadTexture(L"Resources/TitlePage/Title.png", heap, 0, 2);
	heap = _game->mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1, L"cursor.png");
	_game->mTexManager.LoadTexture(L"Resources/Cursor/cursor.png", heap, 0, 3);
	heap = _game->mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1, L"myself1.png");
	_game->mTexManager.LoadTexture(L"Resources/myself1/myself1.png", heap, 0, 4);
}

void LoadShaders(Game* _game)
{
	_game->mShaderManager.LoadShader(L"HTextureDrawVertexShader.hlsl", DX12Config::ShaderType::VERTEX, 0);
	_game->mShaderManager.LoadShader(L"HTextureDrawPixelShader.hlsl", DX12Config::ShaderType::PIXEL, 1);
	_game->mShaderManager.LoadShader(L"MainSceneBasicLayerVertexShader.hlsl", DX12Config::ShaderType::VERTEX, 2);
	_game->mShaderManager.LoadShader(L"MainSceneBasicLayerPixelShader.hlsl", DX12Config::ShaderType::PIXEL, 3);
	_game->mShaderManager.LoadShader(L"HDrawLineFrameVertexShader.hlsl", DX12Config::ShaderType::VERTEX, 4);
	_game->mShaderManager.LoadShader(L"HDrawLineFramePixelShader.hlsl", DX12Config::ShaderType::PIXEL, 5);
	_game->mShaderManager.LoadShader(L"HTextureAlphaRotateDrawVertexShader.hlsl", DX12Config::ShaderType::VERTEX, 6);
	_game->mShaderManager.LoadShader(L"HTextureAlphaRotateDrawPixelShader.hlsl", DX12Config::ShaderType::PIXEL, 7);
	_game->mShaderManager.LoadShader(L"DrawNormalBulletComponentVertexShader.hlsl", DX12Config::ShaderType::VERTEX, 8);
	_game->mShaderManager.LoadShader(L"DrawNormalBulletComponentPixelShader.hlsl", DX12Config::ShaderType::PIXEL, 9);
}