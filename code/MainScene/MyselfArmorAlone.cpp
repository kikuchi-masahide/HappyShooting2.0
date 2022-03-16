#include "MyselfArmorAlone.h"

#include "MyselfMediatorComponent.h"
#include "DrawTextureComponent.h"
#include "MyselfAddNormalBulletComponent.h"

MyselfArmorAlone::MyselfArmorAlone(ComponentHandle<MyselfMediatorComponent> med, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col)
	:MyselfArmorBase()
{
	texture_ = med->mObj->AddOutputComponent<DrawTextureComponent>(layer, 4, 0);
	texture_->width_ = 40;
	texture_->height_ = 40;

	add_bullet_ = med->mObj->AddUpdateComponent<MyselfAddNormalBulletComponent>(layer, col);
}

MyselfArmorAlone::~MyselfArmorAlone()
{
	if (texture_.IsValid())
	{
		texture_->SetDeleteFlag();
	}
	if (add_bullet_.IsValid()) {
		add_bullet_->SetDeleteFlag();
	}
}

void MyselfArmorAlone::Update()
{
}

void MyselfArmorAlone::UpdateAlpha(double alpha)
{
	texture_->alpha_ = alpha;
}

void MyselfArmorAlone::SetBulletAvailability(bool act)
{
	add_bullet_->is_active_ = act;
}
