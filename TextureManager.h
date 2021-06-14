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
	void LoadTexture(const wchar_t* _filename, boost::shared_ptr<DX12DescriptorHeap> _desc, unsigned int _num, unsigned int _textureid);
	/// <summary>
	/// �e�N�X�`���̃A�����[�h(DX12Resource�̉��)
	/// </summary>
	void UnloadTexture(unsigned int _textureid);
	/// <summary>
	/// DX12Resource���擾
	/// </summary>
	boost::shared_ptr<DX12Resource> GetDX12Resource(unsigned int _textureid);
	/// <summary>
	/// DX12DescriptorHeap��Heap���ID��Ԃ�
	/// </summary>
	/// <returns>first:DX12DescriptorHeap,second:ID</returns>
	std::pair<boost::shared_ptr<DX12DescriptorHeap>, unsigned int> GetDX12DescriptorHeap(unsigned int _textureid);
private:
	struct Texture {
	public:
		boost::shared_ptr<DX12Resource> mResource;
		boost::shared_ptr<DX12DescriptorHeap> mDescHeap;
		unsigned int mDescID;
	};
	std::map<unsigned int, Texture> mTexturesmap;
	Game* const mGame;
};