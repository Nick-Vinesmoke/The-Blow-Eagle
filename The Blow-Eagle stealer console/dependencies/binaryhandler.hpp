#pragma once
#include <fstream>
#include <stdexcept>
#include <string>
#ifdef BINFH_EXPERIMENTAL
#include <vector>
#endif

namespace nk125 {
    class binary_file_handler {
    private:
        std::string notallowed = "*?<>|\n"; // Windows Default Disabled Chars

        std::string sanitize(std::string file_name) {
            int index = 0;
            std::string buffer = file_name;

            for (char c : buffer) {
                if (notallowed.find(c) != std::string::npos) {
                    buffer.erase(index, 1);
                }
                index++;
            }

            return buffer;
        }

        std::string read_error = "The file specified cannot be opened.";
        std::string write_error = read_error;
        long long m_size;
        // End Of Private

    public:
        void set_not_allowed_chars(std::string chars) {
            notallowed = chars;
        }

#ifdef BINFH_EXPERIMENTAL
        typedef std::vector<unsigned char> byteArray;

        template <class T = std::string>
        T read_file(std::string file_path, int flags = std::ios::in) {
            file_path = sanitize(file_path);
            std::ifstream in_file(file_path, std::ios::binary | flags);
            T m_str_buff;

            if (in_file.is_open()) {
                in_file.seekg(0, std::ios_base::end);

                std::streamoff sz = in_file.tellg();
                m_str_buff.resize(static_cast<size_t>(sz));

                in_file.seekg(0, std::ios_base::beg);
                in_file.read(reinterpret_cast<char*>(&m_str_buff[0]), sz);
                in_file.close();

                return m_str_buff;
            }
            else {
                throw std::runtime_error(read_error);
            }
        }

        std::streamoff size_file(std::string file_path) {
            file_path = sanitize(file_path);
            std::ifstream sz_file(file_path, std::ios::binary);

            if (sz_file.is_open()) {
                sz_file.seekg(0, std::ios_base::end);
                std::streamoff m_fsize = sz_file.tellg();
                sz_file.close();

                return m_fsize;
            }
            else {
                throw std::runtime_error(read_error);
            }
        }

        template <class T = std::string>
        void write_file(std::string file_path, T content, int flags = std::ios::out) {
            file_path = sanitize(file_path);
            std::ofstream out_file(file_path, std::ios::binary | flags);

            if (out_file.is_open()) {
                out_file.write(reinterpret_cast<char*>(content.data()), content.size());
                out_file.close();

                return;
            }
            else {
                throw std::runtime_error(write_error);
            }
            return;
        }

        void copy_file(std::string origin, std::string end) {
            byteArray buffer = read_file<byteArray>(origin);
            write_file<byteArray>(end, buffer);

            return;
        }
#else
        std::string read_file(std::string file_path) {
            file_path = sanitize(file_path);

            std::ifstream in_file(file_path, std::ios::binary);
            std::string m_str_buff;
            char m_ch_buff;

            if (in_file.is_open()) {
                while (in_file >> std::noskipws >> m_ch_buff) {
                    m_str_buff += m_ch_buff;
                }

                m_ch_buff = '\0';
                in_file.close();

                return m_str_buff;
            }
            else {
                throw std::runtime_error(read_error);
            }
        }

        std::string fast_read_file(std::string file_path) {
            file_path = sanitize(file_path);
            std::ifstream in_file(file_path, std::ios::binary);
            std::string m_str_buff;

            if (in_file.is_open()) {
                in_file.seekg(0, std::ios_base::end);

                long long sz = in_file.tellg();
                m_str_buff.resize(sz);

                in_file.seekg(0, std::ios_base::beg);
                in_file.read(&m_str_buff[0], sz);
                in_file.close();

                return m_str_buff;
            }
            else {
                throw std::runtime_error(read_error);
            }
        }

        long long size_file(std::string file_path) {
            file_path = sanitize(file_path);
            std::ifstream sz_file(file_path, std::ios::binary);

            if (sz_file.is_open()) {
                sz_file.seekg(0, std::ios_base::end);
                long long m_fsize = sz_file.tellg();
                sz_file.close();

                return m_fsize;
            }
            else {
                throw std::runtime_error(read_error);
            }
        }

        void write_file(std::string file_path, std::string content) {
            file_path = sanitize(file_path);
            std::ofstream out_file(file_path, std::ios::binary);

            if (out_file.is_open()) {
                out_file.write(content.c_str(), content.size());
                out_file.close();

                return;
            }
            else {
                throw std::runtime_error(write_error);
            }
            return;
        }

        void append_file(std::string file_path, std::string content) {
            file_path = sanitize(file_path);
            std::ofstream out_file(file_path, std::ios::binary | std::ios::app);

            if (out_file.is_open()) {
                out_file.write(content.c_str(), content.size());
                out_file.close();

                return;
            }
            else {
                throw std::runtime_error(write_error);
            }
            return;
        }

        void copy_file(std::string origin, std::string end) {
            std::string buffer = read_file(origin);
            write_file(end, buffer);

            return;
        }

        void fast_copy_file(std::string origin, std::string end) {
            std::string buffer = fast_read_file(origin);
            write_file(end, buffer);

            return;
        }
#endif
        // End of Public
    };
}