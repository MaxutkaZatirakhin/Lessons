#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Bookmark {
    std::string color;
    std::string material;
    int page;

    Bookmark(std::string col, std::string mat, int pag);
    Bookmark(const Bookmark& other);

    Bookmark& operator++();
    Bookmark& operator--();

};

class Book {
public:
    Book() = default;
    Book(const std::string& writer, const  std::string& title,  const std::vector<std::string>& vec, float rating,  int pages, int cost);
    Book(const Book& other);
    ~Book();

    std::string get_w();
    std::string get_t();
    std::vector<std::string> get_v();
    float get_r();
    int get_p();
    int get_c();

    Bookmark* getBookmark() const;

    void change_cost(int newcost);
    void change_rating_pl();
    void change_rating_min();

    void add_Bookmark(const Bookmark& bookmark);
    void delete_Bookmark();
    void move_forward();   
    void move_back();
    
    Book& operator=(const Book& other);
    Book& operator+(const Book& other);
    Book& operator+=(const Book& other);
    Book operator/(const Book& other);

    void print() const;

private:
    std::string writer_;
    std::string title_;
    std::vector<std::string> vec_;
    float rating_;
    int pages_;
    int cost_;
    Bookmark* bookmark_;
};

class Shelf {
    public:
        Shelf(size_t capacity = 10);
        Shelf(Shelf& other);
        ~Shelf();

        size_t get_ind() const ;
        size_t get_cap() const ;


        void add_book(Book* book);
        void sort_book();

    private:
        std::vector<Book*> indicator_;
        size_t capacity_;
};
