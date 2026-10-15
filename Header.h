#pragma once

#include <vector>
#include <string>
#include <iostream>

class JaggedArray {
private:
    std::vector<std::vector<std::string>> data;

    static const int COLORS[];
    static const int COLORS_COUNT;

    static void setColor(int attr);
    static void resetColor();
    void removeEmptyRows();

    static bool isFirstLetter(const std::string& s);

public:
    JaggedArray();

    void buildFromLines(const std::vector<std::string>& lines);
    void pushRow(const std::vector<std::string>& row);

    size_t rows() const;
    size_t cols(size_t row) const;

    std::vector<std::string>& operator[](size_t i);
    const std::vector<std::string>& operator[](size_t i) const;

    bool deleteAt(size_t i, size_t j);
    int  deleteByValue(const std::string& item);

    bool add_endline(size_t k, const std::string& item);

    JaggedArray  operator+(const JaggedArray& other) const;
    JaggedArray& operator++();
    JaggedArray  operator++(int);

    void sortRows();

    void print() const;

    const std::vector<std::vector<std::string>>& getData() const;
};


bool readLinesFromFile(const std::string& filename,
    std::vector<std::string>& out);