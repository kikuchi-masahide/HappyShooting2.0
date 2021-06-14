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
	auto heap = _game->mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 2);
	_game->mTexManager.LoadTexture(L"Resources/TitlePage/ButtonMouseAway.png", heap, 0, 0);
	_game->mTexManager.LoadTexture(L"Resources/TitlePage/ButtonMouseOn.png", heap, 1, 1);
	heap = _game->mdx12.CreateDescriptorHeap(DX12Config::DescriptorHeapType::CBV_SRV_UAV, DX12Config::DescriptorHeapShaderVisibility::SHADER_VISIBLE, 1);
	_game->mTexManager.LoadTexture(L"Resources/TitlePage/Title.png", heap, 0, 2);
}

void LoadShaders(Game* _game)
{
	_game->mShaderManager.LoadShader(L"HTextureDrawVertexShader.hlsl", DX12Config::ShaderType::VERTEX, 0);
	_game->mShaderManager.LoadShader(L"HTextureDrawPixelShader.hlsl", DX12Config::ShaderType::PIXEL, 1);
}