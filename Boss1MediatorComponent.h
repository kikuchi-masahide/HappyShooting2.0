#pragma once
#include "code/Engine/Component.h"

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
    //Boss1�Ƀ_���[�W��^����
    //TODO:HealthComponent���悹���珈�����e������
    void GetDamaged(unsigned int damage);
private:
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<EnemyWaveManager> enemywave_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    Boss1StateBase* current_state_;
    ComponentHandle<DrawBoss1Component> draw_component_;
    //�A�j���[�V�������~�܂��Ă��邩�ۂ�(��tick����̓K�p)
    bool is_pausing_;
};

