#include "MyselfNormalCondition.h"

#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "MyselfMediatorComponent.h"
#include "MyselfRevivingCondition.h"
#include "MyselfPosAdjustComponent.h"
#include "ScoreManager.h"
#include "MyselfDeadCondition.h"

MyselfNormalCondition::MyselfNormalCondition(GameObjectHandle handle, ComponentHandle<MyselfMediatorComponent> mediator)
	:MyselfConditionBase(handle,mediator)
{
	scene_ = mObj->mScene;
}

MyselfNormalCondition::~MyselfNormalCondition()
{
	//for (int n = 0; n < 4; n++)
	//{
	//	//HACK:プログラム終了時，デストラクタの実行順でこのハンドルが生きてるか否かが左右され，
	//	//このような場合分けをすることが必須になっている
	//	//例えばDEBUG_では画面上にダングリングを参照した行を表示するのみ，
	//	//RELEASE_では適当な空オブジェクトを操作するようにする，などにした方がよいか?
	//	if (pos_adjust_[n].IsValid()) {
	//		pos_adjust_[n]->SetDeleteFlag();
	//	}
	//}
}

void MyselfNormalCondition::Update()
{
	//移動後の座標を求める
	auto after_pos = mObj->GetPosition();
	if (scene_->GetKeyState('A') == ButtonState::Pressed ||
		scene_->GetKeyState('A') == ButtonState::Held)
	{
		after_pos(0) -= moving_dist_;
	}
	if (scene_->GetKeyState('D') == ButtonState::Pressed ||
		scene_->GetKeyState('D') == ButtonState::Held)
	{
		after_pos(0) += moving_dist_;
	}
	if (scene_->GetKeyState('W') == ButtonState::Pressed ||
		scene_->GetKeyState('W') == ButtonState::Held)
	{
		after_pos(1) += moving_dist_;
	}
	if (scene_->GetKeyState('S') == ButtonState::Pressed ||
		scene_->GetKeyState('S') == ButtonState::Held)
	{
		after_pos(1) -= moving_dist_;
	}
	mObj->SetPosition(after_pos);
	mediator_->SetAlpha(1.0);
}

unsigned int MyselfNormalCondition::GetDamaged(unsigned int attack)
{
	auto score = mediator_->score_manager_;
	//実ダメージをスコアに加算
	score->AddScore(-(int)attack);
	//残機を1減らす
	score->ConsumeLife();
	//残機があれば復活状態にmediator_->condition_を譲る
	if (score->IsLifeRemaining()) {
		auto next = mObj->AddUpdateComponent<MyselfRevivingCondition>(mediator_);
		auto next_conv = static_cast<ComponentHandle<MyselfConditionBase>>(next);
		mediator_->SetNextCondition(next_conv);
	}
	else {
		//オブジェクト自体に死なれると面倒なので，移動も何もできない死者状態に移行
		auto dead = mObj->AddUpdateComponent<MyselfDeadCondition>(mediator_);
		auto dead_conv = static_cast<ComponentHandle<MyselfConditionBase>>(dead);
		mediator_->SetNextCondition(dead_conv);
	}
	return attack;
}

bool MyselfNormalCondition::IsInvincible()
{
	return false;
}
