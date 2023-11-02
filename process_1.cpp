#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Enter arguments!:)" << endl;
        return 1;
    }

    // Об'єднуємо аргументи командного рядка в одну рядкову змінну
    string command;
    for (int i = 1; i < argc; i++) {
        command += argv[i];
        if (i < argc - 1) {
            command += " ";
        }
    }

    // Розділяємо команди, якщо вони вказані через точку з комою
    size_t pos = 0;
    while ((pos = command.find(';')) != string::npos) {
        string single_command = command.substr(0, pos);
        int exit_code = system(single_command.c_str());
        cout << "Command: " << single_command << " - Exit Code: " << exit_code << endl;
        command.erase(0, pos + 1);
    }

    // Виконуємо залишок команди
    if (!command.empty()) {
        int exit_code = system(command.c_str());
        cout << "Command: " << command << " - Exit Code: " << exit_code << endl;
    }

    return 0;
}
