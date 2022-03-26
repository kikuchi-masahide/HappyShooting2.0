#include "MyselfAddAimBulletComponent.h"

#include "EnemyWaveManager.h"
#include "../Engine/Scene.h"
#include "LinearMoveRevComponent.h"
#include "MyBulletCollisionComponent.h"
#include "DrawNormalBulletComponent.h"

MyselfAddAimBulletComponent::MyselfAddAimBulletComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col, boost::shared_ptr<EnemyWaveManager> enemy)
	:Component(handle,30),
	layer_(layer),collision_(col),enemy_(enemy),time_(0),speed_(1)
{
}

MyselfAddAimBulletComponent::~MyselfAddAimBulletComponent()
{
}

void MyselfAddAimBulletComponent::Update()
{
	if (time_ % period_to_fire_ == 0)
	{
		if (is_active_ && speed_ == 1)
		{
			auto enemy = enemy_->SolveNearestEnemy();
			//2対のサイドから一個ずつ弾を出す
			ShootFrom(1, enemy);
			ShootFrom(-1, enemy);
		}
		time_ = 0;
		for (auto itr = bullets_.begin(); itr != bullets_.end();)
		{
			if (!itr->IsValid())
			{
				itr = bullets_.erase(itr);
			}
			else {
				itr++;
			}
		}
	}
	time_ += speed_;
}

void MyselfAddAimBulletComponent::SetProgradePlay()
{
	speed_ = 1;
	for (auto itr = bullets_.begin(); itr != bullets_.end(); itr++)
	{
		if (itr->IsValid())
		{
			(*itr)->SetProgradePlay();
		}
	}
}

void MyselfAddAimBulletComponent::SetRetrogradePlay(unsigned int speed)
{
	if (speed != 0)
	{
		speed_ = -(int)(speed);
		for (auto itr = bullets_.begin(); itr != bullets_.end(); itr++)
		{
			if (itr->IsValid())
			{
				(*itr)->SetRetrogradePlay(speed);
			}
		}
	}
}

void MyselfAddAimBulletComponent::ShootFrom(int i, GameObjectHandle to)
{
	auto myangle = mObj->GetRotation();
	//この自機傍機の、弾が出る中心位置
	auto sidepos = mObj->GetPosition() + MatVec::Vector2(cos(myangle + PI * i / 2), sin(myangle + PI * i / 2)) * 40.0;
	//弾の飛んでく方向ベクトル
	//近くの敵がいなかった場合はまっすぐにしておく
	double shootang = PI / 2;
	auto dist = MatVec::Vector2(0, moving_dist_);
	if (to.IsValid()) {
		auto enemypos = to->GetPosition();
		//弾の飛んでく角度・方向ベクトル
		shootang = atan2(enemypos(1) - sidepos(1), enemypos(0) - sidepos(0));
		dist = MatVec::Vector2(cos(shootang), sin(shootang)) * moving_dist_;
	}
	auto bullet = mObj->mScene->AddObject(sidepos, 1.0, shootang);
	auto move = bullet->AddUpdateComponent<LinearMoveRevComponent>(dist, bullet_redius_);
	bullet->AddUpdateComponent<MyBulletCollisionComponent>(collision_, 100, bullet_redius_);
	bullet->AddOutputComponent<DrawNormalBulletComponent>(
		layer_, bullet_redius_, MatVec::Vector3(0.0, 0.0, 1.0), 1.0, 10.0
	);
	bullets_.push_back(move);
}


