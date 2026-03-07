// laba_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Header_laba_3.h"
#include <algorithm>  

Bookmark::Bookmark(std::string col, std::string mat, int pag)
    : color(col), material(mat), page(pag) {
}
Bookmark::Bookmark(const Bookmark& other)
    : color(other.color), material(other.material), page(other.page) {
}

Bookmark& Bookmark::operator++() {
    ++page;
    std::cout << "Moved to page " << page << std::endl;
    return *this;
}
Bookmark& Bookmark::operator--() {
    if (page > 1) {
        --page;
        std::cout << "Moved to page " << page << std::endl;
    }
    else {
        std::cout << "Already at page 1, cannot move back" << std::endl;
    }
    return *this;
}

Book::Book(const std::string& writer, const std::string& title, const std::vector<std::string>& vec, float rating, int pages, int cost)
    : writer_(writer), title_(title), vec_(vec), rating_(rating), pages_(pages), cost_(cost) {
}
Book::Book(const Book& other)
    : writer_(other.writer_), title_(other.title_), vec_(other.vec_), rating_(other.rating_), pages_(other.pages_), cost_(other.cost_) {
}
Book::~Book() {
    vec_.clear();
    std::cout << "dtor" << std::endl;
}

std::string Book::get_w() {
    return writer_;
}
std::string Book::get_t() {
    return title_;
}
std::vector<std::string> Book::get_v() {
    return vec_;
}
float Book::get_r() {
    return rating_;
}
int Book::get_p() {
    return pages_;
}
int Book::get_c() {
    return cost_;
}

Bookmark* Book::getBookmark() const {
    return bookmark_;
}

void Book::change_cost(int newcost) {
    if (newcost >= 0) {
        cost_ = newcost;
        std::cout << "new cost" << cost_ << std::endl;
    }
    else {
        std::cout << "error" << std::endl;
    }
}

void Book::change_rating_pl() {
    float newrating = rating_ + 1;
    rating_ = newrating;
}

void Book::change_rating_min() {
    float newrating = rating_ - 1;
    rating_ = newrating;
}

void Book::add_Bookmark(const Bookmark& bookmark) {
    if (bookmark.page < 1 || bookmark.page > pages_) {
        std::cout << "Error!" << std::endl;
        return;
    }
    if (bookmark_) {
        delete bookmark_;
        std::cout << "del" << std::endl;
    }
    bookmark_ = new Bookmark(bookmark);
    std::cout << "Bookmark added at page " << bookmark.page << std::endl;
}

void Book::delete_Bookmark() {
    if (bookmark_) {
        delete bookmark_;
        bookmark_ = nullptr;
        std::cout << "del" << std::endl;
    }
    else {
        std::cout << "No bookmark" << std::endl;
    }
}

void Book::move_forward() {
    if (!bookmark_) {
        std::cout << "No bookmark" << std::endl;
        return;
    }
    if (bookmark_->page< pages_) {
        ++(*bookmark_);
    }
    else {
        std::cout << "Error!" << std::endl;
    }
}

void Book::move_back() {
    if (!bookmark_) {
        std::cout << "No bookmark" << std::endl;
        return;
    }
    if (bookmark_->page > 1) {
        --(*bookmark_);
    }
    else {
        std::cout << "Error!" << std::endl;
    }
}

Book& Book::operator=(const Book& other) {
    if (this != &other) {
        writer_ = other.writer_;
        title_ = other.title_;
        vec_ = other.vec_;
        rating_ = other.rating_;
        pages_ = other.pages_;
        cost_ = other.cost_;
    }
    return *this;
}

Book& Book:: operator+(const Book& other) {
    pages_ += other.pages_;
    cost_ = (cost_ + other.cost_) * 0.85;

    if (writer_ == other.writer_) {
        for (const auto& work : other.vec_) {
            bool exists = false;
            for (const auto& vec : vec_) {
                if (vec == work) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                vec_.push_back(work);
            }
        }
    }
    else {
        std::cout << "Error";
    }
    return *this;
}

Book& Book::operator+=(const Book& other) {
    pages_ += other.pages_;
    cost_ = (cost_ + other.cost_) * 0.85;
    std::string gg = writer_;
    writer_ = writer_ + " и " + other.writer_;

    for (auto& work : vec_) {
        work = gg + work;
    }
    for (const auto& work : other.vec_) {
        vec_.push_back(other.writer_ + work);
    }
    return *this;
}

Book Book::operator/(const Book& other) {
    Book result;
    result.writer_ = writer_;
    result.title_ = title_;
    result.rating_ = rating_;
    result.pages_ = static_cast<int>((pages_ + other.pages_) * 0.7);
    result.cost_ = static_cast<int>((cost_ + other.cost_) * 1.1);

    std::vector<std::string> selected;


    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned>(time(nullptr)));
        seeded = true;
    }

    if (!vec_.empty()) {
        int count1 = 1 + rand() % vec_.size();
        std::vector<int> used;
        for (int i = 0; i < count1; i++) {
            int idx;
            do {
                idx = rand() % vec_.size();
            } while (std::find(used.begin(), used.end(), idx) != used.end());
            used.push_back(idx);

            if (writer_ == other.writer_) {
                selected.push_back(vec_[idx]);
            }
            else {
                selected.push_back(writer_ + vec_[idx]);
            }
        }
    }
    if (!other.vec_.empty()) {
        int count2 = 1 + rand() % other.vec_.size();
        std::vector<int> usedIndexes;
        for (int i = 0; i < count2; i++) {
            int idx;
            do {
                idx = rand() % other.vec_.size();
            } while (std::find(usedIndexes.begin(), usedIndexes.end(), idx) != usedIndexes.end());
            usedIndexes.push_back(idx);
            std::string work;
            if (writer_ == other.writer_) {
                work = other.vec_[idx];
            }
            else {
                work = other.writer_ + other.vec_[idx];
            }
            if (std::find(selected.begin(), selected.end(), work) == selected.end()) {
                selected.push_back(work);
            }
        }
    }
    result.vec_ = selected;
    return result;
}

void Book::print() const {
    std::cout << "[" << writer_ << ", " << title_ << ", (";
    for (size_t i = 0; i < vec_.size(); i++) {
        std::cout << vec_[i];
        if (i < vec_.size() - 1) std::cout << ",";
    }
    std::cout << "), " << rating_ << ", " << pages_ << ", " << cost_ << "]" << std::endl;
}

Shelf::Shelf(size_t capacity)
    : capacity_(capacity) {
}
Shelf::Shelf(Shelf& other)
    : indicator_(other.indicator_), capacity_(other.capacity_) {
}
Shelf::~Shelf() {
    indicator_.clear();
    std::cout << "dtor" << std::endl;
}

size_t Shelf::get_ind() const {
    return indicator_.size();
}
size_t Shelf::get_cap() const {
    return capacity_;
}

void Shelf::add_book(Book* book) {
    if (indicator_.size() >= capacity_) {
        std::cout << "Error! Shelf is full!" << std::endl;
    }
    indicator_.push_back(book);
    std::cout << "Book added!" << std::endl;
}

void Shelf::sort_book() {
    std::sort(indicator_.begin(), indicator_.end());
    std::cout << "Shelf sorted by title" << std::endl;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
