#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"
#include "CircleGeometry.h"
#include "PolygonGeometry.h"
#include "AABBTree.h"

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
	//���@�C���@�e���̓����蔻��}�`��������
	void AddFriendlyGeometry(ICollisionGeometry* geometry);
	//�G�@�C�G�@�e���̓����蔻��}�`��������
	void AddEnemyGeometry(ICollisionGeometry* geometry);
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
	//comp1��comp2��hit_comps_�ɁC���݂���ǉ�����
	void NoticeEachOther(ComponentHandle<CollisionComponent> comp1, ComponentHandle<CollisionComponent> comp2);
	//���@�C���@�e���́C�G�@�ɍU�������ނ̓����蔻��}�`�Ƃ���AABB�̔z��
	std::vector<ICollisionGeometry*> friendly_geometries_;
	std::vector<Rect2> friendly_aabbs_;
	std::set<ComponentHandle<CollisionComponent>> friendly_comps_;
	//�G�@�C�G�@�e���́C���@�ɍU�������ނ̓����蔻��}�`�Ƃ���AABB�z��
	std::vector<ICollisionGeometry*> enemy_geometries_;
	std::vector<Rect2> enemy_aabbs_;
	std::set<ComponentHandle<CollisionComponent>> enemy_comps_;
	AABBTree aabb_tree_;
};