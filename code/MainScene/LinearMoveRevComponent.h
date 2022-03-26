#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"

//�����ړ����s���A�t�Đ��\�ȃR���|�[�l���g
class LinearMoveRevComponent :
    public Component
{
public:
    LinearMoveRevComponent(GameObjectHandle obj,MatVec::Vector2 d, double exist_limit);
    ~LinearMoveRevComponent();
    void Update() override;
    //��tick���珇�s�Đ����s��
    void SetProgradePlay();
    //��tick����speed�{���ŋt�Đ����s��(���̉ߒ��Ő��N�ʒu�ɖ߂��������)
    void SetRetrogradePlay(unsigned int speed);
private:
    MatVec::Vector2 d_;
    double exist_limit_;
    //�Đ����x 1�ȉ�����0�łȂ������A1�Ȃ�Ώ��s�A���Ȃ�΋t�s
    //Set~Play����ݒ�
    int speed_;
    //��x��ʊO�ɏo�Ă��牽tick�̊Ԑ��������Ă�����
    //(��ʊO�ɏo�Ă��炱��ȏ�̎��Ԃ��o�����I�u�W�F�N�g�͋t�Đ��ł��Ȃ�)
    static const int grace_time_;
    //���߂Ă�Update�Ăяo����0 �t�Đ����A���ꂪ���ɂȂ钼�O��tick�ŏ���
    int time_;
    //��ʓ��ɍŌ�ɂ����Ƃ���time_�̒l
    int last_time_in_stage_;
};

