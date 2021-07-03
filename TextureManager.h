#pragma once

class Game;
class DX12Resource;
class DX12DescriptorHeap;

class TextureManager :public boost::noncopyable {
public:
	//�R���X�g���N�^�Ăяo����Game�ɐ���
	TextureManager(Game* const _game);
	/// <summary>
	/// �e�N�X�`����ǂݍ���
	/// </summary>
	/// <param name="_desc">�f�B�X�N���v�^�q�[�v</param>
	/// <param name="_num">�f�B�X�N���v�^�q�[�v��̂ǂ��Ƀf�B�X�N���v�^��u����</param>
	/// <param name="_textureid">�e�N�X�`��ID</param>
	void LoadTexture(const wchar_t* _filename, unsigned int _textureid);
	/// <summary>
	/// �e�N�X�`���̃A�����[�h(DX12Resource�̉��)
	/// </summary>
	void UnloadTexture(unsigned int _textureid);
	/// <summary>
	/// DX12Resource���擾
	/// </summary>
	boost::shared_ptr<DX12Resource> GetDX12Resource(unsigned int _textureid);
	/// <summary>
	/// �f�B�X�N���v�^�q�[�v�ɁC�e�N�X�`����SRV�����
	/// </summary>
	/// <param name="heap_ind">DescriptorHeap�̉��Ԗڂ�SRV����邩</param>
	void CreateSRVof(unsigned int texture_id, boost::shared_ptr<DX12DescriptorHeap> desc_heap, unsigned int heap_ind);
private:
	std::map<unsigned int, boost::shared_ptr<DX12Resource>> mTexturesmap;
	std::map<unsigned int, unsigned char> mFormat;
	Game* const mGame;
};