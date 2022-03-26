#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"

class LayerManager;
class CollisionManager;
class MyBulletCollisionComponent;
class DrawNormalBulletComponent;

//�t�s�Đ����s����A���@�e�p�̃��f�B�G�[�^
//�����蔻��E�`��̏���������уR���g���[�����s��
class MyBulletComponent :
    public Component
{
public:
    MyBulletComponent(GameObjectHandle obj,boost::shared_ptr<LayerManager> layer, boost::shared_ptr<CollisionManager> col, MatVec::Vector2 d, double radius);
    ~MyBulletComponent();
    void Update() override;
    //��tick���珇�s�Đ����s��
    void SetProgradePlay();
    //��tick����speed�{���ŋt�Đ����s��(���̉ߒ��Ő��N�ʒu�ɖ߂��������)
    void SetRetrogradePlay(unsigned int speed);
    //MyBulletCollisionComponent����Ăяo�����A�Փ˕񍐗p�֐�
    void NoticeCollision();
private:
    MatVec::Vector2 d_;
    double radius_;
    //�Đ����x 1�ȉ�����0�łȂ������A1�Ȃ�Ώ��s�A���Ȃ�΋t�s
    //Set~Play����ݒ�
    int speed_;
    //��x��ʊO�ɏo�Ă��牽tick�̊Ԑ��������Ă�����
    //(��ʊO�ɏo�Ă��炱��ȏ�̎��Ԃ��o�����I�u�W�F�N�g�͋t�Đ��ł��Ȃ�)
    static const int grace_time_;
    //�t�Đ����A���ꂪ���ɂȂ钼�O��tick�ŏ���
    int time_;
    //����time_�܂łŁA��ʓ��ɍŌ�ɂ����A�܂��͓G�ɓ������Ă��Ȃ������Ƃ���time_�̒l
    //�t�s�Đ����͂��̒l�����������Ă���
    int last_time_in_stage_;
    //�����蔻��
    ComponentHandle<MyBulletCollisionComponent> collision_;
    //�`��
    ComponentHandle<DrawNormalBulletComponent> draw_;
};

