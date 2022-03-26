#include "Boss2State3.h"

#include "Boss2Mediator.h"
#include "MyselfMediatorComponent.h"
#include "../Engine/Scene.h"
#include "Boss2State3Bullet.h"
#include "Boss2State0.h"

Boss2State3::Boss2State3(ComponentHandle<Boss2MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager)
	:Boss2StateBase(mediator,layer_manager,score_manager,collision_manager,enemywave_manager),
	time_(-120)
{
}

Boss2State3::~Boss2State3()
{
	if (mediator_.IsValid()) {
		if (mediator_->myself_mediator_.IsValid()) {
			mediator_->myself_mediator_->SetProgradePlay();
		}
		mediator_->mObj->SetPosition(MatVec::Vector2(0, 390));
	}
}

void Boss2State3::Update()
{
	//TODO:���ň�
	//�n�߂�2�b��(0,390)����^�񒆂Ɉړ�
	if (time_ < 0)
	{
		double y = 390.0 * (-time_) / 120;
		mediator_->mObj->SetPosition(MatVec::Vector2(0, y));
	}
	//<240:Wave0,1��g�ݗ��Ăċt�Đ�
	else if(time_ < 240){
		if (time_ < 60 && time_ % bullet_gen_freq_ == 0)
		{
			GenerateBullets(0, time_ / bullet_gen_freq_);
			GenerateBullets(1, time_ / bullet_gen_freq_);
		}
	}
	//<360:2�{���ŋt�Đ�
	else if (time_ < 360)
	{
		if (time_ == 240)
		{
			SetRetrogradePlay(2);
		}
	}
	//<420:Wave0,1��g�ݗ���
	//<480:Wave2��g�ݗ���
	else if (time_ < 660)
	{
		if (time_ == 360)
		{
			SetProgradePlay();
		}
		if (time_ < 420)
		{
			if ((time_ - 360) % bullet_gen_freq_ == 0)
			{
				GenerateBullets(0, (time_ - 360) / bullet_gen_freq_);
				GenerateBullets(1, (time_ - 360) / bullet_gen_freq_);
			}
		}
		else if (time_ < 480)
		{
			if ((time_ - 420) % bullet_gen_freq_ == 0)
			{
				GenerateBullets(2, (time_ - 420) / bullet_gen_freq_);
			}
		}
	}
	//<810:�t�Đ�
	else if (time_ < 810)
	{
		if (time_ == 660)
		{
			SetRetrogradePlay(2);
		}
	}
	//<870:Wave0,1��g�ݗ���
	//<930:Wave2,3��g�ݗ���
	//<990:Wave4��g�ݗ���
	else if (time_ < 1170)
	{
		if (time_ == 810)
		{
			SetProgradePlay();
		}
		if (time_ < 870)
		{
			if ((time_ - 810) % bullet_gen_freq_ == 0)
			{
				GenerateBullets(0, (time_ - 810) / bullet_gen_freq_);
				GenerateBullets(1, (time_ - 810) / bullet_gen_freq_);
			}
		}
		else if (time_ < 930)
		{
			if ((time_ - 870) % bullet_gen_freq_ == 0)
			{
				GenerateBullets(2, (time_ - 870) / bullet_gen_freq_);
				GenerateBullets(0, (time_ - 870) / bullet_gen_freq_);
			}
		}
		else if (time_ < 990)
		{
			if ((time_ - 930) % bullet_gen_freq_ == 0)
			{
				GenerateBullets(1, (time_ - 930) / bullet_gen_freq_);
				GenerateBullets(2, (time_ - 930) / bullet_gen_freq_);
			}
		}
	}
	//<1350:�t�Đ�
	else if (time_ < 1350)
	{
		if (time_ == 1170)
		{
			SetRetrogradePlay(2);
		}
	}
	//���̈ʒu�ɋA��
	else if (time_ < 1470)
	{
		if (time_ == 1350) {
			SetProgradePlay();
		}
		double y = 390.0 * (time_ - 1350) / 120;
		mediator_->mObj->SetPosition(MatVec::Vector2(0, y));
	}
	time_++;
	if (time_ == 1470)
	{
		mediator_->ChangeState(boost::shared_ptr<Boss2State0>(DBG_NEW Boss2State0(
			mediator_, layer_manager_, score_manager_, collision_manager_, enemywave_manager_)));
	}
}

