#pragma once
#include "MainSceneBaseLayer.h"

#include "../Helper/HDrawLineFrame.h"

class MainSceneTackledLayer :
    public MainSceneBaseLayer
{
public:
    MainSceneTackledLayer(Scene* scene, DrawComponentsMultiset* draw_components);
    ~MainSceneTackledLayer();
    void UniqueDraw() override;
    MatVec::Matrix4x4 GetLayerTransform() override;
private:
    //���C���[���S���A�������_(300,450)�̓_����ǂꂾ�����s�ړ������邩
    MatVec::Vector2 x_;
    //���S�̈ړ����x
    MatVec::Vector2 v_;
    //�o�l���ۂ��������Č����邽�߁Aa=F-Cv'�ŉ����x�����߂�
    //(F:�O�́AC:�o�l�萔�Av':���xv�̈ʒu�x�N�g��x�ւ̎ˉe)
    //Boss2���Ԃ����ė��������C���[�ɉ����O�͂̑傫��(|F|)
    static const double abs_f_;
    //�o�l�萔(C)
    static const double spring_const_;
    //���܂ł��т��т�񂵂Ė߂�Ȃ��̂ŁAt=570����͋����I�ɐ��`�Ŗ߂�
    MatVec::Vector2 x_570_;
    void GraphicsInit(Game& game);
    boost::shared_ptr<DX12GraphicsPipeline> pipeline_;
    boost::shared_ptr<DX12RootSignature> root_signature_;
    boost::shared_ptr<DX12Resource> vertex_buffer_;
    boost::shared_ptr<DX12Resource> index_buffer_;
    //���s�ړ��O��4�_�̈ʒu(�E�B���h�E���S���_�A-300<=x<=300,-450<=y<=450)
    MatVec::Vector4 verts_temp_[4];
    //[-1,1]x[-1,1]���W�ɕϊ�
    MatVec::Matrix4x4 conv_;
    void* verts_map_;
    //�t���[���`��p
    Helpers::HDrawLineFrame frame_;
};

