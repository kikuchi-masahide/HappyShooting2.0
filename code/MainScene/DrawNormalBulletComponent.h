#pragma once
#include "MainSceneDrawComponent.h"

#include "../Engine/Game.h"
#include "../Engine/GameObject.h"

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
    //最初に定数バッファ一括確保をするために，起動時に呼び出す
    static void StaticGraphicalInit(Game& game);
private:
    static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    static boost::shared_ptr<DX12RootSignature> root_signature_;
    static boost::shared_ptr<DX12Resource> index_buffer_;
    static boost::shared_ptr<DX12Resource> vertex_buffer_;
    //定数バッファとディスクリプタヒープ(あらかじめ作っておく)
    static std::vector<boost::shared_ptr<DX12Resource>> const_buffers_;
    static std::vector<boost::shared_ptr<DX12DescriptorHeap>> desc_heaps_;
    //maxで定数バッファを何個使えるか
    static constexpr unsigned int max_buffers_num_ = 3100;
    //次インスタンス作成時，desc_heaps_およびconst_buffers_の何番目を割り当てるか
    static std::queue<unsigned int> next_descheap_index_;
    //このインスタンスでdesc_heaps_の何番目を使うか
    unsigned int descheap_index_;
    //定数バッファマップ用ポインタ
    void* crv_map_;
    void NonstaticGraphicalInit();
};