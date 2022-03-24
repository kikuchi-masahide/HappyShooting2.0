#pragma once
#include "MainSceneDrawComponent.h"

#include "../Engine/Game.h"
#include "../Engine/GameObject.h"

//���S��:0->1:�~�� �́C�ʏ�e�p���ˏ�O���f�[�V�����`��p�R���|�[�l���g
class DrawNormalBulletComponent :
    public MainSceneDrawComponent
{
public:
    /// <param name="radius">���a[px]</param>
    /// <param name="edge_rgb">�~�̉��̐F(rgb)</param>
    /// <param name="edge_alpha">�~�̉��̕s�����x</param>
    DrawNormalBulletComponent(GameObjectHandle object, boost::shared_ptr<LayerManager> layer_manager, double radius,MatVec::Vector3 edge_rgb,double edge_alpha,double z);
    ~DrawNormalBulletComponent();
    virtual void Draw();
    //�`�撆�S�́C�I�u�W�F�N�g�̒��S���W����̃I�t�Z�b�g
    MatVec::Vector2 center_offset_;
    //���a[px]
    double radius_;
    //�~���̐F(r,g,b)
    MatVec::Vector3 edge_rgb_;
    //�~���̕s�����x
    double edge_alpha_;
    //�ŏ��ɒ萔�o�b�t�@�ꊇ�m�ۂ����邽�߂ɁC�N�����ɌĂяo��
    static void StaticGraphicalInit(Game& game);
private:
    static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    static boost::shared_ptr<DX12RootSignature> root_signature_;
    static boost::shared_ptr<DX12Resource> index_buffer_;
    static boost::shared_ptr<DX12Resource> vertex_buffer_;
    //�萔�o�b�t�@�ƃf�B�X�N���v�^�q�[�v(���炩���ߍ���Ă���)
    static std::vector<boost::shared_ptr<DX12Resource>> const_buffers_;
    static std::vector<boost::shared_ptr<DX12DescriptorHeap>> desc_heaps_;
    //max�Œ萔�o�b�t�@�����g���邩
    static constexpr unsigned int max_buffers_num_ = 3100;
    //���C���X�^���X�쐬���Cdesc_heaps_�����const_buffers_�̉��Ԗڂ����蓖�Ă邩
    static std::queue<unsigned int> next_descheap_index_;
    //���̃C���X�^���X��desc_heaps_�̉��Ԗڂ��g����
    unsigned int descheap_index_;
    //�萔�o�b�t�@�}�b�v�p�|�C���^
    void* crv_map_;
    void NonstaticGraphicalInit();
};