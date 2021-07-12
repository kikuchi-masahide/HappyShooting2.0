#pragma once

#include "Component.h"
class CollisionComponent;

/// <summary>
/// CollisionComponent�Ŏg����ׂ��􉽐}�`�̃C���^�[�t�F�[�X
/// </summary>
class ICollisionGeometry
{
public:
	ICollisionGeometry(ComponentHandle<CollisionComponent> parent_comp)
	:parent_comp_(parent_comp){};
	virtual ~ICollisionGeometry() {};
	//���̐}�`���܂ށC�ӂ�x,y���ɕ��s�Ȓ����`��Ԃ�
	virtual inline Rect2 GetAABB() const = 0;
	ComponentHandle<CollisionComponent> GetParent() const
	{
		return parent_comp_;
	}
private:
	ComponentHandle<CollisionComponent> parent_comp_;
};

