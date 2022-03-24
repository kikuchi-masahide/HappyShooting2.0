#include "Boss2State0BulletBig.h"

#include "LayerManager.h"
#include "CollisionComponent.h"
#include "../Engine/Scene.h"
#include "DrawNormalBulletComponent.h"
#include "NormalBulletCollisionComponent.h"
#include "Boss2State0BulletSmall.h"

Boss2State0BulletBig::Boss2State0BulletBig(GameObjectHandle obj, bool inv, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager)
	:Component(obj,0),
	layer_(layer_manager),collision_(collision_manager)
{
	//右から左
	if (!inv)
	{
		mObj->SetPosition(MatVec::Vector2(300 - bullet_radius_, 450 + bullet_radius_));
		bullet_dx_ = bullet_dx0_;
	}
	//左から右
	else {
		mObj->SetPosition(MatVec::Vector2(-300 + bullet_radius_, 450 + bullet_radius_));
		bullet_dx_ = -bullet_dx0_;
	}
	mObj->AddOutputComponent<DrawNormalBulletComponent>(layer_, bullet_radius_, MatVec::Vector3(1.0, 0.5, 0.0), 1.0, -10.0);
	mObj->AddUpdateComponent<NormalBulletCollisionComponent>(bullet_radius_, 100, collision_);
}

Boss2State0BulletBig::~Boss2State0BulletBig()
{
}

void Boss2State0BulletBig::Update()
{
	//乱数
	static std::random_device seed_gen;
	static std::mt19937 engine(seed_gen());
	//[-1,1)乱数
	static std::uniform_real_distribution<> dist(-1.0, 1.0);
	auto pos = mObj->GetPosition();
	//自身の内部から小球を湧かせる
	if (time_ % bullet_period_ == 0)
	{
		auto scene = mObj->mScene;
		for (int k = 0; k < bullet_num_per_; k++)
		{
			//小球の位置をランダムに決める
			double x, y;
			while (true)
			{
				x = dist(engine) * bullet_radius_;
				y = dist(engine) * bullet_radius_;
				if (x * x + y * y <= bullet_radius_ * bullet_radius_)
				{
					break;
				}
			}
			auto bullet = scene->AddObject(pos + MatVec::Vector2(x, y), 1.0, 0.0);
			//初期化、更新は任せる
			bullet->AddUpdateComponent<Boss2State0BulletSmall>(layer_, collision_);
		}
	}
	//移動処理
	pos(0) += bullet_dx_;
	pos(1) += bullet_dy_;
	//反射
	if (pos(0) >= 300-bullet_radius_)
	{
		pos(0) = 2 * (300 + bullet_radius_) - pos(0);
		bullet_dx_ *= -1;
	}
	if (pos(0) <= -300 + bullet_radius_)
	{
		pos(0) = -2 * (300 + bullet_radius_) - pos(0);
		bullet_dx_ *= -1;
	}
	mObj->SetPosition(pos);
	if (pos(1) <= -450 - bullet_radius_)
	{
		mObj->SetDeleteFlag();
	}
}

const int Boss2State0BulletBig::bullet_period_ = 2;
const int Boss2State0BulletBig::bullet_num_per_ = 3;
const double Boss2State0BulletBig::bullet_dx0_ = -240.0 / 60;
const double Boss2State0BulletBig::bullet_dy_ = -240.0 / 60;
const double Boss2State0BulletBig::bullet_radius_ = 60.0;
