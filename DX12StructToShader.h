#pragma once
#include "DX12IShaderTransferable.h"
#include "DX12DecimalToShader.h"
#include "DX12MatrixToShader.h"
#include "DX12VectorToShader.h"

/// <summary>
/// シェーダーに送るデータをまとめる構造体
/// </summary>
class DX12StructToShader final :
    public DX12IShaderTransferable
{
public:
    DX12StructToShader();
    ~DX12StructToShader();
    /// <summary>
    /// この構造体にメンバを追加する
    /// GetSizeでサイズを確定する前のみ有効
    /// </summary>
    /// <param name="data">DX12IShaderTransferbleから継承した，追加したいデータ
    /// boost::anyの形で保存する</param>
    void AddData(DX12StructToShader& data);
    /// <summary>
    /// この構造体にメンバを追加する
    /// GetSizeでサイズを確定する前のみ有効
    /// </summary>
    /// <param name="data">DX12IShaderTransferbleから継承した，追加したいデータ
    /// boost::anyの形で保存する</param>
    void AddData(DX12DecimalToShader& data);
    /// <summary>
    /// この構造体にメンバを追加する
    /// GetSizeでサイズを確定する前のみ有効
    /// </summary>
    /// <param name="data">DX12IShaderTransferbleから継承した，追加したいデータ
    /// boost::anyの形で保存する</param>
    void AddData(DX12MatrixToShader& data);
    /// <summary>
    /// この構造体にメンバを追加する
    /// GetSizeでサイズを確定する前のみ有効
    /// </summary>
    /// <param name="data">DX12IShaderTransferbleから継承した，追加したいデータ
    /// boost::anyの形で保存する</param>
    void AddData(DX12Vector2ToShader& data);
    /// <summary>
    /// この構造体にメンバを追加する
    /// GetSizeでサイズを確定する前のみ有効
    /// </summary>
    /// <param name="data">DX12IShaderTransferbleから継承した，追加したいデータ
    /// boost::anyの形で保存する</param>
    void AddData(DX12Vector3ToShader& data);
    /// <summary>
    /// この構造体のn番目のメンバを変更する
    /// </summary>
    /// <param name="n">何番目のデータを変更するか</param>
    /// <param name="data">この値に変更</param>
    //template<Transferable T>
    template<class T>
    void SetData(unsigned int n, T& data)
    {
        BOOST_ASSERT(n < datas_.size());
        datas_[n] = data;
        was_changed_[n] = true;
    }
    //後の特殊化のための箱だけ
    template<class T>
    T& Get(unsigned int n)
    {
    }
    /// <summary>
    /// n番目のメンバを取得
    /// </summary>
    template<>
    DX12StructToShader& Get(unsigned int n)
    {
        was_changed_[n] = true;
        return boost::any_cast<DX12StructToShader&>(datas_[n]);
    };
    /// <summary>
    /// n番目のメンバを取得
    /// </summary>
    template<>
    DX12DecimalToShader& Get(unsigned int n)
    {
        was_changed_[n] = true;
        return boost::any_cast<DX12DecimalToShader&>(datas_[n]);
    };
    /// <summary>
    /// n番目のメンバを取得
    /// </summary>
    template<>
    DX12MatrixToShader& Get(unsigned int n)
    {
        was_changed_[n] = true;
        return boost::any_cast<DX12MatrixToShader&>(datas_[n]);
    };
    /// <summary>
    /// n番目のメンバを取得
    /// </summary>
    template<>
    DX12Vector2ToShader& Get(unsigned int n)
    {
        was_changed_[n] = true;
        return boost::any_cast<DX12Vector2ToShader&>(datas_[n]);
    };
    /// <summary>
    /// n番目のメンバを取得
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
    //各データが変更されたか否か
    std::vector<bool> was_changed_;
    //各データのサイズ
    std::vector<unsigned long long> data_size_;
    SIZE_T whole_size_;
    //メンバの型
    enum class InfoType
    {
        Struct,
        Decimal,
        Matrix,
        Vector2,
        Vector3
    };
    std::vector<InfoType> datas_type_;
    //AddDataする際のwas_changed_,data_size_,shole_size_,datas_type_の変更
    void AddDataSub(SIZE_T size, InfoType type);
};