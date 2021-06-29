#pragma once
#include "MainSceneDrawComponent.h"

#include "HTextureAlphaRotateDraw.h"
#include "GameObjectHandle.h"

/// <summary>
/// �e�N�X�`����`�悷��R���|�[�l���g
/// </summary>
class DrawTextureComponent :
    public MainSceneDrawComponent
{
public:
    DrawTextureComponent(MainScene* scene,unsigned int texture_id,GameObjectHandle object);
    ~DrawTextureComponent();
    virtual void Draw();
    //�`�撆�S�́C�I�u�W�F�N�g�̒��S���W����̃I�t�Z�b�g
    MatVec::Vector2 center_offset_;
    //�I�u�W�F�N�g�̊p�x����́C�`��p�x�̃I�t�Z�b�g
    double angle_offset_;
    //�s�����x(0.0~1.0)
    double alpha_;
    //�`�敝
    double width_;
    //�`�捂��
    double height_;
private:
    HTextureAlphaRotateDraw draw_helper_;
    //�e�I�u�W�F�N�g
    GameObjectHandle object_;
};
