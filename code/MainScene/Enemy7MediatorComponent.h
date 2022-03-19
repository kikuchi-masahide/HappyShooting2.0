#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class EnemyWaveManager;
class CollisionManager;
class ScoreManager;
class DrawTextureComponent;
class EnemyHealthComponent;

/// <summary>
/// Enemy7(�o���A�t�̂��)�̖{�̂ƃo���A�̑S�������ƊǗ����s���A�{�̂̃I�u�W�F�N�g�������f�B�G�[�^
/// </summary>
class Enemy7MediatorComponent :
    public Component
{
public:
    Enemy7MediatorComponent(GameObjectHandle handle, boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col, boost::shared_ptr<ScoreManager> score);
    ~Enemy7MediatorComponent();
    void Update() override;
private:
    //���߂�Update���Ăяo�����Ƃ�-240�A���E�ړ����n�߂�Ƃ�0�ɂȂ�
    int time_;
    ComponentHandle<DrawTextureComponent> texture_;
    boost::shared_ptr<LayerManager> layer_;
    boost::shared_ptr<CollisionManager> collision_;
    //12tick���Ƃ�4�����ɒe�𔭎�
    void Shoot();
    static const int health0_ = 2500;
};

