#include "Header_laba_3.h"
#include <iostream>
#include <locale>
#include <cstdlib>  
#include <ctime>    

int main()
{
    std::setlocale(LC_ALL, "Russian");

    Book b1("À", "D",  { "à", "á", "â", "ã", "ä" }, 5.4,  25, 100);
    Book b2("À", "F",  { "à", "ì", "í", "î", "ï" }, 6.5, 50, 100);
    b1.change_cost(1000);
    b1.change_rating_pl();

    Book result = b1 += b2;
    std::cout << "b1 += b2 = " << std::endl;
    result.print();

    Shelf shelf(5);
    shelf.add_book(&b1);
    shelf.add_book(&b2);
    shelf.sort_book();

    Bookmark mark("green", "paper", 20);
    b1.add_Bookmark(mark);
    b1.move_forward();
    b1.move_forward();
    b1.move_back();

    return 0;
}