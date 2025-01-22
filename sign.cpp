#include "sign.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

// Инициализация статического поля
std::vector<SIGN*> SIGN::records;

// Конструкторы и деструктор
SIGN::SIGN() : lastName(""), firstName(""), zodiacSign(""), birthDate{0, 0, 0} {
    std::cout << "Вызван конструктор по умолчанию для объекта SIGN\n";
}

SIGN::SIGN(const SIGN& other)
    : lastName(other.lastName), firstName(other.firstName), zodiacSign(other.zodiacSign) {
    birthDate[0] = other.birthDate[0];
    birthDate[1] = other.birthDate[1];
    birthDate[2] = other.birthDate[2];
    std::cout << "Вызван конструктор копирования для объекта SIGN\n";
}

SIGN::~SIGN() {
    std::cout << "Вызван деструктор для объекта SIGN\n";
}

// Методы установки
void SIGN::setLastName(const std::string& lastName) { this->lastName = lastName; }
void SIGN::setFirstName(const std::string& firstName) { this->firstName = firstName; }
void SIGN::determineZodiacSign() {
    int day = birthDate[0];
    int month = birthDate[1];

    if ((month == 1 && day >= 20) || (month == 2 && day <= 18))
        zodiacSign = "Aquarius";
    else if ((month == 2 && day >= 19) || (month == 3 && day <= 20))
        zodiacSign = "Pisces";
    else if ((month == 3 && day >= 21) || (month == 4 && day <= 19))
        zodiacSign = "Aries";
    else if ((month == 4 && day >= 20) || (month == 5 && day <= 20))
        zodiacSign = "Taurus";
    else if ((month == 5 && day >= 21) || (month == 6 && day <= 20))
        zodiacSign = "Gemini";
    else if ((month == 6 && day >= 21) || (month == 7 && day <= 22))
        zodiacSign = "Cancer";
    else if ((month == 7 && day >= 23) || (month == 8 && day <= 22))
        zodiacSign = "Leo";
    else if ((month == 8 && day >= 23) || (month == 9 && day <= 22))
        zodiacSign = "Virgo";
    else if ((month == 9 && day >= 23) || (month == 10 && day <= 22))
        zodiacSign = "Libra";
    else if ((month == 10 && day >= 23) || (month == 11 && day <= 21))
        zodiacSign = "Scorpio";
    else if ((month == 11 && day >= 22) || (month == 12 && day <= 21))
        zodiacSign = "Sagittarius";
    else if ((month == 12 && day >= 22) || (month == 1 && day <= 19))
        zodiacSign = "Capricorn";
}

void SIGN::setBirthDate(int day, int month, int year) {
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 0)
        throw std::invalid_argument("Недопустимая дата рождения");
    birthDate[0] = day;
    birthDate[1] = month;
    birthDate[2] = year;
    determineZodiacSign();
}

// Методы получения
std::string SIGN::getLastName() const { return lastName; }
std::string SIGN::getFirstName() const { return firstName; }
std::string SIGN::getZodiacSign() const { return zodiacSign; }
void SIGN::getBirthDate(int& day, int& month, int& year) const {
    day = birthDate[0];
    month = birthDate[1];
    year = birthDate[2];
}

// Управление записями
void SIGN::addRecord(SIGN* sign) {
    records.push_back(sign);
}

void SIGN::editRecord(size_t index) {
    if (index < records.size()) {
        std::cout << "Редактирование записи:\n";
        std::cin >> *records[index];
    } else {
        throw std::out_of_range("Индекс вне диапазона");
    }
}

void SIGN::deleteRecord(size_t index) {
    if (index < records.size()) {
        delete records[index];
        records.erase(records.begin() + index);
        std::cout << "Запись удалена.\n";
    } else {
        throw std::out_of_range("Индекс вне диапазона");
    }
}

void SIGN::insertRecord(size_t position, SIGN* sign) {
    if (position <= records.size()) {
        records.insert(records.begin() + position, sign);
    } else {
        throw std::out_of_range("Позиция вне диапазона");
    }
}

void SIGN::displayRecords() {
    for (size_t i = 0; i < records.size(); ++i) {
        std::cout << "Индекс " << i << ": " << *records[i] << "\n";
    }
}

void SIGN::sortRecords() {
    std::sort(records.begin(), records.end(), [](SIGN* a, SIGN* b) {
        return a->getZodiacSign() < b->getZodiacSign();
    });
    std::cout << "Записи упорядочены по знаку зодиака.\n";
}

void SIGN::findByMonth(int month) {
    if (month < 1 || month > 12) {
        std::cout << "Ошибка: Месяц должен быть от 1 до 12.\n";
        return;
    }
    bool found = false;
    for (SIGN* sign : records) {
        int m = sign->birthDate[1];
        if (m == month) {
            std::cout << *sign << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Нет записей для указанного месяца.\n";
    }
}

// Перегрузка операторов
std::ostream& operator<<(std::ostream& out, const SIGN& sign) {
    out << "Фамилия: " << sign.lastName
        << ", Имя: " << sign.firstName
        << ", Знак зодиака: " << sign.zodiacSign
        << ", Дата рождения: " << sign.birthDate[0] << "." << sign.birthDate[1] << "." << sign.birthDate[2];
    return out;
}

std::istream& operator>>(std::istream& in, SIGN& sign) {
    std::cout << "Введите фамилию: ";
    in >> sign.lastName;
    std::cout << "Введите имя: ";
    in >> sign.firstName;
    std::cout << "Введите дату рождения (день, месяц, год): ";
    in >> sign.birthDate[0] >> sign.birthDate[1] >> sign.birthDate[2];
    if (sign.birthDate[0] < 1 || sign.birthDate[0] > 31 || sign.birthDate[1] < 1 || sign.birthDate[1] > 12 || sign.birthDate[2] < 0) {
        throw std::invalid_argument("Недопустимая дата");
    }
    sign.determineZodiacSign();
    return in;
}

