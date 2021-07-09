#pragma once
#include "Component.h"

#include "GameObject.h"

class MainScene;

/// <summary>
/// 指定フレーム数たったら指定された関数(λ式)を実行しオブジェクトを殺す
/// </summary>
class TimerComponent :
    public Component
{
public:
    /// <param name="scene">λ式に渡すMainSceneポインタ</param>
    /// <param name="object">親オブジェクト</param>
    /// <param name="time_limit">time_limitフレーム目にλ式を実行する
    /// (このコンポーネントを追加した次のフレームを0とする)</param>
    /// <param name="lambda">実行するλ式</param>
    TimerComponent(MainScene* scene,GameObjectHandle object,unsigned int time_limit,std::function<void(MainScene*)> lambda);
    ~TimerComponent();
    void Update() override;
private:
    //λ式に渡す，MainSceneのポインタ
    MainScene* scene_;
    GameObjectHandle object_;
    //実行するλ式
    std::function<void(MainScene*)> lambda_;
    unsigned int time_limit_;
    unsigned int time_;
};

