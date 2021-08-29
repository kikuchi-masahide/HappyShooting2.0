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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
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
	_game->mTexManager.LoadTexture(L"Resources/TitlePage/ButtonMouseAway.png", 0);
	_game->mTexManager.LoadTexture(L"Resources/TitlePage/ButtonMouseOn.png", 1);
	_game->mTexManager.LoadTexture(L"Resources/TitlePage/Title.png", 2);
	_game->mTexManager.LoadTexture(L"Resources/Cursor/cursor.png", 3);
	_game->mTexManager.LoadTexture(L"Resources/myself1/myself1.png", 4);
	_game->mTexManager.LoadTexture(L"Resources/Score_html/score_html.png", 5);
	_game->mTexManager.LoadTexture(L"Resources/numbers/numbers.png", 6);
	_game->mTexManager.LoadTexture(L"Resources/enemy1/enemy1.png", 7);
	_game->mTexManager.LoadTexture(L"Resources/enemy3/enemy3.png", 8);
	_game->mTexManager.LoadTexture(L"Resources/Enemy4/Enemy4_form0.png", 9);
	_game->mTexManager.LoadTexture(L"Resources/Enemy4/Enemy4.png", 10);
	_game->mTexManager.LoadTexture(L"Resources/Enemy4/Enemy4_form1.png", 11);
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
	_game->mShaderManager.LoadShader(L"HNumberDraw_vertex.hlsl", DX12Config::ShaderType::VERTEX, 10);
	_game->mShaderManager.LoadShader(L"HNumberDraw_pixel.hlsl", DX12Config::ShaderType::PIXEL, 11);
	_game->mShaderManager.LoadShader(L"DrawDeathEffectComponent_vertex.hlsl", DX12Config::ShaderType::VERTEX, 12);
	_game->mShaderManager.LoadShader(L"DrawDeathEffectComponent_pixel.hlsl", DX12Config::ShaderType::PIXEL, 13);
	_game->mShaderManager.LoadShader(L"DrawHealthBarComponent_vertex.hlsl", DX12Config::ShaderType::VERTEX, 14);
	_game->mShaderManager.LoadShader(L"DrawHealthBarComponent_pixel.hlsl", DX12Config::ShaderType::PIXEL, 15);
	_game->mShaderManager.LoadShader(L"DrawAnimationComponent_vertex.hlsl", DX12Config::ShaderType::VERTEX, 16);
	_game->mShaderManager.LoadShader(L"DrawAnimationComponent_pixel.hlsl", DX12Config::ShaderType::PIXEL, 17);
	_game->mShaderManager.LoadShader(L"DrawLazerComponent_vertex.hlsl", DX12Config::ShaderType::VERTEX, 18);
	_game->mShaderManager.LoadShader(L"DrawLazerComponent_pixel.hlsl", DX12Config::ShaderType::PIXEL, 19);
}