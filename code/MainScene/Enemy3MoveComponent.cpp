#include "Enemy3MoveComponent.h"

#include "Math.h"
#include "../Engine/GameObject.h"

Enemy3MoveComponent::Enemy3MoveComponent(GameObjectHandle obj, int counter0, std::function<MatVec::Vector2(double)> lambda, double angle_delta)
	:Component(obj),
	counter_(counter0),lambda_(lambda),angle_delta_(angle_delta)
{
}

Enemy3MoveComponent::~Enemy3MoveComponent()
{
}

void Enemy3MoveComponent::Update()
{
	//HACK:画面中心に敵機がちらつく現象について
	//DrawTextureComponentの本追加自体は正しく遅らせられているが、MainSceneBaseLayerへの命令はコンストラクタ
	//で事前に飛ばされているのが原因。やはり遅延初期化を行わないと解決しなそう
	double angle = angle_delta_*counter_;
	MatVec::Vector2 pos = lambda_(angle);
	mObj->SetPosition(pos);
	mObj->SetRotation(angle);
	//画面外
	double x = pos(0);
	if (abs(x) > 300.0 + 20.0) {
		mObj->SetDeleteFlag();
	}
	counter_++;
}
