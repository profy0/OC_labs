#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char *argv[]) {

    string inputFile, outputFile;
    double payRate;

	inputFile = argv[1];
	outputFile = argv[2];
	payRate = atof(argv[3]);

    ifstream file(inputFile, ios::binary);
    employee emp;
    ofstream out(outputFile);

    out << "Report for file \"" << inputFile << "\":" << endl;
    out << "Employee number\tName\tHours worked\tSalary" << endl;

    while (file.read((char*)&emp, sizeof(employee))) {
        double salary = emp.hours * payRate;
        out << emp.num << "\t\t" << emp.name << "\t" << emp.hours << "\t\t" << salary << endl;
    }

    file.close();
    out.close();

    return 0;
}