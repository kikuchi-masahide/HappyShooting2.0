#pragma once
#include "DX12IShaderTransferable.h"

template<class T>
concept Transferable = requires(T & x)
{
    x.DX12IShaderTransferable();
};

/// <summary>
/// �V�F�[�_�[�ɑ���f�[�^���܂Ƃ߂�\����
/// </summary>
class DX12StructToShader final :
    public DX12IShaderTransferable
{
public:
    DX12StructToShader();
    ~DX12StructToShader();
    /// <summary>
    /// ���̍\���̂Ƀ����o��ǉ�����
    /// GetSize�ŃT�C�Y���m�肷��O�̂ݗL��
    /// </summary>
    /// <param name="data_">DX12IShaderTransferble����p�������C�ǉ��������f�[�^
    /// boost::any�̌`�ŕۑ�����</param>
    template<Transferable T>
    void AddData(const T& data)
    {
        if (!is_datas_addable_)
        {
            Log::OutputCritical("Unauthorized data inserting to DX12StructToShader");
            return;
        }
        //�ۑ�����boost::any�^�f�[�^
        boost::any add_data = data;
        datas_.push_back(add_data);
        //�n�߂Ă�Map�ł����ƃ}�b�v�����悤�u�ύX�ς݁v���}�[�N
        was_changed_.push_back(true);
        data_size_.push_back(data.GetSize());
        whole_size_ += data_size_.back();
    }
    /// <summary>
    /// ���̍\���̂�n�Ԗڂ̃����o��ύX����
    /// </summary>
    /// <param name="n">���Ԗڂ̃f�[�^��ύX���邩</param>
    /// <param name="data">���̒l�ɕύX</param>
    template<Transferable T>
    void SetData(unsigned int n, const T& data)
    {
        BOOST_ASSERT(n < datas_.size());
        datas_[n] = data;
        was_changed_[n] = true;
    }
    void Map(void* map_pointer) override;
    SIZE_T GetSize() const override;
private:
    std::vector<boost::any> datas_;
    bool is_datas_addable_;
    //�e�f�[�^���ύX���ꂽ���ۂ�
    std::vector<bool> was_changed_;
    //�e�f�[�^�̃T�C�Y
    std::vector<unsigned long long> data_size_;
    SIZE_T whole_size_;
};