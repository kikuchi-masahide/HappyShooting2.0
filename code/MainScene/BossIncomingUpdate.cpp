#include "BossIncomingUpdate.h"

#include "../Engine/GameObject.h"
#include "DrawTextureComponent.h"

BossIncomingUpdate::BossIncomingUpdate(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager)
	:Component(handle)
{
	danger_mark_ = mObj->AddOutputComponent<DrawTextureComponent>(layer_manager, 21, 10.0);
	danger_mark_->center_offset_ = MatVec::Vector2(danger_mark_centerx_, danger_mark_centery_);
	danger_mark_->alpha_ = 0.0;
	danger_mark_->width_ = 100.0;
	danger_mark_->height_ = 100.0;
	boss_incoming_ = mObj->AddOutputComponent<DrawTextureComponent>(layer_manager, 22, 10.0);
	boss_incoming_->center_offset_ = MatVec::Vector2(boss_incoming_centerx_, boss_incoming_centery_);
	boss_incoming_->alpha_ = 0.0;
	boss_incoming_->width_ = 400.0;
	boss_incoming_->height_ = 60.0;
}

BossIncomingUpdate::~BossIncomingUpdate()
{
}

void BossIncomingUpdate::Update()
{
	double alpha = abs(sin(PI * counter_ / 60));
	danger_mark_->alpha_ = alpha;
	boss_incoming_->alpha_ = alpha;
	counter_++;
	if (counter_ == 240)
	{
		mObj->SetDeleteFlag();
	}
}
