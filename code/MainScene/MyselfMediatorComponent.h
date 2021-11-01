#pragma once
#include "../Engine/Component.h"

#include "../Engine/GameObject.h"

class LayerManager;
class ScoreManager;
class CollisionManager;
class DrawTextureComponent;
class MyselfConditionBase;

//���@�̕����R���|�[�l���g���܂Ƃ߂�R���|�[�l���g �����̃u�W�F�N�g�ւ̒ǉ��͍s��Ȃ�
//�܂Ƃ߂�R���|�[�l���g�́C
//�EDrawTextureComponent
//�E�����蔻��R���|�[�l���g
class MyselfMediatorComponent :
    public Component
{
public:
    MyselfMediatorComponent(GameObjectHandle myself, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager);
    void Update() override;
    /// <summary>
    /// ���@�Ƀ_���[�W��^����(�����蔻�肩��̌Ăяo��)
    /// </summary>
    /// <param name="point">�U����</param>
    void CauseDamageToMyself(unsigned int point);
    /// <summary>
    /// ���@�����G��ԂȂ��true��Ԃ�(�����蔻�肩��̌Ăяo��)
    /// </summary>
    bool IsInvincible();
    //��tick����̌��N��Ԃ�next_state�ɍ����ւ���(��component�̏������s��)
    void SetNextCondition(ComponentHandle<MyselfConditionBase> next_condition);
    //���@�`�掞�̃��ύX(������ƋC��������...)
    void SetAlpha(double alpha);
    //������ւ��S�������҂낰�ɂ���̂͂��܂�ɐ�s���s���ȋC�����邪
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    ComponentHandle<MyselfConditionBase> condition_;
private:
    ~MyselfMediatorComponent();
    ComponentHandle<DrawTextureComponent> draw_texture_component_;
    //�U�����󂯂Ă��牽tick���G�ɂȂ邩
    static constexpr unsigned int invulnerable_time_ = 120;
    //���̒l��0�ȏ�Ȃ�Ζ��G��
    int damage_counter_;
    //�U�����󂯂��󋵂ɂ���Ď��g�̃���ς���
    void SetMyselfAlpha();
};
