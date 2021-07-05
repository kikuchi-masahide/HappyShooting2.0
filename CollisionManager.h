#pragma once
#include "ComponentHandle.h"

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
	/// �����蔻�肷�ׂ�component��ǉ�(�t���[���X�V)
	/// </summary>
	void AddCollisionComponent(ComponentHandle<CollisionComponent> collision_comp);
	/// <summary>
	/// �Scomponent�����}�`���m�̓����蔻������s���Ccomponent�ɏՓ˂���component��������
	/// </summary>
	void TraverseAll();
private:
	//�����蔻�肷�ׂ�component�S��(�e�t���[���Ń��Z�b�g)
	std::vector<ComponentHandle<CollisionComponent>> collision_comps_;
};

