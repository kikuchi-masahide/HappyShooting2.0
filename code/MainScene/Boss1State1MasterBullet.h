#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class CollisionManager;

//��ʉ�����ӂ���Əo�Ă��ĉ�ʏ�Œe����傫�Ȓe�́C�ړ��E�j�ӏ����R���|�[�l���g
//(���������I�u�W�F�N�g�ʒu�����ݒ�ƕK�v�ȃR���|�[�l���g�̒ǉ��������s��)
class Boss1State1MasterBullet :
    public Component
{
public:
    Boss1State1MasterBullet(GameObjectHandle handle,double startx, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager);
    void Update() override;
private:
    int counter_;
    ~Boss1State1MasterBullet();
    //x���W(�㉺�ړ��݂̂Ȃ̂ŕς��Ȃ�)
    double x_;
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    //���Ŏ������Ȓe�������ς���邽�߂̊֐�
    void AddSmallBullet();
    //�������C���Ŏ���y���W
    static constexpr double starty_ = -490.0;
    static constexpr double endy_ = 450;
    //counter_�̒l�����ɂȂ�����e���邩
    static constexpr unsigned int terminal_counter_ = 50 * 60 / 25 - 1;
    //���g�̑傫��
    static constexpr double size_ = 30.0;
    //���Ŏ����̒e����邩
    static constexpr unsigned int small_bullet_num_ = 32;
    //���Ŏ��̊e�e�̏����x�̑傫��
    static constexpr double small_bullet_v0_ = 4.0 * 25 / 60;
    //�����Ȓe��y���������x(��𐳂Ƃ��Ă���)
    static constexpr double small_bullet_ay_ = -0.25 * 25 / 60;
    //�����Ȓe�̑傫��
    static constexpr double small_bullet_size_ = 10.0;
};

