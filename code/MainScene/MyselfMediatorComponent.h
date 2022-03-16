#pragma once
#include "../Engine/Component.h"

#include "../Engine/GameObject.h"

class LayerManager;
class ScoreManager;
class CollisionManager;
class DrawTextureComponent;
class MyselfConditionBase;
class MyselfPosAdjustComponent;
class MyselfAddNormalBulletComponent;
class CollisionComponent;
class MyselfArmorBase;

//���@�̕����R���|�[�l���g���܂Ƃ߂�R���|�[�l���g �����̃u�W�F�N�g�ւ̒ǉ��͍s��Ȃ�
//�܂Ƃ߂�R���|�[�l���g�́C
//�EDrawTextureComponent
//�E�����蔻��R���|�[�l���g
//TODO:�����Ԉ���Ă���C������ �eState�ɓ����蔻���t�����������������炭�y
//�܂��e�X�g�Ŕz������ɍl����
//TODO:���@���U�������ăp�J�p�J���Ă鎞�A��������_���[�W����锻�肪�����Ă�����ۂ�
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
    //��tick����̌��N��Ԃ�next_state�ɍ����ւ���(��component�̏������s��)
    void SetNextCondition(ComponentHandle<MyselfConditionBase> next_condition);
    //���@�`�掞�̃��ύX(������ƋC��������...)
    void SetAlpha(double alpha);
    //������ւ��S�������҂낰�ɂ���̂͂��܂�ɐ�s���s���ȋC�����邪 <- ���ł��������񂾂���
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    ComponentHandle<MyselfConditionBase> condition_;
    //MyselfCollisionComponent����Ăяo�����A�����蔻�菈���֐�
    //(��̓I�ȏ�����condition_�ɔC����)
    void CheckHitComponent(std::set<ComponentHandle<CollisionComponent>>& hit_comps_);
private:
    ~MyselfMediatorComponent();
    ComponentHandle<DrawTextureComponent> draw_texture_component_;
    //�U�����󂯂Ă��牽tick���G�ɂȂ邩
    static constexpr unsigned int invulnerable_time_ = 120;
    //���̒l��0�ȏ�Ȃ�Ζ��G��
    int damage_counter_;
    //�U�����󂯂��󋵂ɂ���Ď��g�̃���ς���
    void SetMyselfAlpha();
    //���@�ړ�����
    //���ӁC���ӁC�E�ӁC���
    ComponentHandle<MyselfPosAdjustComponent> pos_adjust_[4];
    ComponentHandle<MyselfAddNormalBulletComponent> bullet_;
    //���@�̕��푕���A����ю��@�`����Ϗ�����
    boost::shared_ptr<MyselfArmorBase> armor_;
};

