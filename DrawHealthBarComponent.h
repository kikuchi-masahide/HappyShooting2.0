#pragma once
#include "MainSceneDrawComponent.h"

#include "Math.h"
#include "Game.h"
#include "code/Helper/HDrawLineFrame.h"

class EnemyHealthComponent;

/// <summary>
/// 敵機あるいは画面上部にヘルスバーを表示させるcomponent
/// </summary>
class DrawHealthBarComponent :
    public MainSceneDrawComponent
{
public:
    /// <param name="health">対象敵機のEnemyHealthComponent</param>
    /// <param name="offset">このコンポーネントの親オブジェクト座標から見てどの位置にヘルスバー中心を置くか</param>
    /// <param name="width">ヘルスバー幅</param>
    /// <param name="height">ヘルスバー高さ</param>
    DrawHealthBarComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, ComponentHandle<EnemyHealthComponent> health, MatVec::Vector2 offset, double width = 30.0, double height = 6.0);
    void Draw() override;
    ~DrawHealthBarComponent();
    //health_component_の親オブジェクト座標から見てどの位置にヘルスバー中心を置くか
    MatVec::Vector2 center_offset_;
    //ヘルスバー幅
    double width_;
    //ヘルスバー高さ
    double height_;
private:
    ComponentHandle<EnemyHealthComponent> health_component_;
    static void StaticGraphicInit(Game& game);
    void NonstaticGraphicInit(Game& game);
    static boost::shared_ptr<DX12GraphicsPipeline> pipeline_;
    static boost::shared_ptr<DX12RootSignature> root_signature_;
    static boost::shared_ptr<DX12Resource> vertex_buffer_;
    static boost::shared_ptr<DX12Resource> index_buffer_;
    boost::shared_ptr<DX12Resource> const_buffer_;
    boost::shared_ptr<DX12DescriptorHeap> crv_heap_;
    void* const_buffer_map_;
    Helpers::HDrawLineFrame frame_;
};

