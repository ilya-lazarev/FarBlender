// FarBlender.cpp : Defines the exported functions for the DLL.
//


#include "FarBlender.h"

#include <cassert>
#include <vector>
#include <string>

// GUID "027e8d44 - 4291 - 42e1 - bbe6 - fc2e772ef498"
const GUID _GUID = { 0x027e8d44, 0x4291, 0x42e1, {0xbb, 0xe6, 0xfc, 0x2e, 0x77, 0x2e, 0xf4, 0x98} };


PluginStartupInfo    _PSI;
FarStandardFunctions _FSF;

using namespace std;

void WINAPI SetStartupInfoW(const PluginStartupInfo* psi)
{
	_PSI = *psi;
	_FSF = *psi->FSF;
	_PSI.FSF = &_FSF;

//	settings::load();
}


void WINAPI GetGlobalInfoW(GlobalInfo* info)
{
	info->StructSize = sizeof(GlobalInfo);
	info->MinFarVersion = MAKEFARVERSION(FARMANAGERVERSION_MAJOR, FARMANAGERVERSION_MINOR, FARMANAGERVERSION_REVISION, PLUGIN_FAR_BUILD, VS_RELEASE);
	info->Version = MAKEFARVERSION(PLUGIN_VERSION_NUM, VS_RELEASE);
	info->Guid = _GUID;
	info->Title = TEXT(PLUGIN_NAME);
	info->Description = TEXT(PLUGIN_DESCR);
	info->Author = TEXT(PLUGIN_AUTHOR);
}


void WINAPI GetPluginInfoW(PluginInfo* info)
{
	assert(info);

	info->StructSize = sizeof(PluginInfo);

	//if (!settings::cmd_prefix.empty())
	//	info->CommandPrefix = settings::cmd_prefix.c_str();

	static const wchar_t* menu_strings[1];
	menu_strings[0] = TEXT(PLUGIN_NAME);

	info->PluginConfig.Guids = &_GUID;
	info->PluginConfig.Strings = menu_strings;
	info->PluginConfig.Count = sizeof(menu_strings) / sizeof(menu_strings[0]);

	//if (!settings::add_to_panel_menu)
	//	info->Flags |= PF_DISABLEPANELS;
	//else {
		info->PluginMenu.Guids = &_GUID;
		info->PluginMenu.Strings = menu_strings;
		info->PluginMenu.Count = sizeof(menu_strings) / sizeof(menu_strings[0]);
	//}

#ifdef _DEBUG
	info->Flags |= PF_PRELOAD;
#endif // _DEBUG

}

HANDLE WINAPI AnalyseW(const AnalyseInfo* info)
{
	if (!info || info->StructSize < sizeof(AnalyseInfo) || !info->FileName)
		return nullptr;
	wstring filename(info->FileName);

	return filename.rfind(L".blend") != wstring::npos ? (HANDLE)0xdeadbeaf : 0;
}

HANDLE WINAPI OpenW(const OpenInfo* info)
{
	wstring file_name;
	if (info->OpenFrom == OPEN_PLUGINSMENU) 
	{
		PanelInfo pi;
		ZeroMemory(&pi, sizeof(pi));
		pi.StructSize = sizeof(pi);
		if (!_PSI.PanelControl(PANEL_ACTIVE, FCTL_GETPANELINFO, 0, &pi))
			return nullptr;
		const intptr_t ppi_len = _PSI.PanelControl(PANEL_ACTIVE, FCTL_GETPANELITEM, static_cast<intptr_t>(pi.CurrentItem), nullptr);
		if (ppi_len == 0)
			return nullptr;
		vector<unsigned char> buffer(ppi_len);
		PluginPanelItem* ppi = reinterpret_cast<PluginPanelItem*>(&buffer.front());
		FarGetPluginPanelItem fgppi;
		ZeroMemory(&fgppi, sizeof(fgppi));
		fgppi.StructSize = sizeof(fgppi);
		fgppi.Size = buffer.size();
		fgppi.Item = ppi;
		if (!_PSI.PanelControl(PANEL_ACTIVE, FCTL_GETPANELITEM, static_cast<intptr_t>(pi.CurrentItem), &fgppi))
			return nullptr;
		const size_t file_name_len = _FSF.ConvertPath(CPM_FULL, ppi->FileName, nullptr, 0);
		if (file_name_len) 
		{
			file_name.resize(file_name_len);
			_FSF.ConvertPath(CPM_FULL, ppi->FileName, &file_name[0], file_name_len);
		}
	}

	return nullptr; // : panel::open(file_name.c_str(), false);
}
