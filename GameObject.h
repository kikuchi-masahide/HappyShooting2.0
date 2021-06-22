#pragma once

#include "Component.h"
#include "GameObjectHandle.h"

class Scene;
class Game;
class GameObjectHandle;
template<class T>
class ComponentHandle;

/// <summary>
/// シーンに含まれるオブジェクトを表すクラス
/// </summary>
class GameObject final {
public:
	/// <summary>
	/// Scene::AddChildから呼び出されるコンストラクタ
	/// </summary>
	GameObject(Scene* _scene, MatVec::Vector2 _pos, double _scale, double _angle);
	MatVec::Vector2 GetPosition() const;
	MatVec::Vector2 SetPosition(MatVec::Vector2 _pos);
	double GetScale() const;
	double SetScale(double _sc);
	double GetRotation() const;
	double SetRotation(double _ro);
	bool GetDeleteFlag() const { return mDeleteFlag; };
	void SetDeleteFlag() { mDeleteFlag = true; };
	/// <summary>
	/// このオブジェクトにT型のUpdateComponentを追加(_argsはコンストラクタに渡す引数)
	/// concept等でTの正当性を後々(静的に)評価したい
	/// </summary>
	template<class T, class... Args>
	ComponentHandle<T> AddUpdateComponent(Args... _args) {
		//コンポーネント自身
		T* comp = new T(_args...);
		mUpdateComponents.push_back(comp);
		auto handle = comp->This();
		//シーンに追加
		AddUpdateComponentToScene(handle);
		return handle;
	}
	/// <summary>
	/// このオブジェクトにT型のOutputComponentを追加(_argsはコンストラクタに渡す引数)
	/// concept等でTの正当性を後々(静的に)評価したい
	/// </summary>
	template<class T, class... Args>
	ComponentHandle<T> AddOutputComponent(Args... _args) {
		//コンポーネント自身
		T* comp = new T(_args...);
		mOutputComponents.push_back(comp);
		auto handle = comp->This();
		//シーンに追加
		AddOutputComponentToScene(handle);
		return handle;
	};
	Game& GetGame();
private:
	friend class Scene;
	Scene* mScene;
	~GameObject();
	//フラグが立っているコンポーネントを削除
	void DeleteFlagedComponents();
	/// <summary>
	/// オブジェクトの中心座標
	/// </summary>
	MatVec::Vector2 mPosition;
	double mScale;
	/// <summary>
	/// 回転角度(時計回り、度数)
	/// </summary>
	double mRotation;
	//このオブジェクトの持つ更新・出力コンポーネント
	std::list<Component*> mUpdateComponents;
	std::list<Component*> mOutputComponents;
	//このオブジェクトを指すハンドルのset
	std::set<GameObjectHandle*> mHandles;
	bool mDeleteFlag;
	GameObject* operator&() const noexcept;
	//AddUpdateComponent内で呼ばれる
	//#includeの方向を一致させるため別関数に分離
	void AddUpdateComponentToScene(ComponentHandle<Component> _handle);
	void AddOutputComponentToScene(ComponentHandle<Component> _handle);
	/// <summary>
	/// Scene::AddObjectで呼び出される，自身を指すハンドルを返す関数
	/// </summary>
	GameObjectHandle This();
	//このコンポーネントをdeleteしデストラクタを呼ぶ
	//(もともとこのポインタが入っていたlistからのeraseはしない)
	void DeleteComponent(Component* _component);
};