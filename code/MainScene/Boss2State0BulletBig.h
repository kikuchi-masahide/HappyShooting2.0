#pragma once
#include "../Engine/Component.h"

class LayerManager;
class CollisionManager;

class Boss2State0BulletBig :
    public Component
{
public:
    /// <param name="inv">�n�߂ɒe�̓��������𔽓]���č�����E�ɂ��邩�ۂ�</param>
    Boss2State0BulletBig(GameObjectHandle obj, bool inv, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<CollisionManager> collision_manager);
    ~Boss2State0BulletBig();
    void Update() override;
private:
    int time_;
    boost::shared_ptr<LayerManager> layer_;
    boost::shared_ptr<CollisionManager> collision_;
    //��tick�Ԋu�Œe�𐶐����邩
    static const int bullet_period_;
    //�e�𐶐�����Ƃ���C�ɉ���邩
    static const int bullet_num_per_;
    //�ł������e�̐i�ޕ���
    //x�������͕K�v�ɉ����Đ������]
    static const double bullet_dx0_;
    static const double bullet_dy_;
    //�ł������e�̔��a
    static const double bullet_radius_;
    double bullet_dx_;
};

