#include "file_processor.h"

// Конструктор по умолчанию
FileProcessor::FileProcessor() : fileName("") {
    std::cout << "Вызван конструктор по умолчанию для объекта FileProcessor\n";
}

// Конструктор с параметром
FileProcessor::FileProcessor(const std::string& fileName) : fileName(fileName) {
    std::cout << "Вызван конструктор с параметром для объекта FileProcessor\n";
}

// Конструктор копирования
FileProcessor::FileProcessor(const FileProcessor& other) : fileName(other.fileName) {
    std::cout << "Вызван конструктор копирования для объекта FileProcessor\n";
}

// Деструктор
FileProcessor::~FileProcessor() {
    std::cout << "Вызван деструктор для объекта FileProcessor\n";
}

// Методы
void FileProcessor::setFileName(const std::string& fileName) {
    this->fileName = fileName;
}

std::string FileProcessor::getFileName() const {
    return fileName;
}

void FileProcessor::processFile(const std::string& searchWord) const {
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + fileName);
    }

    std::string line;
    int sentenceCount = 0;

    std::cout << "Обработка файла...\n";

    while (std::getline(inputFile, line)) {
        std::istringstream lineStream(line);
        std::string sentence;
        while (std::getline(lineStream, sentence, '.')) {
            if (sentence.empty()) continue;

            int wordCount = 0;
            std::istringstream sentenceStream(sentence);
            std::string word;
            while (sentenceStream >> word) {
                if (word == searchWord) {
                    wordCount++;
                }
            }
            std::cout << "Предложение: " << sentence << ". Слово \"" << searchWord 
                      << "\" встретилось " << wordCount << " раз(а).\n";
            sentenceCount++;
        }
    }

    if (sentenceCount == 0) {
        std::cout << "Файл пуст или не содержит предложений.\n";
    }

    inputFile.close();
}

// Перегрузка операторов
std::ostream& operator<<(std::ostream& out, const FileProcessor& processor) {
    out << "FileProcessor [Имя файла: " << processor.fileName << "]";
    return out;
}

std::istream& operator>>(std::istream& in, FileProcessor& processor) {
    std::cout << "Введите имя файла: ";
    in >> processor.fileName;
    return in;
}

