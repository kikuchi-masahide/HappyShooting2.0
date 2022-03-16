#include "Enemy6MediatorComponent.h"

#include "../Engine/GameObject.h"
#include "DrawAnimationComponent.h"
#include "../Engine/Scene.h"
#include "EnemyHealthComponent.h"
#include "DrawHealthBarComponent.h"
#include "Enemy6CollisionComponent.h"
#include "EnemyWaveManager.h"
#include "NormalBulletCollisionComponent.h"
#include "DrawNormalBulletComponent.h"
#include "LinearMoveComponent.h"
#include "MainScene.h"

Enemy6MediatorComponent::Enemy6MediatorComponent(GameObjectHandle _handle, int time, double x0, double y0, double dx, int life, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager, boost::shared_ptr<CollisionManager> collision_manager)
	:Component(_handle,100),
	dx_(dx),life_(life),time_(time),
	layer_manager_(layer_manager),score_manager_(score_manager),
	enemywave_manager_(enemywave_manager),collision_manager_(collision_manager)
{
	animation_ = mObj->AddOutputComponent<DrawAnimationComponent>(layer_manager,26,80,80,8,15,-5.0,MatVec::Vector2(),120);
	animation_->counter_ = time_ - 1;
	//ヘルス表示もクローンさせたいので、一回初期体力をあげたうえで減らす
	health_ = mObj->AddUpdateComponent<EnemyHealthComponent>(layer_manager_, life0_);
	health_->Damage(life0_ - life_);
	mObj->AddOutputComponent<DrawHealthBarComponent<EnemyHealthComponent>>(
		layer_manager_, health_, MatVec::Vector2(0, 48)
		);
	mObj->AddUpdateComponent<Enemy6CollisionComponent>(collision_manager_, score_manager, health_, time_);
	enemywave_manager_->AddEnemyInWave(mObj);
	//TODO:EnemyWave6を初期化中にこれ呼ぶと、nullを参照して死ぬ
	//いっそ敵機の配列はmanager_に持たせるか?とするとEnemyWaveBaseの存在意義は?
}

Enemy6MediatorComponent::~Enemy6MediatorComponent()
{
	DeathAttack();
}

void Enemy6MediatorComponent::Update()
{
	auto pos = mObj->GetPosition();
	pos(0) += dx_;
	pos(1) += dy_;
	mObj->SetPosition(pos);
	
	if (time_ == lifetime_)
	{
		//死亡演出のために、自分にダメージを入れる
		health_->Damage(life0_);
		mObj->SetDeleteFlag();
	}

	if ((time_ + 1) % clone_cycle_ == 0 && time_ != lifetime_)
	{
		Clone();
	}

	time_++;
	animation_->counter_++;
}

void Enemy6MediatorComponent::Clone()
{
	auto scene = mObj->mScene;
	auto pos = mObj->GetPosition();
	auto obj = scene->AddObject(pos, 1.0, 0.0);
	double x0 = pos(0);
	double y0 = pos(0);
	obj->AddUpdateComponent<Enemy6MediatorComponent>(time_ + 1, x0, y0, -dx_ * 0.75, health_->GetHealth(),
		layer_manager_, score_manager_, enemywave_manager_, collision_manager_);
}

void Enemy6MediatorComponent::DeathAttack()
{
	auto mypos = mObj->GetPosition();
	//速い小さな弾
	for (int n = 0; n < 32; n++)
	{
		auto obj = mObj->mScene->AddObject(mypos, 1.0, 0.0);
		if (obj.IsValid()) {
			obj->AddUpdateComponent<NormalBulletCollisionComponent>(10.0, 100, collision_manager_);
			obj->AddOutputComponent<DrawNormalBulletComponent>(layer_manager_, 10.0, MatVec::Vector3(1.0, 0.0, 0.0), 1.0, -10.0);
			obj->AddUpdateComponent<LinearMoveComponent>(MatVec::Vector2(cos(PI * n / 16), sin(PI * n / 16)) * 20 * 25 / 60, 10.0);
		}
	}
	//遅い大きな弾
	for (int n = 0; n < 8; n++)
	{
		auto obj = mObj->mScene->AddObject(mypos, 1.0, 0.0);
		if (obj.IsValid()) {
			obj->AddUpdateComponent<NormalBulletCollisionComponent>(40.0, 100, collision_manager_);
			obj->AddOutputComponent<DrawNormalBulletComponent>(layer_manager_, 40.0, MatVec::Vector3(0.0, 1.0, 0.0), 1.0, -10.0);
			obj->AddUpdateComponent<LinearMoveComponent>(MatVec::Vector2(cos(PI * n / 4), sin(PI * n / 4)) * 10 * 25 / 60, 40.0);
		}
		//TODO:自機が死んだとき、透明にならなくなっていませんか?
	}
}
