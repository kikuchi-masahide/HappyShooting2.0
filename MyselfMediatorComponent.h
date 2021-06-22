#pragma once
#include "Component.h"

class DrawTextureComponent;

//���@�̕����R���|�[�l���g���܂Ƃ߂�R���|�[�l���g �����̃u�W�F�N�g�ւ̒ǉ��͍s��Ȃ�
//�܂Ƃ߂�R���|�[�l���g�́C
//�EDrawTextureComponent
//�E�����蔻��R���|�[�l���g
class MyselfMediatorComponent :
    public Component
{
public:
    MyselfMediatorComponent(ComponentHandle<DrawTextureComponent> draw_texture_component);
    void Update() override;
private:
    ~MyselfMediatorComponent();
    ComponentHandle<DrawTextureComponent> draw_texture_component_;
};

