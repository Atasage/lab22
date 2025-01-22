#ifndef SIGN_H
#define SIGN_H

#include <iostream>
#include <string>
#include <vector>

class SIGN {
private:
    std::string lastName;
    std::string firstName;
    std::string zodiacSign;
    int birthDate[3]; // [день, месяц, год]
    static std::vector<SIGN*> records; // Хранилище записей

    void determineZodiacSign(); // Определение знака зодиака на основе даты

public:
    SIGN();
    SIGN(const std::string& lastName, const std::string& firstName, int day, int month, int year);
    SIGN(const SIGN& other);
    ~SIGN();

    void setLastName(const std::string& lastName);
    void setFirstName(const std::string& firstName);
    void setBirthDate(int day, int month, int year);

    std::string getLastName() const;
    std::string getFirstName() const;
    std::string getZodiacSign() const;
    void getBirthDate(int& day, int& month, int& year) const;

    static void addRecord(SIGN* sign);
    static void editRecord(size_t index);
    static void deleteRecord(size_t index);
    static void insertRecord(size_t position, SIGN* sign);
    static void displayRecords();
    static void sortRecords();
    static void findByMonth(int month);

    friend std::ostream& operator<<(std::ostream& out, const SIGN& sign);
    friend std::istream& operator>>(std::istream& in, SIGN& sign);
};

#endif // SIGN_H
