#pragma once
#include "Boss1StateBase.h"

//�t���t���ƃ����_���ɓ����e���o���t�F�[�Y
class Boss1State2 :
    public Boss1StateBase
{
public:
    Boss1State2(ComponentHandle<Boss1MediatorComponent> mediator, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager);
    ~Boss1State2();
    void Update() override;
    bool IsCollisionActive() override;
private:
    //x�������Cy�������ɒe���������ׂ邩
    static constexpr unsigned int bullet_num_x_ = 15+1;
    static constexpr unsigned int bullet_num_y_ = 15+1;
    //�ォ�牺�ɃO���f�[�V�����̂悤�ɒe���X�|�[��������ہC��tick�̎��ԍ���u���ăX�|�[�������邩
    static constexpr unsigned int bulletspawn_timelag_ = 10;
    unsigned int counter_;
    //counter_�̏����l�����ɂ��邩(counter_��0�̃^�C�~���O�Œe�X�|�[�����n�߂�)
    static constexpr unsigned int initial_counter_ = -60;
    //��tick�̊Ԃ��̃��[�h�ŋ������邩
    static constexpr unsigned int terminal_counter_ = 60 * 25;
    //�ǉ������e���ׂ�(���̏�Ԃ̓r���Ń{�X���|���ꂽ�ꍇ�C�e�͂��ׂď����Ȃ��Ƃ����Ȃ��̂�)
    std::vector<GameObjectHandle> bullets;
};