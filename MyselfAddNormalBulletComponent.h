#pragma once
#include "Component.h"
#include "GameObjectHandle.h"

class MainScene;

//8tick�����Ɏ��@�ʏ�e��ǉ�
class MyselfAddNormalBulletComponent :
    public Component
{
public:
    MyselfAddNormalBulletComponent(GameObjectHandle handle,MainScene* scene);
    ~MyselfAddNormalBulletComponent();
    void Update() override;
private:
    //�e��1tick�ł̈ړ�����
    static constexpr double moving_dist_ = 8;
    //�e�̔��a
    static constexpr double bullet_redius_ = 5;
    //����tick�������ɒe��ǉ�
    static constexpr unsigned int period_to_fire_ = 8;
    //�e�I�u�W�F�N�g
    GameObjectHandle object_;
    //�e�V�[��
    MainScene* const scene_;
    //���� Update�̍Ō�ŉ��Z
    unsigned int time_;
};

