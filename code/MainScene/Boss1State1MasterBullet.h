#pragma once
#include "../Engine/Component.h"

class LayerManager;
class ScoreManager;
class CollisionManager;

//画面下からふわっと出てきて画面上で弾ける大きな弾の，移動・破砕処理コンポーネント
//(初期化時オブジェクト位置初期設定と必要なコンポーネントの追加処理を行う)
class Boss1State1MasterBullet :
    public Component
{
public:
    Boss1State1MasterBullet(GameObjectHandle handle,double startx, boost::shared_ptr<LayerManager> layer_manager, boost::shared_ptr<ScoreManager> score_manager, boost::shared_ptr<CollisionManager> collision_manager);
    void Update() override;
private:
    int counter_;
    ~Boss1State1MasterBullet();
    //x座標(上下移動のみなので変わらない)
    double x_;
    boost::shared_ptr<LayerManager> layer_manager_;
    boost::shared_ptr<ScoreManager> score_manager_;
    boost::shared_ptr<CollisionManager> collision_manager_;
    //消滅時小さな弾をいっぱい作るための関数
    void AddSmallBullet();
    //生成時，消滅時のy座標
    static constexpr double starty_ = -490.0;
    static constexpr double endy_ = 450;
    //counter_の値が何になったら弾けるか
    static constexpr unsigned int terminal_counter_ = 50 * 60 / 25 - 1;
    //自身の大きさ
    static constexpr double size_ = 30.0;
    //消滅時何個の弾を作るか
    static constexpr unsigned int small_bullet_num_ = 32;
    //消滅時の各弾の初速度の大きさ
    static constexpr double small_bullet_v0_ = 4.0 * 25 / 60;
    //小さな弾のy方向加速度(上を正としている)
    static constexpr double small_bullet_ay_ = -0.25 * 25 / 60;
    //小さな弾の大きさ
    static constexpr double small_bullet_size_ = 10.0;
};

