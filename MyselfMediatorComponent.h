#pragma once
#include "Component.h"

#include "GameObject.h"

class LayerManager;
class ScoreManager;
class CollisionManager;
class DrawTextureComponent;

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
    /// ���@�Ƀ_���[�W��^����
    /// </summary>
    /// <param name="point">���|�C���g�_���[�W�����邩</param>
    void CauseDamageToMyself(unsigned int point);
private:
    ~MyselfMediatorComponent();
    ComponentHandle<DrawTextureComponent> draw_texture_component_;
    //�U�����󂯂Ă��牽tick���G�ɂȂ邩
    static constexpr unsigned int invulnerable_time_ = 120;
    //���̒l��0�ȏ�Ȃ�Ζ��G��
    int damage_counter_;
    //�U�����󂯂��󋵂ɂ���Ď��g�̃���ς���
    void SetMyselfAlpha();
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
};

