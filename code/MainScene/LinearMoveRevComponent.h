#pragma once
#include "../Engine/Component.h"

#include "../Engine/Math/Math.h"

//直線移動を行う、逆再生可能なコンポーネント
class LinearMoveRevComponent :
    public Component
{
public:
    LinearMoveRevComponent(GameObjectHandle obj,MatVec::Vector2 d, double exist_limit);
    ~LinearMoveRevComponent();
    void Update() override;
    //次tickから順行再生を行う
    void SetProgradePlay();
    //次tickからspeed倍速で逆再生を行う(その過程で生起位置に戻ったら消滅)
    void SetRetrogradePlay(unsigned int speed);
private:
    MatVec::Vector2 d_;
    double exist_limit_;
    //再生速度 1以下かつ0でない整数、1ならば順行、負ならば逆行
    //Set~Playから設定
    int speed_;
    //一度画面外に出てから何tickの間生存させておくか
    //(画面外に出てからこれ以上の時間が経ったオブジェクトは逆再生できない)
    static const int grace_time_;
    //初めてのUpdate呼び出しで0 逆再生中、これが負になる直前のtickで消滅
    int time_;
    //画面内に最後にいたときのtime_の値
    int last_time_in_stage_;
};

