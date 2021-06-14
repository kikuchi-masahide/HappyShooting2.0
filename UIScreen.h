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
	/// Input�����ɗ������ǂ�����Ԃ�
	/// </summary>
	bool DoesInputGoThrough();
	/// <summary>
	/// Component��Update���邩�ǂ����Ԃ�
	/// </summary>
	bool DoesUpdateComp();
	/// <summary>
	/// Input�����ɗ������ǂ�����ύX����
	/// </summary>
	void SetInputTransparency(bool _flag);
	/// <summary>
	/// Comp��Update���邩�ۂ���ύX����
	/// </summary>
	void SetCompUpdateFlag(bool _flag);
private:
	bool mDeleteFlag;
	//Input�����ɗ������ǂ���
	bool mDoesInputGoThrough;
	//Component��Update���邩
	bool mDoesUpdateComp;
};