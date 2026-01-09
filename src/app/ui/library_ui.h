//
// Created for library management system UI
//

#ifndef ALGOS_KURSACH_LIBRARY_UI_H
#define ALGOS_KURSACH_LIBRARY_UI_H

#include "../service/library_service.h"

class library_ui {
private:
    library_service service;
    
    void printMenu();

    void printReaderInfo(const reader_info &r);
    void viewReadersPages(const std::vector<reader_info> &readers);

    void handleAddReader();
    void handleEditReader();
    void handleRemoveReader();
    void handleViewAllReaders();
    void handleClearReaders();
    void handleSearchReaderById();
    void handleSearchReader();

    void printBookInfo(const book_info &b);
    void viewBookPages(const std::vector<book_info> &books);

    void handleAddBook();
    void handleEditBook();
    void handleRemoveBook();
    void handleViewAllBooks();
    void handleClearBooks();
    void handleSearchBookByCode();
    void handleSearchBook();
    
    void handleIssueBook();
    void handleReturnBook();
    
public:
    library_ui();
    int run();
};

#endif //ALGOS_KURSACH_LIBRARY_UI_H
