#pragma once
#include "ComponentHandle.h"

#include "Math.h"
#include "CircleGeometry.h"
#include "PolygonGeometry.h"

class CollisionUIScreen;
class CollisionComponent;
class CircleGeometry;
class PolygonGeometry;
class CupsuleGeometry;

/// <summary>
/// �����蔻��R���|�[�l���g�Ɠ����蔻��}�`���Ǘ����C�e�R���|�[�l���g�ɑS�t���[���ŏՓ˂����R���|�[�l���g��n��
/// </summary>
class CollisionManager
{
public:
	CollisionManager(CollisionUIScreen* screen);
	~CollisionManager();
	/// <summary>
	/// �Scomponent�����}�`���m�̓����蔻������s���Ccomponent�ɏՓ˂���component��������
	/// </summary>
	void TraverseAll();
	void AddCircleGeometry(CircleGeometry* circle);
	void AddPolygonGeometry(PolygonGeometry* polygon);
	void AddCupsuleGeometry(CupsuleGeometry* cupsule);
	//TODO:����Tag��(�N���X����?)�e�q�֌W�𓱓����C�Ⴆ��
	//My::body
	//  ::bullet
	//Enemy::body
	//     ::bullet
	//     ::lazer
	//�Ƃ��āC�u�G�����E�G���o���������蔻��ł��� <==> tag == Tag::Enemy�v�̂悤�ɏ����Ȃ���?
	//(���Ԃ�R���ł����܂ł��K�v�͂Ȃ��Ƃ�������)
	enum class Tag :unsigned char {
		Myself,
		MyBullet,
		EnemyBody,
		EnemyBullet,
		EnemyLazer
	};
	CollisionUIScreen* const collision_ui_;
private:
	//geometry�ƁCgeometry.aabb.lx <= geometry_arr[e].aabb.lx�Ȃ�geometry_arr�v�f�Ƃ̓����蔻��
	template<class T,class U>
	void TraverseAllSub_leq(T* geometry, Rect2& aabb, std::vector<std::pair<U*, Rect2>>& geometry_arr);
	//geometry_arr[ind]�ƁC����ȍ~�̓��z��v�f�Ƃ̓����蔻��
	template<class T>
	void TraverseAllSub_same(std::vector<std::pair<T*, Rect2>>& geometry_arr, unsigned int ind);
	//geometry�ƁCgeometry.aabb.lx < geometry_arr[e].aabb.lx�Ȃ�geometry_arr�v�f�Ƃ̓����蔻��
	template<class T,class U>
	void TraverseAllSub_less(T* geometry, Rect2& aabb, std::vector<std::pair<U*, Rect2>>& geometry_arr);
	//comp1��comp2��hit_comps_�ɁC���݂���ǉ�����
	void NoticeEachOther(ComponentHandle<CollisionComponent> comp1, ComponentHandle<CollisionComponent> comp2);
	std::vector<std::pair<CircleGeometry*, Rect2>> circles_;
	std::vector<std::pair<PolygonGeometry*, Rect2>> polygons_;
	std::vector<std::pair<CupsuleGeometry*, Rect2>> cupsules_;
};

template<class T,class U>
inline void CollisionManager::TraverseAllSub_leq(T* geometry, Rect2& aabb, std::vector<std::pair<U*,Rect2>>& geometry_arr)
{
	//CircleGeometry
	int s = -1, e = geometry_arr.size();
	//geometry_arr[s].��x < aabb.��x <= geometry_arr[e].��x
	while (e - s > 1)
	{
		int m = (e + s) / 2;
		Rect2& aabb2 = geometry_arr[m].second;
		if (aabb2.GetLD()(0) < aabb.GetLD()(0))s = m;
		else e = m;
	}
	//geometry_arr[e]�`�̐}�`�Ƃ̓����蔻��
	for (unsigned int n = e; n < geometry_arr.size(); n++)
	{
		U* geometry2 = geometry_arr[n].first;
		Rect2& aabb2 = geometry_arr[n].second;
		//geometry�̉Ex<geometry2�̍�x�ɂȂ�����I��
		if (aabb.GetRU()(0) < aabb2.GetLD()(0))break;
		//AABB���d�Ȃ�Ȃ���Ύ���(y���W������)
		if (
			aabb.GetRU()(1) < aabb2.GetLD()(1) ||
			aabb2.GetRU()(1) < aabb.GetLD()(1)
			)continue;
		//�����R���|�[�l���g���̐}�`���m�͏Փ˂����Ȃ�
		ComponentHandle<CollisionComponent> parent = geometry->GetParent();
		ComponentHandle<CollisionComponent> parent2 = geometry2->GetParent();
		if (parent == parent2)continue;
		//TODO:...
		//���@�e���m�C�G�e���m�Ȃǂ̓����蔻������O
		if (
			(parent->tag_ == Tag::Myself || parent->tag_ == Tag::MyBullet) &&
			(parent2->tag_ == Tag::Myself || parent2->tag_ == Tag::MyBullet)
			)continue;
		if (
			(parent->tag_ == Tag::EnemyBody || parent->tag_ == Tag::EnemyBullet || parent->tag_ == Tag::EnemyBody) &&
			(parent2->tag_ == Tag::EnemyBody || parent2->tag_ == Tag::EnemyBullet || parent->tag_ == Tag::EnemyBody)
			)continue;
		if (geometry->IsCrossing(*geometry2))
		{
			NoticeEachOther(parent,parent2);
		}
	}
}

