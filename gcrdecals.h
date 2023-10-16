#pragma once

#include "GuiBase.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);


class gcrdecals: public BakkesMod::Plugin::BakkesModPlugin,public SettingsWindowBase
	//,public PluginWindowBase // Uncomment if you want to render your own plugin window
{

	//std::shared_ptr<bool> enabled;

	//Boilerplate
	void onLoad() override;
	void onUnload() override; // Uncomment and implement if you need a unload method
	void extractDecals();
	std::wstring ExtractResourceToFile(int resourceId, const wchar_t* resourceType, const std::wstring& originalFilename);

public:
	void RenderSettings() override; // Uncomment if you wanna render your own tab in the settings menu
	//void RenderWindow() override; // Uncomment if you want to render your own plugin window

private:
	std::filesystem::path targetPath;
	void activateOctane();
	void activateFennec();
	void activateDominus();
};