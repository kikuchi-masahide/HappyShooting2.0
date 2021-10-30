#pragma once
#include "MainSceneDrawComponent.h"

#include "code/Engine/Game.h"
#include "code/Engine/GameObject.h"

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
private:
    static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    static boost::shared_ptr<DX12RootSignature> root_signature_;
    static boost::shared_ptr<DX12Resource> index_buffer_;
    static boost::shared_ptr<DX12Resource> vertex_buffer_;
    //�F�C���i�[�p�̃o�b�t�@��CRV
    boost::shared_ptr<DX12DescriptorHeap> crv_desc_heap_;
    boost::shared_ptr<DX12Resource> crv_resource_;
    //�萔�o�b�t�@�}�b�v�p�|�C���^
    void* crv_map_;
    static void StaticGraphicalInit(Scene* scene);
    void NonstaticGraphicalInit();
};

