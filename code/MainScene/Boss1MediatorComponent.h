#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class EnemyWaveManager;
class CollisionManager;
class Boss1StateBase;
class DrawBoss1Component;

class Boss1MediatorComponent :
    public Component
{
public:
    Boss1MediatorComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<EnemyWaveManager> enemywave_manager, boost::shared_ptr<CollisionManager> collision_manager);
    ~Boss1MediatorComponent();
    void Update() override;
    void ChangeState(Boss1StateBase* next_state);
    //�A�j���[�V�������X�g�b�v����(pause == true -> �X�g�b�v����)
    void PauseAnimation(bool pause);
    //�l�p�`�̉�]�p�x�𓾂�
    double GetSquareGrad();
    //�l�p�`�̒��S�ƃI�u�W�F�N�g���W�̋����𓾂�
    double GetSquareCenterDist();
    //�R���W������L���ɂ��邩�Ԃ�
    bool IsCollisionActive();
    /// <summary>
    /// �_���[�W��^����
    /// </summary>
    /// <returns>���ۂɋ������_���[�W(�̗�100��200�_���̒e�𓖂Ă���Ǝ��_���[�W��100�C���G���ɓ������Ă�0,...)</returns>
    double Damage(double damage);
    /// <summary>
    /// �c��̗̑͂��C�S�̗͂ɐ�߂銄����Ԃ�
    /// </summary>
    double GetHealthRate();
private:
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<EnemyWaveManager> enemywave_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    Boss1StateBase* current_state_;
    ComponentHandle<DrawBoss1Component> draw_component_;
    //�A�j���[�V�������~�܂��Ă��邩�ۂ�(��tick����̓K�p)
    bool is_pausing_;
    //�����̗�
    static constexpr double all_health_ = 300.0;//30000.0;
    //���̗�
    double health_;
    //�w���X�o�[��`���ʒu�����̂��߂̃I�u�W�F�N�g
    GameObjectHandle healthbar_object_;
    //�w���X�o�[�̈ʒu�C���C����
    static constexpr double healthbar_x_ = 0.0;
    static constexpr double healthbar_y_ = 430.0;
    static constexpr double healthbar_w_ = 500.0;
    static constexpr double healthbar_h_ = 5.0;
};

