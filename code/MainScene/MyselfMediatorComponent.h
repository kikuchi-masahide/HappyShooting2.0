#pragma once
#include "../Engine/Component.h"

#include "../Engine/GameObject.h"

class LayerManager;
class ScoreManager;
class CollisionManager;
class EnemyWaveManager;
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
    MyselfMediatorComponent(GameObjectHandle myself, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager, boost::shared_ptr<EnemyWaveManager> enemy);
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
    boost::shared_ptr<EnemyWaveManager> enemy_wave_manager_;
    //MyselfCollisionComponent����Ăяo�����A�����蔻�菈���֐�
    //(��̓I�ȏ�����condition_�ɔC����)
    void CheckHitComponent(std::set<ComponentHandle<CollisionComponent>>& hit_comps_);
    //���@�̕����MyselfArmor2�ɕύX����
    //TODO:���񎩋@�̕��킪���X3��ނ��炢�����Ȃ����炢�����ǁA�����Ƃ�������ǂ�����񂾂낤��?
    void SetMyselfArmor2();
    //TODO:�t�Đ�����鎞�AMyselfConditionBase�̎��n��������Ă������Ƃ�������ƍl�������ǁA
    //�C���X�^���X�E�R���|�[�l���g�̐����E�폜���܂܂�Ă��邽�ߑ����߂�ǂ�������
    //�Ⴆ�΃R���|�[�l���g�����݂��邵�Ȃ��ȊO�Ɂuactive��inactive���v���������A����
    //�e�R���f�B�V�����̃C���X�^���X�͏�ɕێ����A�R���f�B�V�����̑J�ڂ̓R�}���h�Ƃ��ċL������
    //�Ƃ����ӂ��ɂ���Ή\��?
    //����͎��Ԃ��A���Ȃ�łƂ肠�������܂��񂯂�
    //��tick���珇�s�E�t�s�Đ�
    void SetProgradePlay();
    void SetRetrogradePlay(unsigned int speed);
    //���@�ʒu�E�p�x�̕ϑJ��deque�Ŏ���(�����̕������ԓI�Ɍ�)
    //TODO:����MyselfRetrogradeCondition����Q�Ƃ��邽�߂�public�ɂ��邪�A
    //���̂��������Condition���Ŋ�������悤�ɂ�����
    std::deque<MatVec::Vector2> pos_transition_;
    std::deque<double> angle_transition_;
private:
    ~MyselfMediatorComponent();
    ComponentHandle<MyselfConditionBase> condition_;
    ComponentHandle<DrawTextureComponent> draw_texture_component_;
    //�U�����󂯂Ă��牽tick���G�ɂȂ邩
    static constexpr unsigned int invulnerable_time_ = 120;
    //���̒l��0�ȏ�Ȃ�Ζ��G��
    int damage_counter_;
    //���@�ړ�����
    //���ӁC���ӁC�E�ӁC���
    ComponentHandle<MyselfPosAdjustComponent> pos_adjust_[4];
    //���@�̕��푕���A����ю��@�`����Ϗ�����
    boost::shared_ptr<MyselfArmorBase> armor_;
    //���@�ʒu�����܂ŕۑ����Ă�����
    static const int transition_max_length_;
    //speed�{���ŋt�s�Đ����Ȃ��speed�A���s�Đ����Ȃ��-1
    int retrograde_speed_;
};

