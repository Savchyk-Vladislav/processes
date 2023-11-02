#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

// Функція для обробки завершення процесу
void processHandler(int number) {
    cout << "Handler #" << number << " is performed." << endl;
    sleep(1); // Затримка на 1 секунду
    cout << "Handler #" << number << " completed." << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "You need to specify the number of handlers." << endl;
        return 1;
    }
    int numHandlers = atoi(argv[1]);
    if (numHandlers <= 0) {
        cerr << "The number of handlers must be greater than 0." << endl;
        return 1;
    }
    // Реєстрація обробників завершення процесу
    for (int i = 1; i <= numHandlers; ++i) {
        if (fork() == 0) {
            processHandler(i);
            exit(0);
        }
    }
    // Очікування завершення всіх обробників
    for (int i = 0; i < numHandlers; ++i) {
        wait(nullptr);
    }
    cout << "All handlers completed." << endl;
    return 0;
}
