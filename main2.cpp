#include <iostream>
#include <vector>
#include <algorithm>
#include "sign.h"
#include "file_processor.h"

int main() {
    int taskOption;
    std::cout << "Выберите задание:\n"
              << "1. Управление знаками зодиака\n"
              << "2. Файловые и строковые потоки\n"
              << "Ваш выбор: ";
    std::cin >> taskOption;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::cerr << "Ошибка: Введите числовое значение для выбора задания.\n";
        return 1;
    }

    if (taskOption == 1) {
        int option;

        try {
            do {
                std::cout << "\nМеню:\n"
                          << "1. Добавить запись\n"
                          << "2. Редактировать запись\n"
                          << "3. Удалить запись\n"
                          << "4. Добавить запись на определенную позицию\n"
                          << "5. Показать все записи\n"
                          << "6. Упорядочить записи по знаку зодиака\n"
                          << "7. Найти записи по месяцу\n"
                          << "8. Выход\n"
                          << "Выберите опцию: ";
                std::cin >> option;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');
                    std::cerr << "Ошибка: Введите числовое значение.\n";
                    continue;
                }

                if (option == 1) {
                    SIGN* newSign = new SIGN();
                    std::cin >> *newSign;
                    SIGN::addRecord(newSign);
                } else if (option == 2) {
                    int index;
                    std::cout << "Введите индекс записи для редактирования: ";
                    std::cin >> index;
                    if (std::cin.fail()) throw std::invalid_argument("Некорректный индекс.");
                    SIGN::editRecord(index);
                } else if (option == 3) {
                    int index;
                    std::cout << "Введите индекс записи для удаления: ";
                    std::cin >> index;
                    if (std::cin.fail()) throw std::invalid_argument("Некорректный индекс.");
                    SIGN::deleteRecord(index);
                } else if (option == 4) {
                    int position;
                    SIGN* newSign = new SIGN();
                    std::cin >> *newSign;
                    std::cout << "Введите позицию для вставки: ";
                    std::cin >> position;
                    if (std::cin.fail()) throw std::invalid_argument("Некорректная позиция.");
                    SIGN::insertRecord(position, newSign);
                } else if (option == 5) {
                    SIGN::displayRecords();
                } else if (option == 6) {
                    SIGN::sortRecords();
                } else if (option == 7) {
                    int month;
                    std::cout << "Введите месяц: ";
                    std::cin >> month;
                    if (std::cin.fail() || month < 1 || month > 12) {
                        std::cin.clear();
                        std::cin.ignore(INT_MAX, '\n');
                        throw std::invalid_argument("Месяц должен быть числом от 1 до 12.");
                    }
                    SIGN::findByMonth(month);
                }
            } while (option != 8);

        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    } else if (taskOption == 2) {
        try {
            FileProcessor processor;
            std::cin >> processor;

            std::string searchWord;
            std::cout << "Введите слово для поиска: ";
            std::cin >> searchWord;

            processor.processFile(searchWord);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    } else {
        std::cerr << "Ошибка: Неверный выбор задания.\n";
    }

    return 0;
}

