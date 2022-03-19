#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class CollisionManager;

/// <summary>
/// Enemy8���o���e�̃R���|�[�l���g�������A�ʒu�X�V���s��
/// </summary>
class Enemy8BulletComponent :
    public Component
{
public:
    //�ŏ��Ɉړ�����p�x�A���@�̃n���h��(�r�����玩�@�_���ɂȂ�̂�)
    Enemy8BulletComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager,double angle, GameObjectHandle myself);
    ~Enemy8BulletComponent();
    void Update() override;
private:
    double angle_;
    //���@�n���h��
    GameObjectHandle myself_;
    //�ŏ���Update�Ăяo����0
    int time_;
};

