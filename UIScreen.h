#pragma once

class UIScreen
{
public:
	UIScreen(bool _inputflag, bool _updateflag);
	virtual void Update() = 0;
	virtual void Output() = 0;
	void SetDeleteFlag();
	bool GetDeleteFlag();
	virtual ~UIScreen() {};
	/// <summary>
	/// Inputを奥に流すかどうかを返す
	/// </summary>
	bool DoesInputGoThrough();
	/// <summary>
	/// ComponentをUpdateするかどうか返す
	/// </summary>
	bool DoesUpdateComp();
	/// <summary>
	/// Inputを奥に流すかどうかを変更する
	/// </summary>
	void SetInputTransparency(bool _flag);
	/// <summary>
	/// CompをUpdateするか否かを変更する
	/// </summary>
	void SetCompUpdateFlag(bool _flag);
private:
	bool mDeleteFlag;
	//Inputを奥に流すかどうか
	bool mDoesInputGoThrough;
	//ComponentをUpdateするか
	bool mDoesUpdateComp;
};