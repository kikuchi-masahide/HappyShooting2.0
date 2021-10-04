#pragma once

#include <fstream>

namespace PerformanceProfiler {

	//1tick���Ƃ̋L�^
	class ProfileUnit
	{
	public:
		ProfileUnit();
		~ProfileUnit();
		//�e�i�K�̎���
		DWORD prior_unique_update_;
		DWORD launch_update_components_;
		DWORD launch_ui_screens_;
		DWORD posterior_unique_update_;
		DWORD prior_unique_output_;
		DWORD launch_output_components_;
		DWORD output_layer_;
		DWORD launch_output_uiscreens_;
		DWORD posterior_unique_output_;
		DWORD process_commands_;
		DWORD delete_obj_comp_;
		DWORD delete_layers_;
		DWORD delete_uiscreen_;
		DWORD process_pandings_;
		//���ꂪtrue�Ȃ�΁C����tick�̖����ŋL�^flash���s��
		bool flash_flag_;
		//�v���t�@�C����̂���tick�̖��O
		std::string record_name_;
		//�L�^��S��������
		void Init();
		//����ofstream�Ɏ����Ă���L�^����������
		void Flash(std::ofstream& stream);
		//����tick�ɂ�����Output�����s����Ă��Ȃ����Ƃ�܂��L�^�������Ă��Ȃ����Ƃ�\�������l
		static constexpr DWORD cinf_ = 60000;
	};

	/// <summary>
	/// �etick��Update,Output�̊e�i�K�̌o�ߎ��Ԃ��L�^��csv��.txt�ŏo�͂���
	/// </summary>
	class PerformanceProfiler
		:public boost::noncopyable
	{
	public:
		PerformanceProfiler();
		~PerformanceProfiler();

		void SetPriorUniqueUpdateTime(DWORD time);
		void SetLaunchUpdateComponentsTime(DWORD time);
		void SetLaunchUIScreenUpdateTime(DWORD time);
		void SetPosteriorUniqueUpdateTime(DWORD time);

		void SetPriorUniqueOutputTime(DWORD time);
		void SetLaunchOutputComponentsTime(DWORD time);
		void SetOutputLayerTime(DWORD time);
		void SetLaunchOutputUIScreensTime(DWORD time);
		void SetPosteriorUniqueOutputTime(DWORD time);
		void SetProcessCommandsTime(DWORD time);
		void SetDeleteObjCompTime(DWORD time);
		void SetDeleteLayersTime(DWORD time);
		void SetDeleteUIScreenTime(DWORD time);
		void SetProcessPandingsTime(DWORD time);

		//���݂�tick�ɋL�^�p�̖��O��t���C���̑O��60tick�̋L�^���o�͂���
		void SetRecordName(std::string name);
		//Update1��C���邢��Update�EOutput1�񂸂��I�������ɌĂяo��
		void CallOnTickEnd();
	private:
		//120tick�ŏz����悤�ɋL�^����
		ProfileUnit units_[120];
		//����tick�ł�units_�̉��ԖڂɋL�^�����邩
		unsigned int units_index_;
		std::ofstream stream_;
		//�L�^��f���o��
		void Flash();
	};
}
