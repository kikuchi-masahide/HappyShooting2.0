#include "MyselfMediatorComponent.h"

#include "DrawTextureComponent.h"
#include "MainScene.h"
#include "MyselfAddNormalBulletComponent.h"
#include "MyselfCollisionComponent.h"
#include "MyselfPosAndAngleComponent.h"
#include "MyselfAngleComponent.h"
#include "MyselfNormalCondition.h"
#include "MyselfPosAdjustComponent.h"
#include "MyselfArmorAlone.h"
#include "MyselfArmor2.h"
#include "MyselfNormalCondition.h"
#include "MyselfRetrogradeCondition.h"

MyselfMediatorComponent::MyselfMediatorComponent(GameObjectHandle myself, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemy)
	:Component(myself, 50),
	damage_counter_(-1), layer_manager_(layer_manager), score_manager_(score_manager),
	collision_manager_(collision_manager),enemy_wave_manager_(enemy),retrograde_speed_(-1)
{
	mObj->AddUpdateComponent<MyselfCollisionComponent>(collision_manager_, This<MyselfMediatorComponent>());
	mObj->AddUpdateComponent<MyselfAngleComponent>(layer_manager_);
	condition_ = static_cast<ComponentHandle<MyselfConditionBase>>(
		mObj->AddUpdateComponent<MyselfNormalCondition>(This<MyselfMediatorComponent>())
	);
	pos_adjust_[0] = mObj->AddUpdateComponent<MyselfPosAdjustComponent>(mObj, MatVec::Vector2(-300.0, -450.0), MatVec::Vector2(-300.0, +450.0));
	pos_adjust_[1] = mObj->AddUpdateComponent<MyselfPosAdjustComponent>(mObj, MatVec::Vector2(+300.0, -450.0), MatVec::Vector2(-300.0, -450.0));
	pos_adjust_[2] = mObj->AddUpdateComponent<MyselfPosAdjustComponent>(mObj, MatVec::Vector2(+300.0, +450.0), MatVec::Vector2(+300.0, -450.0));
	pos_adjust_[3] = mObj->AddUpdateComponent<MyselfPosAdjustComponent>(mObj, MatVec::Vector2(-300.0, +450.0), MatVec::Vector2(+300.0, +450.0));
	armor_ = boost::shared_ptr<MyselfArmorAlone>(new MyselfArmorAlone(This<MyselfMediatorComponent>(), layer_manager_, collision_manager_));
}

void MyselfMediatorComponent::Update()
{
	armor_->SetBulletAvailability(condition_->IsShooterActive());
	armor_->Update();
	//順行再生中ならば、位置・角度を保存
	if (retrograde_speed_ == -1) {
		pos_transition_.push_back(mObj->GetPosition());
		angle_transition_.push_back(mObj->GetRotation());
		if (pos_transition_.size() > transition_max_length_)
		{
			pos_transition_.pop_front();
			angle_transition_.pop_front();
		}
	}
	//逆行再生中なので、記録を読み捨てて位置・角度を戻す
	else {
		int n = min(retrograde_speed_ - 1, pos_transition_.size());
		for (; n > 0; n--)
		{
			pos_transition_.pop_back();
			angle_transition_.pop_back();
		}
		mObj->SetPosition(pos_transition_.back());
		mObj->SetRotation(angle_transition_.back());
		pos_transition_.pop_back();
		angle_transition_.pop_back();
	}
}

void MyselfMediatorComponent::CauseDamageToMyself(unsigned int point)
{
	//攻撃力に対する実ダメージ
	int damage = condition_->GetDamaged(point);
}

void MyselfMediatorComponent::SetNextCondition(ComponentHandle<MyselfConditionBase> next_condition)
{
	condition_->SetDeleteFlag();
	condition_ = next_condition;
}

void MyselfMediatorComponent::SetAlpha(double alpha)
{
	armor_->UpdateAlpha(alpha);
}

void MyselfMediatorComponent::CheckHitComponent(std::set<ComponentHandle<CollisionComponent>>& hit_comps_)
{
	condition_->CheckHitComponent(hit_comps_);
}

void MyselfMediatorComponent::SetMyselfArmor2()
{
	armor_ = boost::shared_ptr<MyselfArmor2>(new MyselfArmor2(
		This<MyselfMediatorComponent>(), layer_manager_, collision_manager_, enemy_wave_manager_
	));
}

void MyselfMediatorComponent::AddLife(int n)
{
	if (condition_->IsShooterActive()) {
		score_manager_->AddLife(n);
	}
}

void MyselfMediatorComponent::SetProgradePlay()
{
	retrograde_speed_ = -1;
	//Stateをとりあえず普通に戻しておく
	auto normal = mObj->AddUpdateComponent<MyselfNormalCondition>(This<MyselfMediatorComponent>());
	SetNextCondition(static_cast<ComponentHandle<MyselfConditionBase>>(normal));
	armor_->SetProgradePlay();
}

void MyselfMediatorComponent::SetRetrogradePlay(unsigned int speed)
{
	if (retrograde_speed_ >= 0) {
		return;
	}
	retrograde_speed_ = speed;
	auto ret = mObj->AddUpdateComponent<MyselfRetrogradeCondition>(This<MyselfMediatorComponent>(), speed);
	SetNextCondition(static_cast<ComponentHandle<MyselfConditionBase>>(ret));
	armor_->SetRetrogradePlay(speed);
}

MyselfMediatorComponent::~MyselfMediatorComponent()
{
}

const int MyselfMediatorComponent::transition_max_length_ = 480;
