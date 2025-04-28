#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Employee {
public:
    int id;
    string name;
    string designation;
    int yearsOfService;

    // Constructor
    Employee(int i = 0, string n = "", string d = "", int y = 0)
        : id(i), name(n), designation(d), yearsOfService(y) {}

    // Convert employee to string for file
    string toString() {
        return to_string(id) + "," + name + "," + designation + "," + to_string(yearsOfService);
    }
};

class EmployeeManager {
private:
    string filename;

public:
    EmployeeManager(string fname) {
        filename = fname;
    }

    // Create initial dummy data
    void createDummyData() {
        ofstream fout(filename);
        fout << "1,Ali,Manager,3\n";
        fout << "2,Ayesha,Developer,1\n";
        fout << "3,Ahmed,Manager,2\n";
        fout << "4,Sara,Designer,4\n";
        fout.close();
        cout << "Dummy data written to file.\n";
    }

    // Read all data
    vector<Employee> readAll() {
        vector<Employee> employees;
        ifstream fin(filename);
        string line;
        while (getline(fin, line)) {
            stringstream ss(line);
            string id, name, designation, years;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, designation, ',');
            getline(ss, years, ',');
            employees.push_back(Employee(stoi(id), name, designation, stoi(years)));
        }
        fin.close();
        return employees;
    }

    // (a) Find managers with at least 2 years of service
    vector<Employee> findManagersWithService() {
        vector<Employee> result;
        vector<Employee> all = readAll();
        for (auto emp : all) {
            if (emp.designation == "Manager" && emp.yearsOfService >= 2)
                result.push_back(emp);
        }
        cout << "Managers with at least 2 years of service:\n";
        for (auto emp : result)
            cout << emp.toString() << endl;
        return result;
    }

    // (b) Delete all data except above result
    void deleteExcept(vector<Employee> selected) {
        ofstream fout(filename);
        for (auto emp : selected)
            fout << emp.toString() << endl;
        fout.close();
        cout << "Deleted all data except managers with 2+ years.\n";
    }

    // (c) Increment IDs and years, then rewrite file
    void incrementAndRewrite(vector<Employee> selected) {
        ofstream fout(filename);
        for (auto& emp : selected) {
            emp.id += 1;
            emp.yearsOfService += 1;
            fout << emp.toString() << endl;
        }
        fout.close();
        cout << "Updated data written with incremented IDs and years.\n";
    }
};

int main() {
    EmployeeManager manager("employees.txt");

    manager.createDummyData();   // write initial dummy data

    auto foundManagers = manager.findManagersWithService(); // (a)
    manager.deleteExcept(foundManagers);                    // (b)
    manager.incrementAndRewrite(foundManagers);              // (c)

    return 0;
}
