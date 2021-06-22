#pragma once
#include "MainSceneBaseLayer.h"
#include "Game.h"
#include "HDrawLineFrame.h"

//ペラポリゴンに枠線を付けてそのまま出力するレイヤー
class MainSceneBasicLayer :
    public MainSceneBaseLayer
{
public:
    MainSceneBasicLayer(MainScene* scene);
    virtual ~MainSceneBasicLayer();
    void UniqueDraw();
private:
    boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    boost::shared_ptr<DX12RootSignature> rootsignature_;
    boost::shared_ptr<DX12Resource> vertex_buffer_;
    boost::shared_ptr<DX12Resource> index_buffer_;
    void GraphicsInit();
    //頂点バッファの1頂点
    struct Vertex {
    public:
        //-1~1頂点座標
        float x_, y_, z_;
        //uv座標
        float u_, v_;
        Vertex(
            float x, float y, float z,
            float u, float v
        )
            :x_(x), y_(y), z_(z),
            u_(u), v_(v)
        {}
    };
    HDrawLineFrame line_frame;
};

