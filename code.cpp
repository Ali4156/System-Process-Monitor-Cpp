#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <ctime>
#include <limits>

// Fix conflict with Windows max macro
#ifdef max
#undef max
#endif

using namespace std;

time_t loginTime; // Global login time

// Safe logging function
void logToFile(const string& text) {
    ofstream file("activity_log.txt", ios::app);
    if (!file) {
        cerr << "Error: Could not open log file!" << endl;
        return;
    }
    file << text << endl;
}

// Get current time as string (no trailing newline)
string getCurrentTime() {
    time_t now = time(0);
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &now);
    string s(buffer);
    if (!s.empty() && s.back() == '\n') s.pop_back();
    return s;
}

// Show login time
void showLoginTime() {
    loginTime = time(0);
    string currentTime = getCurrentTime();
    cout << "Login Time: " << currentTime << endl;
    logToFile("Login Time: " + currentTime);
}

// Show logout time and session duration
void showLogoutAndDuration() {
    time_t logoutTime = time(0);
    string currentTime = getCurrentTime();
    cout << "Logout Time: " << currentTime << endl;
    logToFile("Logout Time: " + currentTime);

    double seconds = difftime(logoutTime, loginTime);
    int minutes = static_cast<int>(seconds / 60);
    cout << "Total Session Duration: " << minutes << " minutes\n";
    logToFile("Total Session Duration: " + to_string(minutes) + " minutes");
}

// Monitor processes and log new ones
void monitorProcesses(set<string>& knownProcesses) {
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap == INVALID_HANDLE_VALUE) {
        cerr << "Failed to take process snapshot!" << endl;
        return;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnap, &pe)) {
        do {
#ifdef UNICODE
            wstring ws(pe.szExeFile);
            string processName(ws.begin(), ws.end());
#else
            string processName(pe.szExeFile);
#endif
            if (knownProcesses.find(processName) == knownProcesses.end()) {
                knownProcesses.insert(processName);
                string log = "PROCESS STARTED: " + processName + " | " + getCurrentTime();
                cout << log << endl;
                logToFile(log);
            }
        } while (Process32Next(hSnap, &pe));
    }

    CloseHandle(hSnap);
}

// Start monitoring session
void startMonitoring() {
    showLoginTime();

    set<string> knownProcesses;
    cout << "\nMonitoring processes... Press CTRL+C to stop.\n";

    while (true) {
        monitorProcesses(knownProcesses);
        Sleep(2000); // Check every 2 seconds
    }
}

// Search activity log
void searchActivity() {
    ifstream file("activity_log.txt");
    if (!file) {
        cout << "No logs found!" << endl;
        return;
    }

    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer
    string keyword;
    cout << "Enter process/application to search (e.g., chrome.exe): ";
    getline(cin, keyword);

    bool found = false;
    string line;
    cout << "\nSearch Results:\n";
    while (getline(file, line)) {
        if (line.find(keyword) != string::npos) {
            cout << line << endl;
            found = true;
        }
    }

    if (!found) cout << "No matching activity found.\n";
    file.close();
}

// View all logs
void viewLogs() {
    ifstream file("activity_log.txt");
    if (!file) {
        cout << "No logs found!" << endl;
        return;
    }

    cout << "\n===== ALL LOGS =====\n";
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

int main() {
    int choice;

    while (true) {
        cout << "\n===== USER ACTIVITY MONITORING TOOL =====\n";
        cout << "1. Start Monitoring\n";
        cout << "2. Search Activity\n";
        cout << "3. View All Logs\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            startMonitoring(); // Continuous monitoring
            break;
        case 2:
            searchActivity();
            break;
        case 3:
            viewLogs();
            break;
        case 4:
            cout << "Exiting..." << endl;
            showLogoutAndDuration(); // Optional logout info
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
} 