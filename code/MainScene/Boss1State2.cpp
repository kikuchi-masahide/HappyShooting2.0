#include "Boss1State2.h"

#include "Boss1MediatorComponent.h"
#include "../Engine/GameObject.h"
#include "../Engine/Scene.h"
#include "Boss1StateNormal.h"
#include "Boss1State2Bullet.h"
#include "EnemyWaveManager.h"
#include "LayerManager.h"

Boss1State2::Boss1State2(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager)
	:Boss1StateBase(mediator, layer_manager, score_manager, collision_manager,enemywave_manager),
	counter_(initial_counter_)
{
	Log::OutputTrivial("Boss1State2::Boss1State2()");
}

Boss1State2::~Boss1State2()
{
	//ì‚Á‚½’e‚ğ‚·‚×‚Ä‚Ü‚í‚èCÁ‚µ‚«‚ê‚Ä‚È‚¢‚à‚Ì‚ğÁ‚·
	for (auto& handle : bullets)
	{
		if (handle.IsValid())
		{
			handle->SetDeleteFlag();
		}
	}
	layer_manager_->SwapLayer(0);
}

void Boss1State2::Update()
{
	if (counter_ >= 0 && counter_ <= bulletspawn_timelag_ * (bullet_num_y_ - 1) && counter_ % bulletspawn_timelag_ == 0)
	{
		if (counter_ == 0)
		{
			layer_manager_->SwapLayer(1);
		}
		auto scene = mediator_->mObj->mScene;
		auto myself_pos = enemywave_manager_->GetMyselfHandle()->GetPosition();
		//’e‚ğ’Ç‰Á‚·‚é
		//ã‚©‚ç‰½—ñ–Ú‚Ì’e‚ğ’Ç‰Á‚·‚é‚©(1”Ôã‚Í1—ñ–Ú)
		int row = counter_ / bulletspawn_timelag_+1;
		double y = 450.0 - 900.0 * (row - 1) / (bullet_num_y_ - 1);
		for (int n = 1; n <= bullet_num_x_; n++)
		{
			double x = -300.0 + 600.0 * (n - 1) / (bullet_num_x_ - 1);
			auto pos = MatVec::Vector2(x, y);
			if ((myself_pos - pos).Norm2() <= spawn_admited_ratio_ * spawn_admited_ratio_)
			{
				continue;
			}
			bullets.push_back(scene->AddObject(MatVec::Vector2(x, y), 1.0, 0.0));
			bullets.back()->AddUpdateComponent<Boss1State2Bullet>(collision_manager_, layer_manager_);
		}
	}
	if (counter_ == terminal_counter_ - 1)
	{
		mediator_->ChangeState(DBG_NEW Boss1StateNormal(mediator_, layer_manager_, score_manager_, collision_manager_,enemywave_manager_,1));
	}
	counter_++;
}

bool Boss1State2::IsCollisionActive()
{
	return true;
}

bool Boss1State2::IsInvincible()
{
	return false;
}
