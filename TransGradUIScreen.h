#pragma once
#include "code/Engine/UIScreen.h"
#include "code/Engine/Math/Math.h"

/// <summary>
/// ��ʑS�̂Ń��j�A�ȃO���f�[�V�����ω�������UIScreen
/// </summary>
class TransGradUIScreen :
    public UIScreen
{
public:
    /// <param name="start">�O���f�[�V�����n�߂̐F</param>
    /// <param name="end">�O���f�[�V�����I���̐F</param>
    /// <param name="time">�S�̂ŉ�tick�̃O���f�[�V�������s����</param>
    /// <param name="terminate">�O���f�[�V�����I��tick�̏���</param>
    TransGradUIScreen(Scene* scene,bool input,bool update,MatVec::Vector4 start, MatVec::Vector4 end, unsigned int time, std::function<void(TransGradUIScreen*)> terminate);
    ~TransGradUIScreen();
    void Update() override;
    void Output() override;
private:
    MatVec::Vector4 start_;
    MatVec::Vector4 end_;
    unsigned int time_;
    unsigned int counter_;
    std::function<void(TransGradUIScreen*)> terminate_;
};
