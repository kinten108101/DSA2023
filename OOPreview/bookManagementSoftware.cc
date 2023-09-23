#include <functional>
#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;

class Book
{
private:
    char* title;
    char* authors;
    int publishingYear;

public:
    Book(): title(nullptr), authors(nullptr), publishingYear(0)
    {
    }

    Book(const char* title, const char* authors, int publishingYear)
    : title((char*)title), authors((char*)authors), publishingYear(publishingYear)
    {
    }

    Book(const Book &book)
    : title(book.title), authors(book.authors), publishingYear(book.publishingYear)
    {
    }
    
    void setTitle(const char* title)
    {
        this->title = (char*) title;
    }

    void setAuthors(const char* authors)
    {
        this->authors = (char*) authors;
    }

    void setPublishingYear(int publishingYear)
    {
        this->publishingYear = publishingYear;
    }

    char* getTitle() const
    {
        return this->title;
    }

    char* getAuthors() const
    {
        return this->authors;
    }

    int getPublishingYear() const
    {
        return this->publishingYear;
    }

    ~Book()
    {
    }

    void printBook(){
        printf("%s\n%s\n%d", this->title, this->authors, this->publishingYear);
    }
};

int assert(std::function<void()> callback) {
   static int i = 0;
   std::cout << "Case" << " " << ++i << std::endl;
   callback();
   std::cout << endl;
   return 0;
}

int main() {
   assert([]() {
      Book book1("Giai tich 1","Nguyen Dinh Huy",2000);
      book1.printBook();
   });
   assert([]() {
      Book book1("Giai tich 1","Nguyen Dinh Huy",2000);
      Book book2 = book1;
      book2.printBook();
   });
   assert([]() {
      Book book1("Giai tich 1","Nguyen Dinh Huy",2000);
      Book book2 = book1;
      book1.setAuthors("Nguyen Thi Xuan Anh");
      book2.printBook();
   });
   assert([]() {
      Book book1("Giai tich 1","Nguyen Dinh Huy",2000);
      book1.setTitle("Giai tich 2");
      book1.setAuthors("Nguyen Thi Xuan Anh");
      book1.printBook();
   });

    return 0;
}