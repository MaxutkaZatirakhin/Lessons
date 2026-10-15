#include "Header.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

#ifdef _WIN32
#include <windows.h>
#endif

const int JaggedArray::COLORS[] = {
    FOREGROUND_RED | FOREGROUND_INTENSITY,
    FOREGROUND_BLUE | FOREGROUND_INTENSITY,
    FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
};
const int JaggedArray::COLORS_COUNT = 4;

void JaggedArray::setColor(int attr) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)attr);
#else
    (void)attr;
#endif
}

void JaggedArray::resetColor() {
    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void JaggedArray::removeEmptyRows() {
    data.erase(
        std::remove_if(data.begin(), data.end(),
            [](const std::vector<std::string>& row) { return row.empty(); }),
        data.end()
    );
}

bool JaggedArray::isFirstLetter(const std::string& s) {
    if (s.empty()) return false;
    unsigned char c = (unsigned char)s[0];

    if (c >= 'a' && c <= 'z') return true;
    if (c >= 'A' && c <= 'Z') return true;

    if (c >= 0xE0 && c <= 0xFF) return true;  
    if (c == 0xB8) return true;               
    if (c >= 0xC0 && c <= 0xDF) return true;  
    if (c == 0xA8) return true;               

    return false;
}

JaggedArray::JaggedArray() : data(0) {}

void JaggedArray::buildFromLines(const std::vector<std::string>& lines) {
    data.clear();
    data.resize(lines.size());

    for (size_t i = 0; i < lines.size(); i++) {
        std::istringstream iss(lines[i]);
        std::string token;
        while (iss >> token) {
            data[i].push_back(token);
        }
    }
}

void JaggedArray::pushRow(const std::vector<std::string>& row) {
    data.push_back(row);
}

size_t JaggedArray::rows() const { return data.size(); }

size_t JaggedArray::cols(size_t row) const {
    if (row >= data.size()) return 0;
    return data[row].size();
}

std::vector<std::string>& JaggedArray::operator[](size_t i) { return data[i]; }
const std::vector<std::string>& JaggedArray::operator[](size_t i) const { return data[i]; }

bool JaggedArray::deleteAt(size_t i, size_t j) {
    if (i >= data.size() || j >= data[i].size()) return false;
    data[i].erase(data[i].begin() + j);
    removeEmptyRows();
    return true;
}

int JaggedArray::deleteByValue(const std::string& item) {
    int removed = 0;
    for (auto& row : data) {
        auto it = std::remove(row.begin(), row.end(), item);
        removed += (int)(row.end() - it);
        row.erase(it, row.end());
    }
    removeEmptyRows();
    return removed;
}

bool JaggedArray::add_endline(size_t k, const std::string& item) {
    if (k > data.size()) return false;

    if (k == data.size()) {
        data.push_back({}); 
    }

    data[k].push_back(item);
    return true;
}

JaggedArray JaggedArray::operator+(const JaggedArray& other) const {
    JaggedArray result;
    size_t maxRows = (data.size() > other.data.size()) ? data.size() : other.data.size();
    result.data.resize(maxRows);

    for (size_t i = 0; i < maxRows; i++) {
        size_t r1 = (i < data.size()) ? data[i].size() : 0;
        size_t r2 = (i < other.data.size()) ? other.data[i].size() : 0;
        size_t maxCols = (r1 > r2) ? r1 : r2;
        result.data[i].resize(maxCols);

        for (size_t j = 0; j < maxCols; j++) {
            std::string a = (j < r1) ? data[i][j] : "";
            std::string b = (j < r2) ? other.data[i][j] : "";

            if (a.empty() && b.empty()) result.data[i][j] = "";
            else if (a.empty())         result.data[i][j] = b;
            else if (b.empty())         result.data[i][j] = a;
            else                        result.data[i][j] = a + b;
        }
    }
    return result;
}

JaggedArray& JaggedArray::operator++() {
    for (auto& row : data) {
        for (auto& s : row) {
            if (isFirstLetter(s)) {
                s[0] = (char)((unsigned char)s[0] + 1);
            }
        }
    }
    return *this;
}

JaggedArray JaggedArray::operator++(int) {
    JaggedArray copy = *this;
    ++(*this);
    return copy;
}

void JaggedArray::sortRows() {
    for (auto& row : data)
        std::sort(row.begin(), row.end());
}

void JaggedArray::print() const {
    for (size_t i = 0; i < data.size(); i++) {
        setColor(COLORS[i % COLORS_COUNT]);
        for (const auto& s : data[i])
            std::cout << "\"" << s << "\" ";
        std::cout << "\n";
        resetColor();
    }
}

const std::vector<std::vector<std::string>>& JaggedArray::getData() const {
    return data;
}

bool readLinesFromFile(const std::string& filename,
    std::vector<std::string>& out)
{
    std::ifstream fin(filename);
    if (!fin.is_open()) return false;

    out.clear();
    std::string line;
    while (std::getline(fin, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        out.push_back(line);
    }
    return true;
}