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
	//	//HACK:�v���O�����I�����C�f�X�g���N�^�̎��s���ł��̃n���h���������Ă邩�ۂ������E����C
	//	//���̂悤�ȏꍇ���������邱�Ƃ��K�{�ɂȂ��Ă���
	//	//�Ⴆ��DEBUG_�ł͉�ʏ�Ƀ_���O�����O���Q�Ƃ����s��\������̂݁C
	//	//RELEASE_�ł͓K���ȋ�I�u�W�F�N�g�𑀍삷��悤�ɂ���C�Ȃǂɂ��������悢��?
	//	if (pos_adjust_[n].IsValid()) {
	//		pos_adjust_[n]->SetDeleteFlag();
	//	}
	//}
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
	auto score = mediator_->score_manager_;
	//���_���[�W���X�R�A�ɉ��Z
	score->AddScore(-(int)attack);
	//�c�@��1���炷
	score->ConsumeLife();
	//�c�@������Ε�����Ԃ�mediator_->condition_������
	if (score->IsLifeRemaining()) {
		auto next = mObj->AddUpdateComponent<MyselfRevivingCondition>(mediator_);
		auto next_conv = static_cast<ComponentHandle<MyselfConditionBase>>(next);
		mediator_->SetNextCondition(next_conv);
	}
	else {
		//�I�u�W�F�N�g���̂Ɏ��Ȃ��Ɩʓ|�Ȃ̂ŁC�ړ��������ł��Ȃ����ҏ�ԂɈڍs
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
