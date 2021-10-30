#pragma once
#include "MainSceneDrawComponent.h"

#include "code/Engine/Game.h"

//Boss1�̒ʏ�e�`���p�̃N���X
//�萔�o�b�t�@�����炩���ߑ�ʂɗp�ӂ��Ă����C������������ڎw��
class DrawBoss1BulletComponent :
    public MainSceneDrawComponent
{
public:
    DrawBoss1BulletComponent(GameObjectHandle obj,boost::shared_ptr<LayerManager> layer_manager);
    ~DrawBoss1BulletComponent();
    //�N���O�ɌĂяo���Ă��炤
    static void StaticGraphicInit(Game& game);
    void Draw() override;
private:
    //���Ԗڂ̒萔�o�b�t�@���g����
    unsigned int index_;
    XMMATRIX* matrix_map_;
    //�g����萔�o�b�t�@�̃L���[
    static std::queue<unsigned int> next_index_;
    //�萔�o�b�t�@�̔z��
    //TODO:���ꂾ���Ń�������0.1GB���x�����̂ł��������Ȃ��͂��������Ȃ�
    static std::vector<boost::shared_ptr<DX12Resource>> const_buffers_;
    static std::vector<boost::shared_ptr<DX12DescriptorHeap>> desc_heaps_;
    static boost::shared_ptr<DX12GraphicsPipeline> graphics_pipeline_;
    static boost::shared_ptr<DX12RootSignature> root_signature_;
    static boost::shared_ptr<DX12Resource> index_buffer_;
    static boost::shared_ptr<DX12Resource> vertex_buffer_;
    //��]�E�g��s��
    MatVec::Matrix4x4 exprotmat;
};

