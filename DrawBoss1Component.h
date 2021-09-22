#pragma once
#include "MainSceneDrawComponent.h"

#include "GameObjectHandle.h"
#include "Game.h"
#include "Math.h"

class DrawBoss1Component :
    public MainSceneDrawComponent
{
public:
    DrawBoss1Component(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, double z);
    ~DrawBoss1Component();
    void Draw() override;
    //UpdateするComponentから変更する
    int t_;
private:
    //四角形をひとつづつ描写する．計4回実行
    boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    boost::shared_ptr<DX12RootSignature> root_signature_;
    boost::shared_ptr<DX12Resource> vertex_buffer_;
    //4つの四角形を描画するので4つの定数バッファを使う
    boost::shared_ptr<DX12Resource> const_buffer_[4];
    boost::shared_ptr<DX12DescriptorHeap> desc_heap_[4];
    void* const_map_[4];
    void GraphicsInit();
    //四角形1つの幅
    static constexpr double square_w_ = 100.0;
    //1tickの回転角度
    static constexpr double delta_theta_ = PI / 120;
};

