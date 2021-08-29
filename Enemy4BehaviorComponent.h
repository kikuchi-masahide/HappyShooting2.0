#pragma once
#include "Component.h"
#include "CollisionComponent.h"

class LayerManager;
class DrawAnimationComponent;
class DrawTextureComponent;
class DrawLazerComponent;

/// <summary>
/// ���Ԃɂ�肩���Enemy4�̈ʒu�C�`��C�����蔻��̏������ƊǗ����s��
/// </summary>
// TODO:�����蔻��ƃ��[�U�[�̕`��ǉ�
class Enemy4BehaviorComponent :
    public CollisionComponent
{
public:
    Enemy4BehaviorComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<LayerManager> layer_manager,int flag);
    ~Enemy4BehaviorComponent();
    void Update() override;
    void CheckHitComponent() override;
private:
    int counter_;
    unsigned int mode_;
    int flag_;   //�E�����ɓ����Ȃ��1�C�����E�ɂ������Ȃ��-1
    ComponentHandle<DrawTextureComponent> texture0_;
    ComponentHandle<DrawAnimationComponent> animation_;
    ComponentHandle<DrawTextureComponent> texture1_;
    ComponentHandle<DrawLazerComponent> lazer_draw_;
    boost::shared_ptr<LayerManager> layer_manager_;
};

