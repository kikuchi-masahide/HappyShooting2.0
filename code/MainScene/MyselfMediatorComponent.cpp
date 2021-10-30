#include "MyselfMediatorComponent.h"

#include "DrawTextureComponent.h"
#include "MainScene.h"
#include "MyselfAddNormalBulletComponent.h"
#include "MyselfCollisionComponent.h"
#include "MyselfPosAndAngleComponent.h"
#include "MyselfAngleComponent.h"
#include "MyselfNormalCondition.h"

MyselfMediatorComponent::MyselfMediatorComponent(GameObjectHandle myself, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager)
	:Component(myself, 50), damage_counter_(-1), layer_manager_(layer_manager), score_manager_(score_manager),collision_manager_(collision_manager)
{
	draw_texture_component_ = myself->AddOutputComponent<DrawTextureComponent>(layer_manager_, 4, 0);
	draw_texture_component_->width_ = 40;
	draw_texture_component_->height_ = 40;
	mObj->AddUpdateComponent<MyselfAddNormalBulletComponent>(layer_manager_,collision_manager_);
	mObj->AddUpdateComponent<MyselfCollisionComponent>(collision_manager_, This<MyselfMediatorComponent>());
	mObj->AddUpdateComponent<MyselfAngleComponent>(layer_manager_);
	condition_ = static_cast<ComponentHandle<MyselfConditionBase>>(
		mObj->AddUpdateComponent<MyselfNormalCondition>(This<MyselfMediatorComponent>())
	);
}

void MyselfMediatorComponent::Update()
{
}

void MyselfMediatorComponent::CauseDamageToMyself(unsigned int point)
{
	//攻撃力に対する実ダメージ
	int damage = condition_->GetDamaged(point);
	//実ダメージをスコアに加算
	score_manager_->AddScore(-damage);
}

bool MyselfMediatorComponent::IsInvincible()
{
	return condition_->IsInvincible();
}

void MyselfMediatorComponent::SetNextCondition(ComponentHandle<MyselfConditionBase> next_condition)
{
	condition_->SetDeleteFlag();
	condition_ = next_condition;
}

void MyselfMediatorComponent::SetAlpha(double alpha)
{
	draw_texture_component_->alpha_ = alpha;
}

MyselfMediatorComponent::~MyselfMediatorComponent()
{
}

void MyselfMediatorComponent::SetMyselfAlpha()
{
	//通常時
	if (damage_counter_ == -1)
	{
		draw_texture_component_->alpha_ = 1.0;
	}
	else
	{
		double theta = 2 * PI * damage_counter_ / 60;
		draw_texture_component_->alpha_ = 1 - cos(theta);
		if (draw_texture_component_->alpha_ > 1.0)
		{
			draw_texture_component_->alpha_ = 1.0;
		}
		damage_counter_--;
	}
}
