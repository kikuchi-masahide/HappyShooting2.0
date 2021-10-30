#pragma once
#include "MainSceneDrawComponent.h"

#include "code/Engine/Game.h"
#include "code/Engine/GameObject.h"

//中心α:0->1:円周 の，通常弾用放射状グラデーション描画用コンポーネント
class DrawNormalBulletComponent :
    public MainSceneDrawComponent
{
public:
    /// <param name="radius">半径[px]</param>
    /// <param name="edge_rgb">円の縁の色(rgb)</param>
    /// <param name="edge_alpha">円の縁の不透明度</param>
    DrawNormalBulletComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, double radius,MatVec::Vector3 edge_rgb,double edge_alpha,double z);
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
    static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    static boost::shared_ptr<DX12RootSignature> root_signature_;
    static boost::shared_ptr<DX12Resource> index_buffer_;
    static boost::shared_ptr<DX12Resource> vertex_buffer_;
    //色，α格納用のバッファとCRV
    boost::shared_ptr<DX12DescriptorHeap> crv_desc_heap_;
    boost::shared_ptr<DX12Resource> crv_resource_;
    //定数バッファマップ用ポインタ
    void* crv_map_;
    static void StaticGraphicalInit(Scene* scene);
    void NonstaticGraphicalInit();
};

