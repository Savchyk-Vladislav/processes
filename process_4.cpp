#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <getopt.h>
using namespace std;

// Дефолтна змінна для імені файлу
string FILE_NAME = "default_file";

// Функція для генерації випадкового числа в діапазоні [0, 1]
double generateRandomNumber() {
    return (double)rand() / RAND_MAX;
}

int main(int argc, char* argv[]) {
    int numberOfCount = 1;  // За замовчанням запускаємо 1 дочірню програму
    // Обробка опцій командного рядка за допомогою getopt
    int option;
    while ((option = getopt(argc, argv, "f:n:")) != -1) {
        switch (option) {
            case 'f':
                FILE_NAME = optarg; // Передає у FILE_NAME значення(рядок) опції -f
                break;
            case 'n':
                numberOfCount = stoi(optarg); // Передає у numberOfPrograms цілочисельне значення отриманого рядка з опції -n
                break;
            default:
                cerr << "Невідома опція" << endl;
                return 1;
        }
    }
    // Створення файлу
    string fileName = FILE_NAME + "_" + to_string(numberOfCount) + ".txt";
    ofstream outputFile(fileName);
    // Генерація випадкових чисел та збереження їх у файлі
    srand(time(nullptr));
    for (int i = 1; i <= numberOfCount; i++) {
        if (outputFile.is_open()) {
            double randomValue = generateRandomNumber();
            outputFile << randomValue << endl;
        }
    }
    outputFile.close();
    cout << "Випадкові числа збережено у файлі: " << fileName << endl;
    return 0;
}
