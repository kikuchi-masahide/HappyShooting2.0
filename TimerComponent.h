#pragma once
#include "Component.h"

#include "GameObject.h"

class MainScene;

/// <summary>
/// �w��t���[������������w�肳�ꂽ�֐�(�Ɏ�)�����s���I�u�W�F�N�g���E��
/// </summary>
class TimerComponent :
    public Component
{
public:
    /// <param name="scene">�Ɏ��ɓn��MainScene�|�C���^</param>
    /// <param name="object">�e�I�u�W�F�N�g</param>
    /// <param name="time_limit">time_limit�t���[���ڂɃɎ������s����
    /// (���̃R���|�[�l���g��ǉ��������̃t���[����0�Ƃ���)</param>
    /// <param name="lambda">���s����Ɏ�</param>
    TimerComponent(MainScene* scene,GameObjectHandle object,unsigned int time_limit,std::function<void(MainScene*)> lambda);
    ~TimerComponent();
    void Update() override;
private:
    //�Ɏ��ɓn���CMainScene�̃|�C���^
    MainScene* scene_;
    GameObjectHandle object_;
    //���s����Ɏ�
    std::function<void(MainScene*)> lambda_;
    unsigned int time_limit_;
    unsigned int time_;
};

