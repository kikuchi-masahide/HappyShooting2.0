#pragma once
#include "ComponentHandle.h"

#include "CircleGeometry.h"

class CollisionComponent;

/// <summary>
/// �����蔻��R���|�[�l���g�Ɠ����蔻��}�`���Ǘ����C�e�R���|�[�l���g�ɑS�t���[���ŏՓ˂����R���|�[�l���g��n��
/// </summary>
class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	/// <summary>
	/// �Scomponent�����}�`���m�̓����蔻������s���Ccomponent�ɏՓ˂���component��������
	/// </summary>
	void TraverseAll();
	std::vector<CircleGeometry> circles_;
private:
	//���̊􉽐}�`�z���AABB��x�����Ń\�[�g�����̂��C��x�����̐}�`�̂���ȏ�ł���}�`�Ƃ̓����蔻����s���D
	template<class T,class U>
	void TraverseAllSub(T& geometry,std::vector<U>& geometry_arr);
	//�􉽐}�`�z��S�̂�AABB��x�����Ń\�[�g�����̂��C��x�����̐}�`�̂���ȏ�ł���}�`�Ƃ̓����蔻����s���D
	template<class T>
	void TraverseAllSub(T& geometry);
	//comp1��comp2��hit_comps_�ɁC���݂���ǉ�����
	void NoticeEachOther(ComponentHandle<CollisionComponent> comp1, ComponentHandle<CollisionComponent> comp2);
};

template<class T,class U>
inline void CollisionManager::TraverseAllSub(T& geometry, std::vector<U>& geometry_arr)
{
	Rect2 aabb = geometry.GetAABB();

	//CircleGeometry
	int s = -1, e = geometry_arr.size();
	//geometry_arr[s].��x < aabb.��x <= geometry_arr[e].��x
	while (e - s > 1)
	{
		int m = (e + s) / 2;
		Rect2 aabb2 = geometry_arr[m].GetAABB();
		if (aabb2.GetLD()(0) < aabb.GetLD()(0))s = m;
		else e = m;
	}
	//geometry_arr[e]�`�̐}�`�Ƃ̓����蔻��
	for (unsigned int n = e; n < geometry_arr.size(); n++)
	{
		U& geometry2 = geometry_arr[n];
		//geometry�̉Ex<geometry2�̍�x�ɂȂ�����I��
		if (aabb.GetRU()(0) < aabb.GetLD()(0))break;
		//AABB���d�Ȃ�Ȃ���Ύ���(y���W������)
		Rect2 aabb2 = geometry2.GetAABB();
		if (
			aabb.GetRU()(1) < aabb2.GetLD()(1) ||
			aabb2.GetRU()(1) < aabb.GetLD()(1)
			)continue;
		//�����R���|�[�l���g���̐}�`���m�͏Փ˂����Ȃ�
		ComponentHandle<CollisionComponent> parent = geometry.GetParent();
		ComponentHandle<CollisionComponent> parent2 = geometry2.GetParent();
		if (parent == parent2)continue;
		if (geometry.IsCrossing(geometry2))
		{
			NoticeEachOther(parent,parent2);
		}
	}
}

template<class T>
inline void CollisionManager::TraverseAllSub(T& geometry)
{
	TraverseAllSub(geometry, circles_);
}