template<class T>
inline void CollisionManager::TraverseAllSub_same(std::vector<std::pair<T*, Rect2>>& geometry_arr, unsigned int ind)
{
	T* geometry = geometry_arr[ind].first;
	Rect2& aabb = geometry_arr[ind].second;
	for (unsigned int n = ind + 1; n < geometry_arr.size(); n++)
	{
		T* geometry2 = geometry_arr[n].first;
		Rect2& aabb2 = geometry_arr[n].second;
		if (aabb.GetRU()(0) < aabb2.GetLD()(0))break;
		if (
			aabb.GetRU()(1) < aabb2.GetLD()(1) ||
			aabb2.GetRU()(1) < aabb.GetLD()(1)
			)continue;
		ComponentHandle<CollisionComponent> parent = geometry->GetParent();
		ComponentHandle<CollisionComponent> parent2 = geometry2->GetParent();
		if (parent == parent2)continue;
		//���@�e���m�C�G�e���m�Ȃǂ̓����蔻������O
		if (
			(parent->tag_ == Tag::Myself || parent->tag_ == Tag::MyBullet) &&
			(parent2->tag_ == Tag::Myself || parent2->tag_ == Tag::MyBullet)
			)continue;
		if (
			(parent->tag_ == Tag::EnemyBody || parent->tag_ == Tag::EnemyBullet || parent->tag_ == Tag::EnemyBody) &&
			(parent2->tag_ == Tag::EnemyBody || parent2->tag_ == Tag::EnemyBullet || parent->tag_ == Tag::EnemyBody)
			)continue;
		if (geometry->IsCrossing(*geometry2))
		{
			NoticeEachOther(parent, parent2);
		}
	}
}

template<class T, class U>
inline void CollisionManager::TraverseAllSub_less(T* geometry, Rect2& aabb, std::vector<std::pair<U*, Rect2>>& geometry_arr)
{
	//CircleGeometry
	int s = -1, e = geometry_arr.size();
	//geometry_arr[s].��x <= aabb.��x < geometry_arr[e].��x
	while (e - s > 1)
	{
		int m = (e + s) / 2;
		Rect2& aabb2 = geometry_arr[m].second;
		if (aabb2.GetLD()(0) < aabb.GetLD()(0))s = m;
		else e = m;
	}
	//geometry_arr[e]�`�̐}�`�Ƃ̓����蔻��
	for (unsigned int n = e; n < geometry_arr.size(); n++)
	{
		U* geometry2 = geometry_arr[n].first;
		Rect2& aabb2 = geometry_arr[n].second;
		//geometry�̉Ex<geometry2�̍�x�ɂȂ�����I��
		if (aabb.GetRU()(0) < aabb2.GetLD()(0))break;
		//AABB���d�Ȃ�Ȃ���Ύ���(y���W������)
		if (
			aabb.GetRU()(1) < aabb2.GetLD()(1) ||
			aabb2.GetRU()(1) < aabb.GetLD()(1)
			)continue;
		//�����R���|�[�l���g���̐}�`���m�͏Փ˂����Ȃ�
		ComponentHandle<CollisionComponent> parent = geometry->GetParent();
		ComponentHandle<CollisionComponent> parent2 = geometry2->GetParent();
		if (parent == parent2)continue;
		//���@�e���m�C�G�e���m�Ȃǂ̓����蔻������O
		if (
			(parent->tag_ == Tag::Myself || parent->tag_ == Tag::MyBullet) &&
			(parent2->tag_ == Tag::Myself || parent2->tag_ == Tag::MyBullet)
			)continue;
		if (
			(parent->tag_ == Tag::EnemyBody || parent->tag_ == Tag::EnemyBullet || parent->tag_ == Tag::EnemyBody) &&
			(parent2->tag_ == Tag::EnemyBody || parent2->tag_ == Tag::EnemyBullet || parent->tag_ == Tag::EnemyBody)
			)continue;
		if (geometry->IsCrossing(*geometry2))
		{
			NoticeEachOther(parent, parent2);
		}
	}
}
