#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include "Header.h"

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <clocale>

#ifdef _WIN32
#include <windows.h>
#endif

std::vector<std::string> readLines(const std::string& label,
    const std::string& defaultFile)
{
    std::cout << "\n=== Источник массива " << label << " ===\n";
    std::cout << "1 - ввести с клавиатуры\n";
    std::cout << "2 - прочитать из файла (" << defaultFile << ")\n";  //  C:\Users\Admin\source\repos\ссс.txt
    std::cout << ": ";

    int choice = 1;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<std::string> lines;

    if (choice == 2) {
        std::string filename;
        std::cout << "Имя файла (Enter = " << defaultFile << "): ";
        std::getline(std::cin, filename);
        if (filename.empty()) filename = defaultFile;

        if (readLinesFromFile(filename, lines)) {
            std::cout << "Прочитано строк: " << lines.size()
                << " из \"" << filename << "\"\n";
        }
        else {
            std::cout << "Не удалось открыть \"" << filename
                << "\". Введите строки вручную.\n";
            choice = 1;
        }
    }

    if (choice == 1) {
        std::cout << "Сколько строк? ";
        int n = 0;
        std::cin >> n;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (int i = 0; i < n; i++) {
            std::cout << "Строка " << i << ": ";
            std::string line;
            std::getline(std::cin, line);
            lines.push_back(line);
        }
    }

    return lines;
}

int main() {
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif
    setlocale(LC_ALL, "Russian");

    std::vector<std::string> linesA = readLines("A", ".txt");
    JaggedArray A;
    A.buildFromLines(linesA);

    std::cout << "\nМассив A:\n";
    A.print();

    std::vector<std::string> linesB = readLines("B", ".txt");
    JaggedArray B;
    B.buildFromLines(linesB);

    std::cout << "\nМассив B:\n";
    B.print();

    JaggedArray C = A + B;
    std::cout << "\nA + B:\n";
    C.print();

    JaggedArray E = A;

    std::cout << "\nA после ++:\n";
    ++E;
    E.print();

    size_t di, dj;
    std::cout << "\ndelete(i, j): введите i и j: ";
    std::cin >> di >> dj;
    if (E.deleteAt(di, dj)) std::cout << "Удалено.\n";
    else                    std::cout << "Индекс вне диапазона.\n";
    E.print();

    std::string item;
    std::cout << "\ndelete(item): введите значение: ";
    std::cin >> item;
    int removed = E.deleteByValue(item);
    std::cout << "Удалено вхождений: " << removed << "\n";
    E.print();

    size_t k;
    std::string newItem;
    std::cout << "\nadd_endline(k, item): введите k и item: ";
    std::cin >> k >> newItem;
    if (E.add_endline(k, newItem)) std::cout << "Добавлено.\n";
    else                           std::cout << "Строки с таким номером нет.\n";
    E.print();

    std::cout << "\nДо сортировки:\n";
    E.print();
    E.sortRows();
    std::cout << "После сортировки:\n";
    E.print();

    return 0;
}