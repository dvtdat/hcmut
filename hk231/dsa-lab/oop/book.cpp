#include <bits/stdc++.h>

using namespace std;

class Book
{
private:
    char* title;
    char* authors;
    int publishingYear;

public:
    Book()
    {
        publishingYear = 0;
        title = authors = nullptr;
    }

    Book(const char* title, const char* authors, int publishingYear)
    {
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
        this->authors = new char[strlen(authors) + 1];
        strcpy(this->authors, authors);

        this->publishingYear = publishingYear;
    }

    Book(const Book &book)
    {
        this->title = new char[strlen(book.getTitle()) + 1];
        strcpy(this->title, book.getTitle());
        this->authors = new char[strlen(book.getAuthors()) + 1];
        strcpy(this->authors, book.getAuthors());

        this->publishingYear = book.getPublishingYear();
    }
    
    void setTitle(const char* title)
    {
        this->title = new char[strlen(title) + 1];
        strcpy(this->title, title);
    }

    void setAuthors(const char* authors)
    {
        this->authors = new char[strlen(authors) + 1];
        strcpy(this->authors, authors);
    }

    void setPublishingYear(int publishingYear)
    {
        this->publishingYear = publishingYear;
    }

    char* getTitle() const
    {
        return title;
    }

    char* getAuthors() const
    {
        return authors;
    }

    int getPublishingYear() const
    {
        return publishingYear;
    }

    ~Book()
    {
        delete title;
        delete authors;
    }

    void printBook() {
        printf("%s\n%s\n%d", this->title, this->authors, this->publishingYear);
    }
};

int main() {
    Book book1("Giai tich 1", "Nguyen Dinh Huy", 2000);
    Book book2 = book1;
    book1.printBook();
}