#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    HANDLE hFile;
    DWORD dwBytesRead;
    char buffer[21];
    string fileName;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    cout << "Enter file name: ";
    cin >> fileName;

    hFile = CreateFile(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);    if (hFile == INVALID_HANDLE_VALUE) {
        cout << "Could not open file (error " << GetLastError() << ")" << endl;
        return 1;
    }
    SetEndOfFile(hFile);
    cin.ignore();

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    string commandLine = "Sender.exe " + fileName;

    if (!CreateProcess(NULL, const_cast<char*>(commandLine.c_str()), NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi)) {
        cout << "Could not create Sender process (error " << GetLastError() << ")" << endl;
        return 1;
    }

    while (true) {
        cout << "Enter command (read/exit): ";
        string command;
        getline(cin, command);

        if (command == "exit") {
            break;
        }

        if (command == "read") {
            if (!ReadFile(hFile, buffer, 20, &dwBytesRead, NULL)) {
                cout << "Could not read from file (error " << GetLastError() << ")" << endl;
                break;
            }

            if (dwBytesRead == 0) {
                cout << "No more messages" << endl;
            } else {
                buffer[dwBytesRead] = '\0';
                cout << "Message: " << buffer << endl;
            }
        }
    }

    CloseHandle(hFile);

    return 0;
}