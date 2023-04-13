#include <iostream>
#include <fstream>

using namespace std;

struct employee {
    int num;
    char name[10];
    double hours;
};

int main(int argc, char *argv[]) {
	
    int n = atoi(argv[2]);

    employee* emp = new employee[n];

    for (int i = 0; i < n; i++) {
        cout << "Enter employee number, name and hours worked respectively:\n";
        cin >> emp[i].num >> emp[i].name >> emp[i].hours;
    }

    ofstream file(argv[1], ios::binary);
    
    for(int i = 0; i < n; i++) {
        file.write((char*)&emp[i], sizeof(employee));
    }

    file.close();
    delete[] emp;

    return 0;
}