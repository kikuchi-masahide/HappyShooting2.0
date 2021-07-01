#pragma once
#include "DX12IShaderTransferable.h"
#include "DX12DecimalToShader.h"
#include "DX12MatrixToShader.h"
#include "DX12VectorToShader.h"

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
    /// <param name="data">DX12IShaderTransferble����p�������C�ǉ��������f�[�^
    /// boost::any�̌`�ŕۑ�����</param>
    void AddData(DX12StructToShader& data);
    /// <summary>
    /// ���̍\���̂Ƀ����o��ǉ�����
    /// GetSize�ŃT�C�Y���m�肷��O�̂ݗL��
    /// </summary>
    /// <param name="data">DX12IShaderTransferble����p�������C�ǉ��������f�[�^
    /// boost::any�̌`�ŕۑ�����</param>
    void AddData(DX12DecimalToShader& data);
    /// <summary>
    /// ���̍\���̂Ƀ����o��ǉ�����
    /// GetSize�ŃT�C�Y���m�肷��O�̂ݗL��
    /// </summary>
    /// <param name="data">DX12IShaderTransferble����p�������C�ǉ��������f�[�^
    /// boost::any�̌`�ŕۑ�����</param>
    void AddData(DX12MatrixToShader& data);
    /// <summary>
    /// ���̍\���̂Ƀ����o��ǉ�����
    /// GetSize�ŃT�C�Y���m�肷��O�̂ݗL��
    /// </summary>
    /// <param name="data">DX12IShaderTransferble����p�������C�ǉ��������f�[�^
    /// boost::any�̌`�ŕۑ�����</param>
    void AddData(DX12Vector2ToShader& data);
    /// <summary>
    /// ���̍\���̂Ƀ����o��ǉ�����
    /// GetSize�ŃT�C�Y���m�肷��O�̂ݗL��
    /// </summary>
    /// <param name="data">DX12IShaderTransferble����p�������C�ǉ��������f�[�^
    /// boost::any�̌`�ŕۑ�����</param>
    void AddData(DX12Vector3ToShader& data);
    /// <summary>
    /// ���̍\���̂�n�Ԗڂ̃����o��ύX����
    /// </summary>
    /// <param name="n">���Ԗڂ̃f�[�^��ύX���邩</param>
    /// <param name="data">���̒l�ɕύX</param>
    //template<Transferable T>
    template<class T>
    void SetData(unsigned int n, T& data)
    {
        BOOST_ASSERT(n < datas_.size());
        datas_[n] = data;
        was_changed_[n] = true;
    }
    //��̓��ꉻ�̂��߂̔�����
    template<class T>
    T& Get(unsigned int n)
    {
    }
    /// <summary>
    /// n�Ԗڂ̃����o���擾
    /// </summary>
    template<>
    DX12StructToShader& Get(unsigned int n)
    {
        was_changed_[n] = true;
        return boost::any_cast<DX12StructToShader&>(datas_[n]);
    };
    /// <summary>
    /// n�Ԗڂ̃����o���擾
    /// </summary>
    template<>
    DX12DecimalToShader& Get(unsigned int n)
    {
        was_changed_[n] = true;
        return boost::any_cast<DX12DecimalToShader&>(datas_[n]);
    };
    /// <summary>
    /// n�Ԗڂ̃����o���擾
    /// </summary>
    template<>
    DX12MatrixToShader& Get(unsigned int n)
    {
        was_changed_[n] = true;
        return boost::any_cast<DX12MatrixToShader&>(datas_[n]);
    };
    /// <summary>
    /// n�Ԗڂ̃����o���擾
    /// </summary>
    template<>
    DX12Vector2ToShader& Get(unsigned int n)
    {
        was_changed_[n] = true;
        return boost::any_cast<DX12Vector2ToShader&>(datas_[n]);
    };
    /// <summary>
    /// n�Ԗڂ̃����o���擾
    /// </summary>
    template<>
    DX12Vector3ToShader& Get(unsigned int n)
    {
        was_changed_[n] = true;
        return boost::any_cast<DX12Vector3ToShader&>(datas_[n]);
    };
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
    //�����o�̌^
    enum class InfoType
    {
        Struct,
        Decimal,
        Matrix,
        Vector2,
        Vector3
    };
    std::vector<InfoType> datas_type_;
    //AddData����ۂ�was_changed_,data_size_,shole_size_,datas_type_�̕ύX
    void AddDataSub(SIZE_T size, InfoType type);
};