#include "MyselfArmor2.h"

#include "MyselfMediatorComponent.h"
#include "DrawAnimationComponent.h"
#include "MyselfAddNormalBulletComponent.h"
#include "MyselfAddAimBulletComponent.h"


MyselfArmor2::MyselfArmor2(ComponentHandle<MyselfMediatorComponent> med, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col, boost::shared_ptr<EnemyWaveManager> enemy)
	:MyselfArmorBase(),
	layer_(layer),collision_(col),enemy_(enemy),time_(0),is_bullet_active_(true)
{
	auto obj = med->mObj;
	animation_ = obj->AddOutputComponent<DrawAnimationComponent>(layer_, 27, 40.0, 100.0, 12, 15, 0.0, MatVec::Vector2(), 180);
	normal_bullet_ = obj->AddUpdateComponent<MyselfAddNormalBulletComponent>(layer, col);
	aim_bullet_ = obj->AddUpdateComponent<MyselfAddAimBulletComponent>(layer_, collision_, enemy_);
	aim_bullet_->is_active_ = false;
}

MyselfArmor2::~MyselfArmor2()
{
	if (animation_.IsValid())
	{
		animation_->SetDeleteFlag();
	}
	if (normal_bullet_.IsValid())
	{
		normal_bullet_->SetDeleteFlag();
	}
	if (aim_bullet_.IsValid())
	{
		aim_bullet_->SetDeleteFlag();
	}
}

void MyselfArmor2::Update()
{
	normal_bullet_->is_active_ = is_bullet_active_;
	if (time_ < 180)
	{
		animation_->counter_ = time_;
		time_++;
		if (time_ == 180)
		{
			aim_bullet_->is_active_ = is_bullet_active_;
		}
	}
	else {
		aim_bullet_->is_active_ = is_bullet_active_;
	}
}

void MyselfArmor2::UpdateAlpha(double alpha)
{
	animation_->alpha_ = alpha;
}

void MyselfArmor2::SetBulletAvailability(bool act)
{
	//両コンポーネントの実際の設定はUpdateで行う
	is_bullet_active_ = act;
}

void MyselfArmor2::SetProgradePlay()
{
	normal_bullet_->SetProgradePlay();
	aim_bullet_->SetProgradePlay();
}

void MyselfArmor2::SetRetrogradePlay(unsigned int speed)
{
	normal_bullet_->SetRetrogradePlay(speed);
	aim_bullet_->SetRetrogradePlay(speed);
}
