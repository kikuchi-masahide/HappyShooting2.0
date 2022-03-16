#pragma once

/// <summary>
/// 自機の武器装備の更新、および描画機能・初期化を委譲した基底クラス
/// </summary>
class MyselfArmorBase
{
public:
	MyselfArmorBase() {};
	virtual ~MyselfArmorBase() {};
	/// <summary>
	/// メディエータが更新処理をするとき呼び出される
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 描画αを変える
	/// </summary>
	virtual void UpdateAlpha(double alpha) = 0;
	/// <summary>
	/// 弾を出すか出さないかを変える
	/// </summary>
	virtual void SetBulletAvailability(bool act) = 0;
private:
};

