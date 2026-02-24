# 🖥️ User Activity Monitoring Tool (Windows)

A Windows-based User Activity Monitoring Tool developed in C++.  
This tool monitors running processes, logs session activity, and provides search functionality.

---

## 📌 Features

- ✅ Real-time process monitoring
- ✅ Logs newly started applications
- ✅ Records login and logout time
- ✅ Calculates total session duration
- ✅ Search functionality for specific processes
- ✅ View complete activity logs
- ✅ Stores logs in a text file (activity_log.txt)

---

## 📌 Technologies Used

- C++
- Windows API
- ToolHelp32Snapshot
- File Handling (fstream)
- STL (set, string)

---

## 📌 How It Works

1. Takes a snapshot of running processes.
2. Detects newly started processes.
3. Logs process name with timestamp.
4. Stores logs inside `activity_log.txt`.
5. Allows searching specific application activity.

---

## 📌 How To Run

1. Open in Visual Studio (Windows)
2. Create new Console Application
3. Replace main.cpp with project code
4. Build and Run

---

## 📌 Sample Output


Login Time: Mon Feb 24 14:30:00 2026
PROCESS STARTED: chrome.exe | Mon Feb 24 14:31:05 2026
PROCESS STARTED: notepad.exe | Mon Feb 24 14:32:10 2026
Logout Time: Mon Feb 24 15:00:00 2026
Total Session Duration: 30 minutes


---

## 📌 Project Structure


User-Activity-Monitor-Windows/
│
├── main.cpp
├── activity_log.txt
└── README.md


---

## 📌 Future Improvements

- GUI Version
- Export logs to CSV
- Filter by date/time
- Background monitoring service
- Admin privilege detection

---

## 📌 Author

Raja Ali Shahid  
BS Cyber Security  
C++ System Programming Project
