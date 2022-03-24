#pragma once
#include "../Engine/Component.h"

class LayerManager;
class CollisionManager;

//Boss2State1�ŏ㉺������ł���e�̏������A�X�V���s��
class Boss2State1Bullet :
    public Component
{
public:
    Boss2State1Bullet(GameObjectHandle obj,bool go_down, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col);
    ~Boss2State1Bullet();
    void Update() override;
private:
    //�����x�̐�Βl
    static const double abs_g_;
    //���x�̐�Βl�ő�
    static const double max_v_;
    double v_;
    bool go_down_;
};

