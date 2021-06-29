#pragma once
#include "MainSceneDrawComponent.h"

#include "Game.h"
#include "GameObjectHandle.h"

//中心α:0->1:円周 の，通常弾用放射状グラデーション描画用コンポーネント
class DrawNormalBulletComponent :
    public MainSceneDrawComponent
{
public:
    /// <param name="radius">半径[px]</param>
    /// <param name="edge_rgb">円の縁の色(rgb)</param>
    /// <param name="edge_alpha">円の縁の不透明度</param>
    DrawNormalBulletComponent(MainScene* scene, GameObjectHandle object,double radius,MatVec::Vector3 edge_rgb,double edge_alpha);
    ~DrawNormalBulletComponent();
    virtual void Draw();
    //描画中心の，オブジェクトの中心座標からのオフセット
    MatVec::Vector2 center_offset_;
    //半径[px]
    double radius_;
    //円周の色(r,g,b)
    MatVec::Vector3 edge_rgb_;
    //円周の不透明度
    double edge_alpha_;
private:
    //親
    GameObjectHandle object_handle_;
    static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    static boost::shared_ptr<DX12RootSignature> root_signature_;
    static boost::shared_ptr<DX12Resource> index_buffer_;
    //シェーダに渡す情報
    struct InfoToShader {
    public:
        float r_;
        float g_;
        float b_;
        float alpha_;
    };
    //色，α格納用のバッファとCRV
    boost::shared_ptr<DX12DescriptorHeap> crv_desc_heap_;
    boost::shared_ptr<DX12Resource> crv_resource_;
    //定数バッファマップ用ポインタ
    InfoToShader* crv_map_;
    //頂点バッファ
    boost::shared_ptr<DX12Resource> vertex_buffer_;
    //頂点バッファマップ用ポインタ
    float* vertex_map_;
    static void StaticGraphicalInit(MainScene* scene);
    void NonstaticGraphicalInit();
    struct Vertex {
    public:
        MatVec::Vector3 pos_;
        MatVec::Vector2 uv_;
        Vertex(MatVec::Vector2 uv)
            :uv_(uv),pos_(MatVec::Vector3(0,0,0)){}
    };
};

