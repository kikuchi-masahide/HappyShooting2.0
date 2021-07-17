#pragma once
#include "Component.h"

#include "GameObjectHandle.h"
#include "Math.h"

class MainScene;

class MyselfPosAndAngleComponent :
    public Component
{
public:
    //active���C���[���猻�݂̕ό`�󋵂��󂯎��C�������Ɏ��@�̈ʒu�ƌ��������肷��UpdateComponent
    MyselfPosAndAngleComponent(GameObjectHandle handle, MainScene* scene);
    void Update() override;
    ~MyselfPosAndAngleComponent();
    /// <summary>
    /// ���̃R���|�[�l���g�����C���[�̕ό`���󂯎�邽�߂̊֐�
    /// ���̈ʒu�ɂ��郌�C���[�̒��S�����_�Ƃ��C��������̃��C���[�̕ό`��
    /// �s��ɂ܂Ƃ߂Ė�tick�n��
    /// </summary>
    void SetLayerTransform(MatVec::Matrix4x4 matrix);
private:
    MatVec::Matrix4x4 layer_transform_;
    MainScene* main_scene_;
    //1tick������̈ړ�����
    constexpr static double moving_dist_ = 3.45;
};

