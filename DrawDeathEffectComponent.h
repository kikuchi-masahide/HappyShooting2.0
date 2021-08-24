#pragma once
#include "MainSceneDrawComponent.h"

#include "Game.h"
#include "GameObject.h"

/// <summary>
/// ���S�G�t�F�N�g��`��
/// �`�悪�I�������I�u�W�F�N�g���E�����ۂ���I���ł���
/// </summary>
class DrawDeathEffectComponent :
    public MainSceneDrawComponent
{
public:
    /// <param name="z">�`��z(�ȗ���20)</param>
    /// <param name="radius">���a[px](�ȗ���50)</param>
    /// <param name="will_kill_object">�`��I�����I�u�W�F�N�g�ƐS�����邩�ۂ�(�ȗ���true)</param>
    /// <param name="offset">�~���S�́C�e�I�u�W�F�N�g�ʒu����̃I�t�Z�b�g(�ȗ���(0,0))</param>
    DrawDeathEffectComponent(GameObjectHandle obj, boost::shared_ptr<LayerManager> layer_manager, double z = 20, double max_radius = 50.0, bool will_kill_object = true, MatVec::Vector2 offset = MatVec::Vector2(0,0));
    ~DrawDeathEffectComponent();
    void Draw() override;
private:
    static boost::shared_ptr<DX12GraphicsPipeline> pipeline_;
    static boost::shared_ptr<DX12RootSignature> root_signature_;
    static boost::shared_ptr<DX12Resource> vertex_buffer_;
    static boost::shared_ptr<DX12Resource> index_buffer_;
    boost::shared_ptr<DX12Resource> const_buffer_;
    boost::shared_ptr<DX12DescriptorHeap> crv_heap_;
    static void StaticGraphicInit(Game& game);
    void NonstaticGraphicInit(Game& game);
    double max_radius_;
    bool will_kill_object_;
    MatVec::Vector2 offset_;
    void* const_buffer_map_;
    unsigned int time_;
};

