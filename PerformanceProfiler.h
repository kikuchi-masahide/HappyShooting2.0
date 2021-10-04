#pragma once

#include <fstream>

namespace PerformanceProfiler {

	//1tickごとの記録
	class ProfileUnit
	{
	public:
		ProfileUnit();
		~ProfileUnit();
		//各段階の時間
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
		//これがtrueならば，このtickの末尾で記録flashを行う
		bool flash_flag_;
		//プロファイル上のこのtickの名前
		std::string record_name_;
		//記録を全消去する
		void Init();
		//このofstreamに持っている記録を書きだす
		void Flash(std::ofstream& stream);
		//このtickにおいてOutputが実行されていないことやまだ記録を持っていないことを表す無限値
		static constexpr DWORD cinf_ = 60000;
	};

	/// <summary>
	/// 各tickのUpdate,Outputの各段階の経過時間を記録しcsvの.txtで出力する
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

		//現在のtickに記録用の名前を付け，この前後60tickの記録を出力する
		void SetRecordName(std::string name);
		//Update1回，あるいはUpdate・Output1回ずつが終わった後に呼び出す
		void CallOnTickEnd();
	private:
		//120tickで循環するように記録する
		ProfileUnit units_[120];
		//このtickではunits_の何番目に記録をするか
		unsigned int units_index_;
		std::ofstream stream_;
		//記録を吐き出す
		void Flash();
	};
}
