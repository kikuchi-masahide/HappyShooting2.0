#include "stdafx.h"
#include "CollisionManager.h"

#include "CollisionComponent.h"
#include "CircleGeometry.h"
#include "PolygonGeometry.h"
#include "CupsuleGeometry.h"

using CircleGeometry_AABB = std::pair<CircleGeometry*, Rect2>;
using PolygonGeometry_AABB = std::pair<PolygonGeometry*, Rect2>;
using CupsuleGeometry_AABB = std::pair<CupsuleGeometry*, Rect2>;
using Geometry_AABB = std::pair<ICollisionGeometry*, Rect2>;

CollisionManager::CollisionManager(CollisionUIScreen* screen)
	:collision_ui_(screen)
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::TraverseAll()
{
	//敵機側当たり判定からAABB木を構築する
	aabb_tree_.ConstructAABBTree(enemy_aabbs_);
	std::vector<unsigned int> hit_indexs_;
	//自機側を順にチェックし，敵側との当たり判定を行う．
	std::string output("friendly:");
	output += std::to_string(friendly_geometries_.size());
	output += "\nenemy:";
	output += std::to_string(enemy_geometries_.size());
	output += "\n";
	Log::OutputTrivial(output);
	for (int index = 0; index < friendly_geometries_.size(); index++)
	{
		//AABBが衝突した敵側をhit_indexs_に入れる
		aabb_tree_.TraverseAgainst(friendly_aabbs_[index], hit_indexs_);
		for (unsigned int enemy : hit_indexs_)
		{
			if (friendly_geometries_[index]->Dispatch(enemy_geometries_[enemy]))
			{
				//本当に衝突している場合
				NoticeEachOther(friendly_geometries_[index]->GetParent(), enemy_geometries_[enemy]->GetParent());
			}
		}
	}
	//全CheckHitComponentの実行
	for (auto comp : friendly_comps_)
	{
		comp->CheckHitComponent();
		comp->hit_comps_.clear();
	}
	for (auto comp : enemy_comps_)
	{
		comp->CheckHitComponent();
		comp->hit_comps_.clear();
	}
	friendly_geometries_.clear();
	friendly_aabbs_.clear();
	friendly_comps_.clear();
	enemy_geometries_.clear();
	enemy_aabbs_.clear();
	enemy_comps_.clear();
}

void CollisionManager::AddFriendlyGeometry(ICollisionGeometry* geometry)
{
	friendly_geometries_.push_back(geometry);
	friendly_aabbs_.push_back(geometry->GetAABB());
	friendly_comps_.insert(geometry->GetParent());
}

void CollisionManager::AddEnemyGeometry(ICollisionGeometry* geometry)
{
	enemy_geometries_.push_back(geometry);
	enemy_aabbs_.push_back(geometry->GetAABB());
	enemy_comps_.insert(geometry->GetParent());
}

void CollisionManager::NoticeEachOther(ComponentHandle<CollisionComponent> comp1, ComponentHandle<CollisionComponent> comp2)
{
	comp1->hit_comps_.insert(comp2);
	comp2->hit_comps_.insert(comp1);
}