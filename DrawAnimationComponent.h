#pragma once
#include "MainSceneDrawComponent.h"

#include "Math.h"
#include "Game.h"

/// <summary>
/// �A�j���[�V������`�悷��
/// </summary>
class DrawAnimationComponent :
    public MainSceneDrawComponent
{
public:
    /// <param name="texture_id">�A�j���[�V�����̊e�t���[���̊G�����񂵂�1���̃e�N�X�`����ID</param>
    /// <param name="flame_width">1�t���[���̊G�̕�[px]</param>
    /// <param name="flame_height">1�t���[���̊G�̍���[px]</param>
    /// <param name="column">���e�N�X�`��������ɓn��R�}���܂ނ�</param>
    /// <param name="row">���e�N�X�`�������s�ɓn��R�}���܂ނ�</param>
    /// <param name="offset">�摜�̕`�撆�S�ʒu�́C�e�I�u�W�F�N�g�ʒu����̂���</param>
    /// <param name="flame_num">1���[�v�����t���[����</param>
    DrawAnimationComponent(GameObjectHandle obj, boost::shared_ptr<LayerManager> layer_manager, unsigned int texture_id, double flame_width, double flame_height, unsigned int column, unsigned int row, double z, MatVec::Vector2 offset, unsigned int flame_num);
    ~DrawAnimationComponent();
    void Draw() override;
    MatVec::Vector2 center_offset_;
    //UpdateComponent����++����悤�ɂ��Ȃ��ƁC�|�[�Y���ȂǂɍĐ�����~���Ȃ�
    int counter_;
private:
    //1�t���[�����̊G�̕��C����
    double flame_width_;
    double flame_height_;
    unsigned int column_;
    unsigned int row_;
    unsigned int flame_num_;
    static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    static boost::shared_ptr<DX12RootSignature> root_signature_;
    static boost::shared_ptr<DX12Resource> index_buffer_;
    static boost::shared_ptr<DX12Resource> vertex_buffer_;
    boost::shared_ptr<DX12DescriptorHeap> desc_heap_;
    boost::shared_ptr<DX12Resource> const_buffer_;
    void* const_buffer_map_;
    static void StaticGraphicInit(Game& game);
    void NonstaticGraphicInit(Game& game, unsigned int texture_id);
};

