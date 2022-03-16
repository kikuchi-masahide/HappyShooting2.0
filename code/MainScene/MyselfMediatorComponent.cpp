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

MyselfMediatorComponent::MyselfMediatorComponent(GameObjectHandle myself, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager)
	:Component(myself, 50), damage_counter_(-1), layer_manager_(layer_manager), score_manager_(score_manager),collision_manager_(collision_manager)
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
}

void MyselfMediatorComponent::CauseDamageToMyself(unsigned int point)
{
	//�U���͂ɑ΂�����_���[�W
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

MyselfMediatorComponent::~MyselfMediatorComponent()
{
}

void MyselfMediatorComponent::SetMyselfAlpha()
{
	//�ʏ펞
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
