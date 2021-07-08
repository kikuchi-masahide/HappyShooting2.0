#pragma once
#include "Component.h"

#include "GameObjectHandle.h"

class MainScene;

//敵機用体力管理コンポーネント
//0未満になるとオブジェクトを消滅させ，消滅エフェクトを追加する
class EnemyHealthComponent :
    public Component
{
public:
    /// <param name="scene">消滅オブジェクト追加用シーンポインタ</param>
    /// <param name="object">親オブジェクト</param>
    /// <param name="health0">開始時体力</param>
    EnemyHealthComponent(MainScene* scene, GameObjectHandle object, double health0);
    ~EnemyHealthComponent();
    /// <summary>
    /// ダメージを与える
    /// 当たり判定から呼び出される
    /// </summary>
    void Damage(double damage);
    /// <summary>
    /// 体力チェック
    /// </summary>
    void Update() override;
private:
    double health_;
    GameObjectHandle object_;
    MainScene* scene_;
};

