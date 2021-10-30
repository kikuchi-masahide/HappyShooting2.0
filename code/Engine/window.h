#pragma once
#include <Windows.h>

/// <summary>
/// 1�̃E�B���h�E��\���N���X(�R�s�[�s��)
/// </summary>
class Window : public boost::noncopyable {
private:
	WNDCLASSEX mWindowClass;
	HWND mHwnd;
public:
	/// <summary>
	/// �E�B���h�E�̍쐬�𓯎��ɍs���R���X�g���N�^
	/// </summary>
	/// <param name="_wndproc">�E�B���h�E�v���V���\�W��</param>
	/// <param name="_classID">�E�B���h�E�N���X��\��ID</param>
	/// <param name="_width">��</param>
	/// <param name="_height">����</param>
	/// <param name="_windowTitle">�E�B���h�E�̃^�C�g��</param>
	Window(WNDPROC _wndproc, LPCWSTR _classID,int _width,int _height,
		LPCWSTR _windowTitle);
	Window();
	/// <summary>
	/// �E�B���h�E���쐬����
	/// </summary>
	/// <param name="_wndproc">�E�B���h�E�v���V���\�W��</param>
	/// <param name="_classID">�E�B���h�E�N���X��\��ID</param>
	/// <param name="_width">��</param>
	/// <param name="_height">����</param>
	/// <param name="_windowTitle">�E�B���h�E�̃^�C�g��</param>
	void Create(WNDPROC _wndproc, LPCWSTR _classID, int _width, int _height,
		LPCWSTR _windowTitle);
	HWND GetWindowHandle() const;
	RECT GetWindowSize() const;
	~Window();
	void ShowWindow();
};