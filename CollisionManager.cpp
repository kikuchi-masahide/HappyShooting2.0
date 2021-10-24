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
	//AABB�̍�x���W�����ŕ��ёւ�
	std::sort(geometries_.begin(), geometries_.end(), [](const Geometry_AABB& left, const Geometry_AABB& right) {
		const Rect2& left_aabb = left.second;
		const Rect2& right_aabb = right.second;
		return left_aabb.GetLD()(0) < right_aabb.GetLD()(0);
	});
	//�SCollisionComponent�̏W��
	std::set<ComponentHandle<CollisionComponent>> all_comps;

	//�S�}�`�̓����蔻��
	for (int n = 0; n < geometries_.size(); n++)
	{
		all_comps.insert(geometries_[n].first->GetParent());
		TraverseAllAgainst(n);
	}

	for (auto comp : all_comps)
	{
		comp->CheckHitComponent();
		comp->hit_comps_.clear();
	}
	geometries_.clear();
}

void CollisionManager::AddGeometry(ICollisionGeometry* geometry)
{
	geometries_.emplace_back(geometry, geometry->GetAABB());
}

void CollisionManager::NoticeEachOther(ComponentHandle<CollisionComponent> comp1, ComponentHandle<CollisionComponent> comp2)
{
	comp1->hit_comps_.insert(comp2);
	comp2->hit_comps_.insert(comp1);
}

void CollisionManager::TraverseAllAgainst(int target)
{
	//geometries_[target].AABB�Ex
	double aabb_target_rightx = geometries_[target].second.GetRU()(0);
	//geometries_[s].AABB��x <= geometries_[target].AABB�Ex < geometries_[e].AABB��x
	int s = target, e = geometries_.size();
	while (e - s > 1)
	{
		int m = (e + s) / 2;
		double aabb_m_leftx = geometries_[m].second.GetLD()(0);
		if (aabb_m_leftx <= aabb_target_rightx)
		{
			s = m;
		}
		else {
			e = m;
		}
	}
	//�������₪����Ȃ�
	if (s == target)
	{
		return;
	}
	double aabb_target_leftx = geometries_[target].second.GetLD()(0);
	double aabb_target_upy = geometries_[target].second.GetRU()(1);
	double aabb_target_downy = geometries_[target].second.GetLD()(1);
	ComponentHandle<CollisionComponent> parent = geometries_[target].first->GetParent();
	//geometries_[target+1]~geometries_[s]�̓����蔻��
	for (int n = target + 1; n <= s; n++)
	{
		auto* geometry2 = geometries_[n].first;
		Rect2& aabb2 = geometries_[n].second;
		//y���W�ł͂�����ꍇ
		if (
			aabb2.GetLD()(1) > aabb_target_upy ||
			aabb2.GetRU()(1) < aabb_target_downy
			)
		{
			continue;
		}
		//�e�������ꍇ�������蔻����s��Ȃ�
		ComponentHandle<CollisionComponent> parent2 = geometry2->GetParent();
		if (parent == parent2)
		{
			continue;
		}
		//TODO:...
		//���@�e���m�C�G�e���m�Ȃǂ̓����蔻������O
		if (
			(parent->tag_ == Tag::Myself || parent->tag_ == Tag::MyBullet) &&
			(parent2->tag_ == Tag::Myself || parent2->tag_ == Tag::MyBullet)
			)
		{
			continue;
		}
		if (
			(parent->tag_ == Tag::EnemyBody || parent->tag_ == Tag::EnemyBullet || parent->tag_ == Tag::EnemyBody) &&
			(parent2->tag_ == Tag::EnemyBody || parent2->tag_ == Tag::EnemyBullet || parent->tag_ == Tag::EnemyBody)
			)
		{
			continue;
		}
		//�{���̓����蔻��
		if (geometry2->Dispatch(geometries_[target].first))
		{
			NoticeEachOther(parent, parent2);
		}
	}
}
