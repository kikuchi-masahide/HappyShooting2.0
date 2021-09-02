#pragma once
#include "Component.h"
#include "CollisionComponent.h"

#include "CircleGeometry.h"
#include "PolygonGeometry.h"

class LayerManager;
class DrawAnimationComponent;
class DrawTextureComponent;
class DrawLazerComponent;
class EnemyHealthComponent;
class ScoreManager;
class LazerCollisionComponent;

/// <summary>
/// ���Ԃɂ�肩���Enemy4�{�́E���[�U�[�̈ʒu�C�̗́C�`��C�����蔻��̏������ƊǗ����s��
/// </summary>
// TODO:�����蔻��ƃ��[�U�[�̕`��ǉ�
class Enemy4BehaviorComponent :
    public CollisionComponent
{
public:
    Enemy4BehaviorComponent(GameObjectHandle obj, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<LayerManager> layer_manager,boost::shared_ptr<ScoreManager> score_manager,int flag);
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
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    //�����ۂ̔��~
    CircleGeometry tail_;
    //�^�񒆂̐����`
    PolygonGeometry center_square_;
    //�p�J�b�ĊJ���O�p�`
    PolygonGeometry mouce_left_;
    PolygonGeometry mouce_right_;
    /// <summary>
    /// �����蔻��}�`��ݒ�E�o�^����֐��𕪗�
    /// </summary>
    /// <param name="center">�I�u�W�F�N�g���W</param>
    /// <param name="deg_counter">�O�p�`�̊p�x���ǂ����邩
    /// ������Ԃ�deg_counter=0,�J������Ԃ�deg_counter=60�Ƃ���</param>
    void RegCollisionGeometry(MatVec::Vector2 center, int deg_counter);
    //���ł���Ƃ��̂��߂ɕێ�
    ComponentHandle<EnemyHealthComponent> health_;
    //�u�{�̂ɂ��������v�̂Ɓu���[�U�[�ɓ��������v�̂𕪂������̂�
    ComponentHandle<LazerCollisionComponent> lazer_collision_;
};

