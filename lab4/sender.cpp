#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    HANDLE hFile;
    DWORD dwBytesWritten;
    string message;
    string fileName = argv[1];
    
    hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        cout << "Could not create file (error " << GetLastError() << ")" << endl;
        return 1;
    }

    while (true) {
        cout << "Enter message (or \"exit\" to quit): ";
        getline(cin, message);

        if (message == "exit") {
            break;
        }

        if (message.length() > 20) {
            cout << "Message is too long. Maximum length is 20 characters." << endl;
            continue;
        }

        if (!WriteFile(hFile, message.c_str(), message.length(), &dwBytesWritten, NULL)) {
            cout << "Could not write to file (error " << GetLastError() << ")" << endl;
            break;
        }
    }

    CloseHandle(hFile);

    return 0;
}