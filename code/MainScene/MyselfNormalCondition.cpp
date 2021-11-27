#include "MyselfNormalCondition.h"

#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "MyselfMediatorComponent.h"
#include "MyselfRevivingCondition.h"
#include "MyselfPosAdjustComponent.h"

MyselfNormalCondition::MyselfNormalCondition(GameObjectHandle handle, ComponentHandle<MyselfMediatorComponent> mediator)
	:MyselfConditionBase(handle,mediator)
{
	scene_ = mObj->mScene;
	pos_adjust_[0] = mObj->AddUpdateComponent<MyselfPosAdjustComponent>(mObj, MatVec::Vector2(-300.0, -450.0), MatVec::Vector2(-300.0, +450.0));
	pos_adjust_[1] = mObj->AddUpdateComponent<MyselfPosAdjustComponent>(mObj, MatVec::Vector2(+300.0, -450.0), MatVec::Vector2(-300.0, -450.0));
	pos_adjust_[2] = mObj->AddUpdateComponent<MyselfPosAdjustComponent>(mObj, MatVec::Vector2(+300.0, +450.0), MatVec::Vector2(+300.0, -450.0));
	pos_adjust_[3] = mObj->AddUpdateComponent<MyselfPosAdjustComponent>(mObj, MatVec::Vector2(-300.0, +450.0), MatVec::Vector2(+300.0, +450.0));
}

MyselfNormalCondition::~MyselfNormalCondition()
{
	for (int n = 0; n < 4; n++)
	{
		//HACK:�v���O�����I�����C�f�X�g���N�^�̎��s���ł��̃n���h���������Ă邩�ۂ������E����C
		//���̂悤�ȏꍇ���������邱�Ƃ��K�{�ɂȂ��Ă���
		//�Ⴆ��DEBUG_�ł͉�ʏ�Ƀ_���O�����O���Q�Ƃ����s��\������̂݁C
		//RELEASE_�ł͓K���ȋ�I�u�W�F�N�g�𑀍삷��悤�ɂ���C�Ȃǂɂ��������悢��?
		if (pos_adjust_[n].IsValid()) {
			pos_adjust_[n]->SetDeleteFlag();
		}
	}
}

void MyselfNormalCondition::Update()
{
	//�ړ���̍��W�����߂�
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
	//����ŕ�����Ԃ�mediator_->condition_������
	auto next = mObj->AddUpdateComponent<MyselfRevivingCondition>(mediator_);
	auto next_conv = static_cast<ComponentHandle<MyselfConditionBase>>(next);
	mediator_->SetNextCondition(next_conv);
	return attack;
}

bool MyselfNormalCondition::IsInvincible()
{
	return false;
}
