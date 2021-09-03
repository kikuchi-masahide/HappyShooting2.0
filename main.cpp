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
	_game->mTexManager.LoadTexture(L"Resources/images/ButtonMouseAway.png", 0);
	_game->mTexManager.LoadTexture(L"Resources/images/ButtonMouseOn.png", 1);
	_game->mTexManager.LoadTexture(L"Resources/images/Title.png", 2);
	_game->mTexManager.LoadTexture(L"Resources/images/cursor.png", 3);
	_game->mTexManager.LoadTexture(L"Resources/images/myself1.png", 4);
	_game->mTexManager.LoadTexture(L"Resources/images/score_html.png", 5);
	_game->mTexManager.LoadTexture(L"Resources/images/numbers.png", 6);
	_game->mTexManager.LoadTexture(L"Resources/images/enemy1.png", 7);
	_game->mTexManager.LoadTexture(L"Resources/images/enemy3.png", 8);
	_game->mTexManager.LoadTexture(L"Resources/images/Enemy4_form0.png", 9);
	_game->mTexManager.LoadTexture(L"Resources/images/Enemy4.png", 10);
	_game->mTexManager.LoadTexture(L"Resources/images/Enemy4_form1.png", 11);
}

void LoadShaders(Game* _game)
{
	_game->mShaderManager.LoadShader(L"Shader/HTextureDrawVertexShader.hlsl", DX12Config::ShaderType::VERTEX, 0);
	_game->mShaderManager.LoadShader(L"Shader/HTextureDrawPixelShader.hlsl", DX12Config::ShaderType::PIXEL, 1);
	_game->mShaderManager.LoadShader(L"Shader/MainSceneBasicLayerVertexShader.hlsl", DX12Config::ShaderType::VERTEX, 2);
	_game->mShaderManager.LoadShader(L"Shader/MainSceneBasicLayerPixelShader.hlsl", DX12Config::ShaderType::PIXEL, 3);
	_game->mShaderManager.LoadShader(L"Shader/HDrawLineFrameVertexShader.hlsl", DX12Config::ShaderType::VERTEX, 4);
	_game->mShaderManager.LoadShader(L"Shader/HDrawLineFramePixelShader.hlsl", DX12Config::ShaderType::PIXEL, 5);
	_game->mShaderManager.LoadShader(L"Shader/HTextureAlphaRotateDrawVertexShader.hlsl", DX12Config::ShaderType::VERTEX, 6);
	_game->mShaderManager.LoadShader(L"Shader/HTextureAlphaRotateDrawPixelShader.hlsl", DX12Config::ShaderType::PIXEL, 7);
	_game->mShaderManager.LoadShader(L"Shader/DrawNormalBulletComponentVertexShader.hlsl", DX12Config::ShaderType::VERTEX, 8);
	_game->mShaderManager.LoadShader(L"Shader/DrawNormalBulletComponentPixelShader.hlsl", DX12Config::ShaderType::PIXEL, 9);
	_game->mShaderManager.LoadShader(L"Shader/HNumberDraw_vertex.hlsl", DX12Config::ShaderType::VERTEX, 10);
	_game->mShaderManager.LoadShader(L"Shader/HNumberDraw_pixel.hlsl", DX12Config::ShaderType::PIXEL, 11);
	_game->mShaderManager.LoadShader(L"Shader/DrawDeathEffectComponent_vertex.hlsl", DX12Config::ShaderType::VERTEX, 12);
	_game->mShaderManager.LoadShader(L"Shader/DrawDeathEffectComponent_pixel.hlsl", DX12Config::ShaderType::PIXEL, 13);
	_game->mShaderManager.LoadShader(L"Shader/DrawHealthBarComponent_vertex.hlsl", DX12Config::ShaderType::VERTEX, 14);
	_game->mShaderManager.LoadShader(L"Shader/DrawHealthBarComponent_pixel.hlsl", DX12Config::ShaderType::PIXEL, 15);
	_game->mShaderManager.LoadShader(L"Shader/DrawAnimationComponent_vertex.hlsl", DX12Config::ShaderType::VERTEX, 16);
	_game->mShaderManager.LoadShader(L"Shader/DrawAnimationComponent_pixel.hlsl", DX12Config::ShaderType::PIXEL, 17);
	_game->mShaderManager.LoadShader(L"Shader/DrawLazerComponent_vertex.hlsl", DX12Config::ShaderType::VERTEX, 18);
	_game->mShaderManager.LoadShader(L"Shader/DrawLazerComponent_pixel.hlsl", DX12Config::ShaderType::PIXEL, 19);
}