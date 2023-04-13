#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <cstring>
#include <fstream>

using namespace std;

struct employee {
	int num;
	char name[10];
	double hours;
};

int main() {
	
	cout << "Enter binary file path: ";
	string binFilePath;
	cin >> binFilePath;
	cout << "\nEnter number of employees: ";
	int emplNum;
	cin >> emplNum;

	STARTUPINFO siCreator;
	PROCESS_INFORMATION piCreator;

	ZeroMemory(&siCreator, sizeof(siCreator));
	siCreator.cb = sizeof(siCreator);

	string str = "C:/OC/lab1/creator.exe " + binFilePath + " " + to_string(emplNum);
	char* consoleCreator = new char[str.size() + 1];
	strcpy(consoleCreator, str.c_str());

	if (!CreateProcess(NULL, consoleCreator, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siCreator, &piCreator)) {
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return 0;
	}

	WaitForSingleObject(piCreator.hProcess, INFINITE);


	ifstream file(binFilePath, ios::binary);
	employee emp;
	while (file.read((char*)&emp, sizeof(employee))) {
		cout << emp.num << "\t" << emp.name << "\t" << emp.hours << endl;
	}

	file.close();

	cout << "Enter output file name: ";
	string outputFileName;
	cin >> outputFileName;
	cout << "Enter pay rate per hour: ";
	double payRate;
	cin >> payRate;

	STARTUPINFO siReporter;
	PROCESS_INFORMATION piReporter;

	ZeroMemory(&siReporter, sizeof(siReporter));
	siReporter.cb = sizeof(siReporter);

	str = "C:/OC/lab1/reporter.exe " + binFilePath + " " + outputFileName + " " + to_string(payRate);
	char* consoleReporter = new char[str.length() + 1];
	strcpy(consoleReporter, str.c_str());

	if (!CreateProcess(NULL, consoleReporter, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siReporter, &piReporter)) {
		_cputs("The new process is not created.\n");
		_cputs("Check a name of the process.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return 0;
	}

	WaitForSingleObject(piReporter.hProcess, INFINITE);


	ifstream outputFile(outputFileName);
	string next;
	while (getline(outputFile, next)) {
		cout << next << "\n";
	}

	file.close();

	//  C:/Users/nikit/source/repos/lab1_oc/employees.bin
	// output.txt

}