#pragma once

#include "Component.h"

#include "Rect2.h"

class CircleGeometry;
class CupsuleGeometry;
class PolygonGeometry;

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
	virtual inline Rect2 GetAABB() = 0;
	ComponentHandle<CollisionComponent> GetParent() const
	{
		return parent_comp_;
	}
	//���̐}�`�Ƃ̓����蔻��(double dispatch)
	virtual bool Dispatch(ICollisionGeometry* geometry) = 0;
	//���̌^�̐}�`�Ƃ̓����蔻��
	virtual bool IsInCollision(CircleGeometry* circle) = 0;
	virtual bool IsInCollision(CupsuleGeometry* cupsule) = 0;
	virtual bool IsInCollision(PolygonGeometry* polygon) = 0;
	//�_p�Ɛ���ab�̋�����2��
	static double Dist2(MatVec::Vector2 p, MatVec::Vector2 a, MatVec::Vector2 b);
	//���̓_������ab�̍����ɂ��邩�ۂ�����
	static bool IsPointOnLeft(MatVec::Vector2 p, MatVec::Vector2 a, MatVec::Vector2 b);
private:
	ComponentHandle<CollisionComponent> parent_comp_;
};

