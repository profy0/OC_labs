#include <iostream>
#include <windows.h>
#include <vector>
#include <thread>
#include <set>

using namespace std;

HANDLE hMutex;
vector <HANDLE> hStartEvent, hBreakEvent;
int arr_length, threads_count;
vector <int> arr;
set <int> threads;

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{   
    int id = *(int*)lpParameter;

    WaitForSingleObject(hStartEvent[id - 1], INFINITE);
    WaitForSingleObject(hMutex, INFINITE);

    srand(id);
    int cnt = 0;
    while (true) {
        if (WaitForSingleObject(hBreakEvent[id - 1], 0) == WAIT_OBJECT_0) {
            for (auto& now : arr) if (now == id) now = 0;
            ReleaseMutex(hMutex);
            return 0;
        }
        int index = rand() % arr_length;
        if (arr[index] == 0) {
            Sleep(5);
            arr[index] = id;
            cnt++;
            Sleep(5);
        }
        else {
            cout << "Thread - " << id << " / elements - " << cnt << " / index - " << index << endl;
            std::cout << std::flush;
            ResetEvent(hStartEvent[id - 1]);
            SetEvent(hBreakEvent[id - 1]);
            ReleaseMutex(hMutex);
            WaitForSingleObject(hStartEvent[id - 1], INFINITE);
            WaitForSingleObject(hMutex, INFINITE);
        }
    }
    
    ResetEvent(hStartEvent[id - 1]);
    ReleaseMutex(hMutex);
    return 0;
}



int main() {
    
    hMutex = CreateMutex(NULL, FALSE, NULL);
    cout << "Enter array length: ";
    cin >> arr_length;
    arr.resize(arr_length);
    cout << endl;
    cout << "Enter threads number: ";
    cin >> threads_count;
    cout << endl;
    int *ids = new int[threads_count];
    vector <HANDLE> hThread(threads_count);
    vector <DWORD> dwThreadId(threads_count);
    hStartEvent.resize(threads_count);
    hBreakEvent.resize(threads_count);
    for (int i = 0; i < threads_count; i++) ids[i] = i + 1;
    for (int i = 0; i < threads_count; i++) {
        hStartEvent[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        hBreakEvent[i] = CreateEvent(NULL, TRUE, FALSE, NULL);
        SetEvent(hStartEvent[i]);
        ResetEvent(hBreakEvent[i]);
        hThread[i] = CreateThread(NULL, 0, ThreadProc, &ids[i], 0, &dwThreadId[i]);
    }
    for (int i = 0; i < threads_count; i++) {
        threads.insert(i + 1);
    }
    int cnt = threads_count;
    while (cnt--) {
        vector<HANDLE> hEvents;
        for (auto now : threads) {
            hEvents.push_back(hBreakEvent[now - 1]);
        }
        WaitForMultipleObjects(hEvents.size(), hEvents.data(), TRUE, INFINITE);
        WaitForSingleObject(hMutex, INFINITE);
        for (auto now : arr) cout << now << " ";
        if (cnt == 0) break;
        cout << "\nEnter thread to stop: " << endl;
        int thread_num;
        cin >> thread_num;
        ReleaseMutex(hMutex);
        
        for (auto now : threads) {
            SetEvent(hStartEvent[now - 1]);
            if (now == thread_num) continue;
            ResetEvent(hBreakEvent[now - 1]);
        }
        threads.erase(thread_num);
    }

    CloseHandle(hMutex);
    for (int i = 0; i < threads_count; i++) {
        CloseHandle(hThread[i]);
        CloseHandle(hStartEvent[i]);
        CloseHandle(hBreakEvent[i]);
    }

    return 0;
}
