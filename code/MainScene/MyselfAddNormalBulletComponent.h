#pragma once
#include "../Engine/Component.h"
#include "../Engine/GameObject.h"

class LayerManager;
class CollisionManager;
class MyBulletComponent;

//8tick�����̒ʏ펩�@�e�ǉ��A����т����̊Ǘ�(���s�E�t�s�Đ��ɑΉ�������)
class MyselfAddNormalBulletComponent :
    public Component
{
public:
    MyselfAddNormalBulletComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager);
    ~MyselfAddNormalBulletComponent();
    void Update() override;
    //�e���Ȃ��true�ɂ���
    bool is_active_;
    //��tick���珇�s�Đ����s��
    void SetProgradePlay();
    //��tick����speed�{���ŋt�Đ����s��
    void SetRetrogradePlay(unsigned int speed);
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
    int time_;
    //�������������e��vector LinearMoveRevComponent���������Ă����΂悢
    std::vector<ComponentHandle<MyBulletComponent>> bullets_;
    //�Đ�����
    int speed_;
};

