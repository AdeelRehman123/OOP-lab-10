#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class ToDoManager {
private:
    string fileName = "todo.txt";

public:
    void addTask(const string& task) {
        ofstream fout(fileName, ios::app);
        fout << task << ",Pending" << endl;
        fout.close();
        cout << "Task added.\n";
    }

    void viewTasks() {
        ifstream fin(fileName);
        string line;
        int count = 1;
        cout << "\nTasks:\n";
        while (getline(fin, line)) {
            cout << count++ << ". " << line << endl;
        }
        fin.close();
    }

    void markTaskDone(int taskNumber) {
        ifstream fin(fileName);
        vector<string> tasks;
        string line;
        while (getline(fin, line)) {
            tasks.push_back(line);
        }
        fin.close();

        if (taskNumber < 1 || taskNumber > tasks.size()) {
            cout << "Invalid task number!\n";
            return;
        }

        // Update selected task
        size_t pos = tasks[taskNumber - 1].find(",Pending");
        if (pos != string::npos) {
            tasks[taskNumber - 1].replace(pos, 7, ",Done");
        }

        ofstream fout(fileName);
        for (auto& t : tasks) {
            fout << t << endl;
        }
        fout.close();

        cout << "Task marked as done.\n";
    }
};

int main() {
    ToDoManager todo;
    int choice;
    string task;
    int num;

    do {
        cout << "\n1. Add Task\n2. View Tasks\n3. Mark Task as Done\n0. Exit\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter task: ";
                getline(cin, task);
                todo.addTask(task);
                break;
            case 2:
                todo.viewTasks();
                break;
            case 3:
                todo.viewTasks();
                cout << "Enter task number to mark as done: ";
                cin >> num;
                todo.markTaskDone(num);
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
