#include "pch.h"
#include "gcrdecals.h"
#include "resource.h"
#include <windows.h>

#define IDB_PNG1	125
#define IDB_PNG2	126
#define IDB_PNG3	127
#define IDB_PNG4	128
#define IDB_PNG5	129
#define IDB_PNG6	130
#define IDB_PNG7	131
#define IDB_PNG8	132
#define IDB_PNG9	133
#define IDR_JSON1	107


BAKKESMOD_PLUGIN(gcrdecals, "Plugin description or some sht", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void gcrdecals::onLoad()
{

	// This line is required for LOG to work and must be before any use of LOG()
	_globalCvarManager = cvarManager;

	LOG("GCB Decal Installer/Manager launched.");

	cvarManager->registerNotifier("GcrDecalInstall", [this](std::vector<std::string> args) {
		extractDecals();
		}, "", PERMISSION_ALL);

	cvarManager->registerNotifier("ActivateOctane", [this](std::vector<std::string> args) {
		activateOctane();
		}, "", PERMISSION_ALL);
	cvarManager->registerNotifier("ActivateDominus", [this](std::vector<std::string> args) {
		activateDominus();
		}, "", PERMISSION_ALL);
	cvarManager->registerNotifier("ActivateFennec", [this](std::vector<std::string> args) {
		activateFennec();
		}, "", PERMISSION_ALL);

	cvarManager->registerCvar("gcb_cur_decal_blue", "GCBOctaneHom", "Current Set GCR Decal");
	cvarManager->registerCvar("gcb_cur_body", "Oct", "Current Set Body");
	
	// Construct the target path
	std::filesystem::path dataFolderPath = gameWrapper->GetDataFolder();
	targetPath = dataFolderPath / "acplugin" / "DecalTextures";
	std::filesystem::create_directories(targetPath);

}

void gcrdecals::onUnload() {
	LOG("GCBDecals has been unloaded.");
}


void gcrdecals::extractDecals() {
	std::wstring pngPath = ExtractResourceToFile(IDB_PNG1, L"PNG", L"oct_home_diffuse.png");
	ExtractResourceToFile(IDB_PNG2, L"PNG", L"oct_away_diffuse.png");
	ExtractResourceToFile(IDB_PNG3, L"PNG", L"oct_anodised.png");
	ExtractResourceToFile(IDB_PNG4, L"PNG", L"dom_anodised.png");
	ExtractResourceToFile(IDB_PNG5, L"PNG", L"dom_away_diffuse.png");
	ExtractResourceToFile(IDB_PNG6, L"PNG", L"dom_home_diffuse.png");
	ExtractResourceToFile(IDB_PNG7, L"PNG", L"fen_anodised.png");
	ExtractResourceToFile(IDB_PNG8, L"PNG", L"fen_away_diffuse.png");
	ExtractResourceToFile(IDB_PNG9, L"PNG", L"fen_home_diffuse.png");
	ExtractResourceToFile(IDR_JSON1, L"JSON", L"GCB.json");

	cvarManager->executeCommand("plugin reload acplugin");
}

std::wstring gcrdecals::ExtractResourceToFile(int resourceId, const wchar_t* resourceType, const std::wstring& originalFilename) {
	HMODULE hModule = GetModuleHandle(TEXT("gcrdecals.dll"));
	HRSRC hRes = FindResource(hModule, MAKEINTRESOURCE(resourceId), resourceType);
	if (!hRes) {
		DWORD error = GetLastError();
		LPVOID errMsg;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			error,
			0, // Default language (this was a paint to understand)
			(LPWSTR)&errMsg,
			0,
			NULL
		);
		LOG("Failed to find resource.Error code : " + std::to_string(error));
		LOG(std::wstring((LPWSTR)errMsg));
		LocalFree(errMsg);
		return L"";
	}

	DWORD size = SizeofResource(hModule, hRes);
	if (size == 0) {
		LOG("Resource size is zero.");
		return L"";
	}

	HGLOBAL hResData = LoadResource(hModule, hRes);
	if (!hResData) {
		LOG("Failed to load resource.");
		return L"";
	}

	void* pRes = LockResource(hResData);
	if (!pRes) {
		LOG("Failed to lock resource.");
		return L"";
	}

	std::wstring fullPath = targetPath.wstring() + L"\\" + originalFilename;
	FILE* fp = _wfopen(fullPath.c_str(), L"wb");
	if (!fp) {
		LOG("Failed to open file for writing.");
		return L"";
	}

	size_t bytesWritten = fwrite(pRes, 1, size, fp);
	if (bytesWritten != size) {
		LOG("Failed to write all bytes to file.");
	}

	fclose(fp);
	return fullPath;

	if (!fullPath.empty()) {
		std::string narrowString(fullPath.begin(), fullPath.end());
		LOG("Success creating file");
		LOG(narrowString);
	}
	else {
		LOG("pngPath is empty.");
	}
}

void gcrdecals::activateOctane() {
	cvarManager->executeCommand("cl_itemmod_code \"hAPCB1wABMIriAECAAA\"");
	cvarManager->executeCommand("cl_itemmod_enabled \"1\"");
	cvarManager->executeCommand("acplugin_decaltexture_selectedtexture_blue \"GCBOctaneHome\"");
	cvarManager->executeCommand("acplugin_decaltexture_selectedtexture_orange \"GCBOctaneAway\"");
	cvarManager->executeCommand("gcb_cur_body \"Oct\"");
}

void gcrdecals::activateDominus() {
	cvarManager->executeCommand("cl_itemmod_code \"hANUB0wGBEIriAECAAA=\"");
	cvarManager->executeCommand("cl_itemmod_enabled \"1\"");
	cvarManager->executeCommand("acplugin_decaltexture_selectedtexture_blue \"GCBDominusHome\"");
	cvarManager->executeCommand("acplugin_decaltexture_selectedtexture_orange \"GCBDominusAway\"");
	cvarManager->executeCommand("gcb_cur_body \"Dom\"");
}

void gcrdecals::activateFennec() {
	cvarManager->executeCommand("cl_itemmod_code \"hAMtB/BCBMIqiAECAAA=\"");
	cvarManager->executeCommand("cl_itemmod_enabled \"1\"");
	cvarManager->executeCommand("acplugin_decaltexture_selectedtexture_blue \"GCBFennecHome\"");
	cvarManager->executeCommand("acplugin_decaltexture_selectedtexture_orange \"GCBFennecAway\"");
	cvarManager->executeCommand("gcb_cur_body \"Fen\"");
}