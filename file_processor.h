#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class FileProcessor {
private:
    std::string fileName;

public:
    // Конструкторы
    FileProcessor();
    explicit FileProcessor(const std::string& fileName);
    FileProcessor(const FileProcessor& other);

    // Деструктор
    ~FileProcessor();

    // Методы
    void setFileName(const std::string& fileName);
    std::string getFileName() const;
    void processFile(const std::string& searchWord) const;

    // Перегрузка операторов
    friend std::ostream& operator<<(std::ostream& out, const FileProcessor& processor);
    friend std::istream& operator>>(std::istream& in, FileProcessor& processor);
};

#endif // FILE_PROCESSOR_H

