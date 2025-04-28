#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Encryptor {
private:
    string text;
    string encryptedText;

public:
    void getInput() {
        cout << "Enter String: ";
        getline(cin, text);
    }

    void encrypt() {
        encryptedText = "";
        for (int i = 0; i < text.length(); i++) {
            encryptedText += char(text[i] + (i + 1));
        }
        cout << "\nNormal Text: " << text << endl;
    }

    void writeToFile() {
        ofstream fout("encrypted_file.txt");
        fout << encryptedText;
        fout.close();
        cout << "Encrypted text inserted in file" << endl;
    }

    void readAndDecrypt() {
        string fileText;
        ifstream fin("encrypted_file.txt");
        getline(fin, fileText);
        fin.close();

        string decryptedText = "";
        for (int i = 0; i < fileText.length(); i++) {
            decryptedText += char(fileText[i] - (i + 1));
        }

        cout << "Encrypted Text Read from file: " << fileText << endl;
        cout << "Decrypted Text Read then decoded from file: " << decryptedText << endl;
    }
};

int main() {
    Encryptor e;
    e.getInput();
    e.encrypt();
    e.writeToFile();
    e.readAndDecrypt();

    return 0;
}
