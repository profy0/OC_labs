#include <iostream>
#include <Windows.h>
#include <process.h>

using namespace std;

int* arr;
int n;
int minn = INT_MAX;
int maxx = INT_MIN;
int avg = 0;

HANDLE hAverage;
HANDLE hMinMax;

void Average(void* pArguments) {
    for (int i = 0; i < n; i++) {
        avg += arr[i];
        Sleep(12);
    }
    avg /= n;
    cout << "Average value of array elements: " << avg << endl;
}

void MinMax(void* pArguments) {
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxx) maxx = arr[i];
        Sleep(7);
        if (arr[i] < minn) minn = arr[i];
        Sleep(7);
    }
    cout << "Minimum value of array elements: " << minn << endl;
    cout << "Maximum value of array elements: " << maxx << endl;
}

int main() {
    cout << "Enter size of array:" << endl;
    cin >> n;

    arr = new int[n];

    cout << "Enter array elements:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    hAverage = (HANDLE)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Average, NULL, 0, NULL);
    hMinMax = (HANDLE)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MinMax, NULL, 0, NULL);

    WaitForSingleObject(hAverage, INFINITE);
    WaitForSingleObject(hMinMax, INFINITE);

    for (int i = 0; i < n; i++) {
        if (arr[i] == maxx || arr[i] == minn) arr[i] = avg;
        cout << arr[i] << " ";
    }

    CloseHandle(hAverage);
    CloseHandle(hMinMax);
}