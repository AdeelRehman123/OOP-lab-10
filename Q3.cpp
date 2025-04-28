#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct User {
    string user_id;
    string first_name;
    string last_name;
    string address;
    string email;
};

struct Product {
    string product_id;
    string product_name;
    string description;
    int price;
};

struct Order {
    string order_id;
    string user_id;
    string product_id;
    int total_paid;
};

class Database {
public:
    void addDummyData() {
        ofstream ufile("users.txt");
        ufile << "U1,Linus,Torvalds,Finland,linus@linux.org\n";
        ufile << "U2,Bill,Gates,USA,bill@microsoft.com\n";
        ufile.close();

        ofstream pfile("products.txt");
        pfile << "P1,Laptop,High-end Laptop,1500\n";
        pfile << "P2,Phone,Smartphone,700\n";
        pfile << "P3,Server,Dedicated Server,3000\n";
        pfile.close();

        ofstream ofile("orders.txt");
        ofile << "O1,U1,P1,1500\n";
        ofile << "O2,U1,P3,3000\n";
        ofile << "O3,U2,P2,700\n";
        ofile.close();

        cout << "Dummy data added.\n";
    }

    // Fetch product names associated with 'Linus'
    void fetchProductsByUser(string targetName) {
        vector<User> users;
        vector<Product> products;
        vector<Order> orders;

        // Load Users
        ifstream ufile("users.txt");
        string line;
        while (getline(ufile, line)) {
            stringstream ss(line);
            string uid, fname, lname, addr, email;
            getline(ss, uid, ',');
            getline(ss, fname, ',');
            getline(ss, lname, ',');
            getline(ss, addr, ',');
            getline(ss, email, ',');
            users.push_back({uid, fname, lname, addr, email});
        }
        ufile.close();

        // Load Products
        ifstream pfile("products.txt");
        while (getline(pfile, line)) {
            stringstream ss(line);
            string pid, pname, desc, price;
            getline(ss, pid, ',');
            getline(ss, pname, ',');
            getline(ss, desc, ',');
            getline(ss, price, ',');
            products.push_back({pid, pname, desc, stoi(price)});
        }
        pfile.close();

        // Load Orders
        ifstream ofile("orders.txt");
        while (getline(ofile, line)) {
            stringstream ss(line);
            string oid, uid, pid, total;
            getline(ss, oid, ',');
            getline(ss, uid, ',');
            getline(ss, pid, ',');
            getline(ss, total, ',');
            orders.push_back({oid, uid, pid, stoi(total)});
        }
        ofile.close();

        // Find User ID for 'Linus'
        string linusID = "";
        for (auto u : users) {
            if (u.first_name == targetName) {
                linusID = u.user_id;
                break;
            }
        }

        if (linusID == "") {
            cout << "User " << targetName << " not found.\n";
            return;
        }

        // Fetch Products ordered by 'Linus'
        cout << "\nProducts associated with user " << targetName << ":\n";
        for (auto o : orders) {
            if (o.user_id == linusID) {
                for (auto p : products) {
                    if (p.product_id == o.product_id) {
                        cout << "- " << p.product_name << endl;
                    }
                }
            }
        }
    }
};

int main() {
    Database db;
    db.addDummyData(); // Adds sample users, products, orders
    db.fetchProductsByUser("Linus"); // Fetch and display products for Linus

    return 0;
}
