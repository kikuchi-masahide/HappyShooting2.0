#pragma once
#include "../Engine/Component.h"

class DrawNormalBulletComponent;
class NormalBulletCollisionComponent;
class LayerManager;
class CollisionManager;

//Boss1State2�œo�ꂷ��C�t���t�������Ă�e�̑S��������ړ��C���ł����ׂĊǗ�����
class Boss1State2Bullet :
    public Component
{
public:
    Boss1State2Bullet(GameObjectHandle handle, boost::shared_ptr<CollisionManager> collision_manager,boost::shared_ptr<LayerManager> layer_manager);
    void Update() override;
private:
    ~Boss1State2Bullet();
    //���̉�(�s�����x0->1)�ɉ�tick�����邩
    static constexpr unsigned int visualization_period_ = 60;
    //���ł���܂ł̎��R�Ȉړ�����tick�s����.
    static constexpr unsigned int freemove_period_ = 60 * 20;
    //�ړ����I���Ă�����ł܂ŉ�tick�����邩
    static constexpr unsigned int unvisualization_period_ = 60;
    //���a
    static constexpr double size_ = 30;
    unsigned int counter_;
    //����������ŕύX����
    ComponentHandle<DrawNormalBulletComponent> draw_component_;
    //���̉����I������u�Ԓǉ����C�ړ����I������u�ԏ���
    ComponentHandle<NormalBulletCollisionComponent> collision_component_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    //�ړ�����
    double dx_, dy_;
    //�e�����x��Βl��max
    static constexpr double max_speed_ = 0.75;
    //���������p
    static std::random_device seed_gen_;
    static std::mt19937 engine_;
    //[0,1)��������
    static std::uniform_real_distribution<> dist_;
    //static�ϐ��̏�������1�x�ł��s������true
    static bool static_init_flag_;
};