bool Boss2State3::IsCollisionActive()
{
	return true;
}

bool Boss2State3::IsInvincible()
{
	return false;
}

void Boss2State3::GenerateBullets(int n, int m)
{
	//TODO:�t�@�C������CSV�ŋȐ���ǂݍ���ŉ��킹��`���ɂ��Ȃ��������Ƃ�{�C�Ō�����Ă�
	//�u����Ȓe���̌����ڂɋÂ�C�Ȃ����������ł������v�Ƃ��r�߂����ƌ����ĂĂ����܂���ł���
	auto scene = mediator_->mObj->mScene;
	//�܊p�`�����ڂ��锼�a�����߂�
	static const double ratio = (1.0 + sin(PI / 5)) / cos(PI / 5);
	//��n���̊�ƂȂ鐳�܊p�`�����ڂ���~�̔��a�́Ar0*(ratio^(n-1))
	double r = r0_;
	//��n���ł́A1�̒��_�ɂ����̒e�𐶐����邩
	int K = 60 / bullet_gen_freq_;
	//��m�Q���A1�̒��_����o��e�̂���p��~q-1�ڂł���
	int p = m;
	int q = m + 1;
	for (int nn = 0; nn < n; nn++)
	{
		r *= ratio;
		K *= 2;
		p *= 2;
		q *= 2;
	}
	//��Ƃ��鐳�܊p�`�̒��_����ǂꂭ�炢���ꂽ�ʒu�ɒe��u����
	double s = r * sin(PI / 5);
	//���܊p�`�̒��_�̕Ίp
	//�����̎���"�����"�̐��܊p�`�A���"������" ���邲�Ƃ�2PI/5�𑫂��Ă���
	double arg0;
	if (n % 2 == 0)
	{
		arg0 = PI / 2;
	}
	else {
		arg0 = -PI / 2;
	}
	//nn�ڂ̒��_�ɂ���
	for (int nn = 0; nn < 5; nn++)
	{
		//���܊p�`�̒��_
		auto vert = r * MatVec::Vector2(cos(arg0), sin(arg0));
		//���_���猩���Ƃ��́A�e��z�u����Ίp�͈̔͂́Aarg0+[-7PI/10,7PI/10)
		//�]���āA�������̏ꍇ�Ai�ڂ̒e��arg0-7PI/10+(7PI/5)*(i/K)
		//����̏ꍇ�Aarg0-7PI/10+(7PI/5)*(1-i/K)
		for (int i = p; i < q; i++)
		{
			double arg;
			if (n % 2 == 0) {
				arg = arg0 - PI * 7 / 10 + PI * 7 * i / (5 * K);
			}
			else {
				arg = arg0 - PI * 7 / 10 + PI * 7 * (K - i) / (5 * K);
			}
			auto pos = vert + s * MatVec::Vector2(cos(arg), sin(arg));
			auto bullet = scene->AddObject(pos, 1.0, 0.0);
			auto med = bullet->AddUpdateComponent<Boss2State3Bullet>(layer_manager_, collision_manager_);
			bullets_.push_back(med);
		}
		arg0 += PI * 2 / 5;
	}
}

void Boss2State3::SetProgradePlay()
{
	mediator_->myself_mediator_->SetProgradePlay();
	for (auto itr = bullets_.begin(); itr != bullets_.end();)
	{
		if (itr->IsValid())
		{
			(*itr)->SetProgradePlay();
			itr++;
		}
		else {
			itr = bullets_.erase(itr);
		}
	}
}

void Boss2State3::SetRetrogradePlay(unsigned int speed)
{
	if (speed != 0)
	{
		mediator_->myself_mediator_->SetRetrogradePlay(speed);
		for (auto itr = bullets_.begin(); itr != bullets_.end();)
		{
			if (itr->IsValid())
			{
				(*itr)->SetRetrogradePlay(speed);
				itr++;
			}
			else
			{
				itr = bullets_.erase(itr);
			}
		}
	}
}

const double Boss2State3::r0_ = 40.0;
const int Boss2State3::bullet_gen_freq_ = 10;
