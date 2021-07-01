#pragma once
#include "DX12IShaderTransferable.h"

template<class T>
concept Transferable = requires(T & x)
{
    x.DX12IShaderTransferable();
};

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
    /// <param name="data_">DX12IShaderTransferbleから継承した，追加したいデータ
    /// boost::anyの形で保存する</param>
    template<Transferable T>
    void AddData(const T& data)
    {
        if (!is_datas_addable_)
        {
            Log::OutputCritical("Unauthorized data inserting to DX12StructToShader");
            return;
        }
        //保存するboost::any型データ
        boost::any add_data = data;
        datas_.push_back(add_data);
        //始めてのMapでちゃんとマップされるよう「変更済み」をマーク
        was_changed_.push_back(true);
        data_size_.push_back(data.GetSize());
        whole_size_ += data_size_.back();
    }
    /// <summary>
    /// この構造体のn番目のメンバを変更する
    /// </summary>
    /// <param name="n">何番目のデータを変更するか</param>
    /// <param name="data">この値に変更</param>
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
    //各データが変更されたか否か
    std::vector<bool> was_changed_;
    //各データのサイズ
    std::vector<unsigned long long> data_size_;
    SIZE_T whole_size_;
};