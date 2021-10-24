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
	//���̐}�`�̓����蔻���������
	void AddGeometry(ICollisionGeometry* geometry);
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
	std::vector<std::pair<ICollisionGeometry*, Rect2>> geometries_;
	//geometries_[n]��geometries_[n+1]~geometries_.back()�S�̂Ƃ̓����蔻��
	void TraverseAllAgainst(int target);
};