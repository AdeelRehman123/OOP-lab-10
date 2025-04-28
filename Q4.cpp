#include <iostream>
#include <fstream>
#include <cstdio>   // for rename()
#include <string>
using namespace std;

class Logger {
private:
    string logFileName = "log.txt";
    int maxFileSize = 5120; // 5KB for demo

    // Get file size using C-style fopen/ftell
    long getFileSize(const string& filename) {
        FILE* file = fopen(filename.c_str(), "r");
        if (!file) return 0;
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        fclose(file);
        return size;
    }

    // Rotate log files if size exceeds limit
    void checkAndRotate() {
        if (getFileSize(logFileName) >= maxFileSize) {
            int count = 1;
            string newFileName;
            do {
                newFileName = "log" + to_string(count) + ".txt";
                FILE* file = fopen(newFileName.c_str(), "r");
                if (!file) break;
                fclose(file);
                count++;
            } while (true);

            rename(logFileName.c_str(), newFileName.c_str());
        }
    }

public:
    void writeLog(const string& message) {
        checkAndRotate();
        ofstream fout(logFileName, ios::app);
        fout << message << endl;
        fout.close();
        cout << "Log written.\n";
    }
};

int main() {
    Logger logger;
    logger.writeLog("System initialized.");
    logger.writeLog("User logged in.");

    // Loop for demo purpose (remove or lower count later)
    for (int i = 0; i < 300; i++) {
        logger.writeLog("Dummy log message " + to_string(i));
    }

    return 0;
}
