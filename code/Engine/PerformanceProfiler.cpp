#include "PerformanceProfiler.h"

PerformanceProfiler::ProfileUnit::ProfileUnit()
{
	Init();
}

PerformanceProfiler::ProfileUnit::~ProfileUnit()
{
}

void PerformanceProfiler::ProfileUnit::Init()
{
	prior_unique_update_ = cinf_;
	launch_update_components_ = cinf_;
	launch_ui_screens_ = cinf_;
	posterior_unique_update_ = cinf_;

	prior_unique_output_ = cinf_;
	launch_output_components_ = cinf_;
	output_layer_ = cinf_;
	launch_output_uiscreens_ = cinf_;
	posterior_unique_output_ = cinf_;
	process_commands_ = cinf_;
	delete_obj_comp_ = cinf_;
	delete_layers_ = cinf_;
	delete_uiscreen_ = cinf_;
	process_pandings_ = cinf_;
	flash_flag_ = false;
	record_name_.clear();
}

void PerformanceProfiler::ProfileUnit::Flash(std::ofstream& stream)
{
	//記録なしの場合
	if (prior_unique_update_ == cinf_)
	{
		stream << "\n";
		return;
	}
	stream << prior_unique_update_ << ","
		<< launch_update_components_ << ","
		<< launch_ui_screens_ << ","
		<< posterior_unique_update_ << ","
		<< prior_unique_update_+launch_update_components_+launch_ui_screens_+posterior_unique_update_ << ",";
	//Outputの記録がある場合
	if (prior_unique_output_ != cinf_)
	{
		stream << prior_unique_output_ << ","
			<< launch_output_components_ << ","
			<< output_layer_ << ","
			<< launch_output_uiscreens_ << ","
			<< posterior_unique_output_ << ","
			<< process_commands_ << ","
			<< delete_obj_comp_ << ","
			<< delete_layers_ << ","
			<< delete_uiscreen_ << ","
			<< process_pandings_ << ","
			<< prior_unique_output_+launch_output_components_+output_layer_+launch_output_uiscreens_+posterior_unique_output_+
			process_commands_+delete_obj_comp_+delete_layers_+delete_uiscreen_+process_pandings_ << ",";
	}
	else {
		stream << ",,,,,,,,,,,";
	}
	stream << record_name_;
	stream << "\n";
}

PerformanceProfiler::PerformanceProfiler::PerformanceProfiler()
	:stream_("performance_profiler.txt")
{
	units_index_ = 0;
}

PerformanceProfiler::PerformanceProfiler::~PerformanceProfiler()
{
	//終了する直前の120tickの様子を吐き出す
	Flash();
}

void PerformanceProfiler::PerformanceProfiler::SetPriorUniqueUpdateTime(DWORD time)
{
	units_[units_index_].prior_unique_update_ = time;
}

void PerformanceProfiler::PerformanceProfiler::SetLaunchUpdateComponentsTime(DWORD time)
{
	units_[units_index_].launch_update_components_ = time;
}

void PerformanceProfiler::PerformanceProfiler::SetLaunchUIScreenUpdateTime(DWORD time)
{
	units_[units_index_].launch_ui_screens_ = time;
}

void PerformanceProfiler::PerformanceProfiler::SetPosteriorUniqueUpdateTime(DWORD time)
{
	units_[units_index_].posterior_unique_update_ = time;
}

void PerformanceProfiler::PerformanceProfiler::SetPriorUniqueOutputTime(DWORD time)
{
	units_[units_index_].prior_unique_output_ = time;
}

void PerformanceProfiler::PerformanceProfiler::SetLaunchOutputComponentsTime(DWORD time)
{
	units_[units_index_].launch_output_components_ = time;
}

void PerformanceProfiler::PerformanceProfiler::SetOutputLayerTime(DWORD time)
{
	units_[units_index_].output_layer_ = time;
}

void PerformanceProfiler::PerformanceProfiler::SetLaunchOutputUIScreensTime(DWORD time)
{
	units_[units_index_].launch_output_uiscreens_ = time;
}

void PerformanceProfiler::PerformanceProfiler::SetPosteriorUniqueOutputTime(DWORD time)
{
	units_[units_index_].posterior_unique_output_ = time;
}

void PerformanceProfiler::PerformanceProfiler::SetProcessCommandsTime(DWORD time)
{
	units_[units_index_].process_commands_ = time;
}

void PerformanceProfiler::PerformanceProfiler::SetDeleteObjCompTime(DWORD time)
{
	units_[units_index_].delete_obj_comp_ = time;
}

void PerformanceProfiler::PerformanceProfiler::SetDeleteLayersTime(DWORD time)
{
	units_[units_index_].delete_layers_ = time;
}

void PerformanceProfiler::PerformanceProfiler::SetDeleteUIScreenTime(DWORD time)
{
	units_[units_index_].delete_uiscreen_ = time;
}

void PerformanceProfiler::PerformanceProfiler::SetProcessPandingsTime(DWORD time)
{
	units_[units_index_].process_pandings_ = time;
}

void PerformanceProfiler::PerformanceProfiler::SetRecordName(std::string name)
{
	units_[units_index_].record_name_ = name;
	units_[units_index_].flash_flag_ = true;
}

void PerformanceProfiler::PerformanceProfiler::CallOnTickEnd()
{
	//59tick前(="61tick後 mod 120")にrecord_name_がセットされたか?
	unsigned int record_tick = units_index_ + 61;
	if (record_tick >= 120)
	{
		record_tick -= 120;
	}
	if (units_[record_tick].flash_flag_)
	{
		Flash();
	}
	//units_index_を次に使う値にし，次tick記録メモリを初期化
	units_index_++;
	if (units_index_ == 120) {
		units_index_ = 0;
	}
	units_[units_index_].Init();
}

void PerformanceProfiler::PerformanceProfiler::Flash()
{
	//表を無理やり作る
	stream_ << ",Update,,,,,Output,,,,,,,,,,,record_name\n";
	stream_ << ",PriorUniqueUpdate,LaunchUpdateComponents,LaunchUIScreenUpdate,PosteriorUniqueUpdate,SUM,"
		<< "PriorUniqueOutput,LaunchOutputComponents,OutputLayer,LaunchOutputUIScreens,PosteriorUniqueOutput,ProcessCommands,DeleteObjComp,DeleteLayers,DeleteUIScreen,ProcessPanding,SUM\n";
	//119tick前は配列上一つ後になる
	for (unsigned int i = units_index_ + 1; i < 120; i++)
	{
		stream_ << i - units_index_ - 1 << ",";
		units_[i].Flash(stream_);
	}
	for (unsigned int i = 0; i <= units_index_; i++)
	{
		stream_ << 119 - units_index_ + i << ",";
		units_[i].Flash(stream_);
	}
	stream_ << "\n\n";
}
