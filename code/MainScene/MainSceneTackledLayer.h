#pragma once
#include "MainSceneBaseLayer.h"

#include "../Helper/HDrawLineFrame.h"

class MainSceneTackledLayer :
    public MainSceneBaseLayer
{
public:
    MainSceneTackledLayer(Scene* scene, DrawComponentsMultiset* draw_components);
    ~MainSceneTackledLayer();
    void UniqueDraw() override;
    MatVec::Matrix4x4 GetLayerTransform() override;
private:
    //レイヤー中心を、左下原点(300,450)の点からどれだけ平行移動させるか
    MatVec::Vector2 x_;
    //中心の移動速度
    MatVec::Vector2 v_;
    //バネっぽい動きを再現するため、a=F-Cv'で加速度を求める
    //(F:外力、C:バネ定数、v':速度vの位置ベクトルxへの射影)
    //Boss2がぶつかって来た時レイヤーに加わる外力の大きさ(|F|)
    static const double abs_f_;
    //バネ定数(C)
    static const double spring_const_;
    //いつまでもびよんびよんして戻らないので、t=570からは強制的に線形で戻す
    MatVec::Vector2 x_570_;
    void GraphicsInit(Game& game);
    boost::shared_ptr<DX12GraphicsPipeline> pipeline_;
    boost::shared_ptr<DX12RootSignature> root_signature_;
    boost::shared_ptr<DX12Resource> vertex_buffer_;
    boost::shared_ptr<DX12Resource> index_buffer_;
    //平行移動前の4点の位置(ウィンドウ中心原点、-300<=x<=300,-450<=y<=450)
    MatVec::Vector4 verts_temp_[4];
    //[-1,1]x[-1,1]座標に変換
    MatVec::Matrix4x4 conv_;
    void* verts_map_;
    //フレーム描画用
    Helpers::HDrawLineFrame frame_;
};

