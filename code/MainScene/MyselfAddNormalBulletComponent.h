#pragma once
#include "../Engine/Component.h"
#include "../Engine/GameObject.h"

class LayerManager;
class CollisionManager;

//8tick�����Ɏ��@�ʏ�e��ǉ�
class MyselfAddNormalBulletComponent :
    public Component
{
public:
    MyselfAddNormalBulletComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager);
    ~MyselfAddNormalBulletComponent();
    void Update() override;
private:
    //�e��1tick�ł̈ړ�����
    static constexpr double moving_dist_ = 8;
    //�e�̔��a
    static constexpr double bullet_redius_ = 5;
    //����tick�������ɒe��ǉ�
    static constexpr unsigned int period_to_fire_ = 8;
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    //���� Update�̍Ō�ŉ��Z
    unsigned int time_;
};

