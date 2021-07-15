#pragma once
#include "Component.h"

class MainScene;

class MainSceneDrawComponent :public Component
{
public:
	MainSceneDrawComponent(GameObjectHandle object, MainScene* scene);
	void Update() final;
	virtual ~MainSceneDrawComponent();
	/// <summary>
	/// Updateでシーンに自分のハンドルが投げられた後レイヤーから呼び出される，描画機能本体を担う関数．SRVは開いているとしてよい．
	/// </summary>
	virtual void Draw() = 0;
protected:
	MainScene* scene_;
};