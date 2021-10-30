#pragma once
#include "MainSceneDrawComponent.h"

#include "code/Engine/Game.h"

//Boss1の通常弾描画専用のクラス
//定数バッファをあらかじめ大量に用意しておき，処理高速化を目指す
class DrawBoss1BulletComponent :
    public MainSceneDrawComponent
{
public:
    DrawBoss1BulletComponent(GameObjectHandle obj,boost::shared_ptr<LayerManager> layer_manager);
    ~DrawBoss1BulletComponent();
    //起動前に呼び出してもらう
    static void StaticGraphicInit(Game& game);
    void Draw() override;
private:
    //何番目の定数バッファを使うか
    unsigned int index_;
    XMMATRIX* matrix_map_;
    //使える定数バッファのキュー
    static std::queue<unsigned int> next_index_;
    //定数バッファの配列
    //TODO:これだけでメモリを0.1GB程度消費するのでもったいないはもったいない
    static std::vector<boost::shared_ptr<DX12Resource>> const_buffers_;
    static std::vector<boost::shared_ptr<DX12DescriptorHeap>> desc_heaps_;
    static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    static boost::shared_ptr<DX12RootSignature> root_signature_;
    static boost::shared_ptr<DX12Resource> index_buffer_;
    static boost::shared_ptr<DX12Resource> vertex_buffer_;
    //回転・拡大行列
    MatVec::Matrix4x4 exprotmat;
};

