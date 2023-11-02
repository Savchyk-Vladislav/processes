#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
using namespace std;

void displayHelp() {
    cout << "Available options: " << endl << "-h or --help: Display help" << endl << "-b or --buffer <size>: Set buffer size (default 127)";
}

int main(int argc, char* argv[]) {
    char* username = getenv("USER");
    if (username == nullptr) {
        username = "user";
    }
    int buffer_size = 127;
    // Обробка опцій командного рядка
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            displayHelp();
            return 0;
        } else if ((strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--buffer") == 0) && i + 1 < argc) {
            buffer_size = atoi(argv[i + 1]);
            i++;
        }
    }
    char* buffer = new char[buffer_size];
    cout << "Welcome, " << username << "!" << endl;
    while (true) {
        cout << "[" << username << "]$ ";
        if (fgets(buffer, buffer_size, stdin) == nullptr) {
            cerr << "Command input error. Try again." << endl;
            continue;
        }
        // Видаляємо символ нового рядка
        size_t input_length = strlen(buffer);
        if (input_length > 0 && buffer[input_length - 1] == '\n') {
            buffer[input_length - 1] = '\0';
        }
        if (strcmp(buffer, "stop") == 0) {
            break;
        }
        // Виконання команди за допомогою системної функції
        int result = system(buffer);
        if (result == 0) {
            cout << "The command was executed successfully." << endl;
        } else {
            cerr << "Command execution error." << endl;
        }
    }
    cout << "Wait 3 seconds..." << endl;
    sleep(3);
    // Очистити екран
    system("clear");
    delete[] buffer;
    return 0;
}
