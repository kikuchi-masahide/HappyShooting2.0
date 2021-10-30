#pragma once
#include "MainSceneDrawComponent.h"

#include "Math.h"
#include "Game.h"
#include "code/Helper/HDrawLineFrame.h"

class EnemyHealthComponent;

/// <summary>
/// �G�@���邢�͉�ʏ㕔�Ƀw���X�o�[��\��������component
/// </summary>
class DrawHealthBarComponent :
    public MainSceneDrawComponent
{
public:
    /// <param name="health">�ΏۓG�@��EnemyHealthComponent</param>
    /// <param name="offset">���̃R���|�[�l���g�̐e�I�u�W�F�N�g���W���猩�Ăǂ̈ʒu�Ƀw���X�o�[���S��u����</param>
    /// <param name="width">�w���X�o�[��</param>
    /// <param name="height">�w���X�o�[����</param>
    DrawHealthBarComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, ComponentHandle<EnemyHealthComponent> health, MatVec::Vector2 offset, double width = 30.0, double height = 6.0);
    void Draw() override;
    ~DrawHealthBarComponent();
    //health_component_�̐e�I�u�W�F�N�g���W���猩�Ăǂ̈ʒu�Ƀw���X�o�[���S��u����
    MatVec::Vector2 center_offset_;
    //�w���X�o�[��
    double width_;
    //�w���X�o�[����
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

