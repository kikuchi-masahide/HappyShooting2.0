#pragma once
#include "MainSceneDrawComponent.h"

#include "Game.h"
#include "GameObjectHandle.h"

//���S��:0->1:�~�� �́C�ʏ�e�p���ˏ�O���f�[�V�����`��p�R���|�[�l���g
class DrawNormalBulletComponent :
    public MainSceneDrawComponent
{
public:
    /// <param name="radius">���a[px]</param>
    /// <param name="edge_rgb">�~�̉��̐F(rgb)</param>
    /// <param name="edge_alpha">�~�̉��̕s�����x</param>
    DrawNormalBulletComponent(MainScene* scene, GameObjectHandle object,double radius,MatVec::Vector3 edge_rgb,double edge_alpha);
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
    //�e
    GameObjectHandle object_handle_;
    static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    static boost::shared_ptr<DX12RootSignature> root_signature_;
    static boost::shared_ptr<DX12Resource> index_buffer_;
    //�V�F�[�_�ɓn�����
    struct InfoToShader {
    public:
        float r_;
        float g_;
        float b_;
        float alpha_;
    };
    //�F�C���i�[�p�̃o�b�t�@��CRV
    boost::shared_ptr<DX12DescriptorHeap> crv_desc_heap_;
    boost::shared_ptr<DX12Resource> crv_resource_;
    //�萔�o�b�t�@�}�b�v�p�|�C���^
    InfoToShader* crv_map_;
    //���_�o�b�t�@
    boost::shared_ptr<DX12Resource> vertex_buffer_;
    //���_�o�b�t�@�}�b�v�p�|�C���^
    float* vertex_map_;
    static void StaticGraphicalInit(MainScene* scene);
    void NonstaticGraphicalInit();
    struct Vertex {
    public:
        MatVec::Vector3 pos_;
        MatVec::Vector2 uv_;
        Vertex(MatVec::Vector2 uv)
            :uv_(uv),pos_(MatVec::Vector3(0,0,0)){}
    };
};

