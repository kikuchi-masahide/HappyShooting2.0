#pragma once
#include "MainSceneBaseLayer.h"
#include "../Engine/Game.h"
#include "../Helper/HDrawLineFrame.h"

//�y���|���S���ɘg����t���Ă��̂܂܏o�͂��郌�C���[
class MainSceneBasicLayer :
    public MainSceneBaseLayer
{
public:
    MainSceneBasicLayer(Scene* scene);
    virtual ~MainSceneBasicLayer();
    MatVec::Matrix4x4 GetLayerTransform();
    void UniqueDraw();
private:
    boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    boost::shared_ptr<DX12RootSignature> rootsignature_;
    boost::shared_ptr<DX12Resource> vertex_buffer_;
    boost::shared_ptr<DX12Resource> index_buffer_;
    void GraphicsInit();
    //���_�o�b�t�@��1���_
    struct Vertex {
    public:
        //-1~1���_���W
        float x_, y_, z_;
        //uv���W
        float u_, v_;
        Vertex(
            float x, float y, float z,
            float u, float v
        )
            :x_(x), y_(y), z_(z),
            u_(u), v_(v)
        {}
    };
    Helpers::HDrawLineFrame line_frame;
};
