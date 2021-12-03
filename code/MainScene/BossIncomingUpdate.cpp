#include "BossIncomingUpdate.h"

#include "../Engine/GameObject.h"
#include "DrawTextureComponent.h"
#include "DrawSquareRepeatPattern.h"

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
	square_up_ = mObj->AddOutputComponent<DrawSquareRepeatPattern>(layer_manager, 10.0, 23, 60.0, 30.0);
	square_up_->square_width_ = 600.0;
	square_up_->square_height_ = 30.0;
	square_down_ = mObj->AddOutputComponent<DrawSquareRepeatPattern>(layer_manager, 10.0, 23, 60.0, 30.0);
	square_down_->square_width_ = 600.0;
	square_down_->square_height_ = 30.0;
}

BossIncomingUpdate::~BossIncomingUpdate()
{
}

void BossIncomingUpdate::Update()
{
	double alpha = abs(sin(PI * counter_ / 60));
	danger_mark_->alpha_ = alpha;
	boss_incoming_->alpha_ = alpha;
	square_up_->alpha_ = alpha;
	square_down_->alpha_ = alpha;
	square_up_->center_ = MatVec::Vector2(-300.0 + 5.0 * counter_, square_up_centery_);
	square_down_->center_ = MatVec::Vector2(300.0 - 5.0 * counter_, square_down_centery_);
	counter_++;
	if (counter_ == 240)
	{
		mObj->SetDeleteFlag();
	}
}
