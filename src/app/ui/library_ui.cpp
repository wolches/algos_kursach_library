//
// Created for library management system UI
//

#include "library_ui.h"
#include <iostream>
#include <string>

#include "io.h"

library_ui::library_ui() : service() {
}

void library_ui::printMenu() {
    printString(L"=== Библиотечная информационная система ===");
    printString(L"");
    printString(L"Работа с читателями:");
    printString(L"  1. Регистрация нового читателя");
    printString(L"  2. Редактирование данных читателя");
    printString(L"  3. Снятие с обслуживания читателя");
    printString(L"  4. Просмотр всех зарегистрированных читателей");
    printString(L"  5. Очистка данных о читателях");
    printString(L"  6. Поиск читателя по номеру читательского билета");
    printString(L"  7. Полнотекстовый поиск читателя");
    printString(L"");
    printString(L"Работа с книгами:");
    printString(L"  8. Добавление новой книги");
    printString(L"  9. Редактирование сведений о книге");
    printString(L" 10. Удаление сведений о книге");
    printString(L" 11. Просмотр всех имеющихся книг");
    printString(L" 12. Очистка данных о книгах");
    printString(L" 13. Поиск книги по шифру");
    printString(L" 14. Полнотекстовый поиск книги");
    printString(L"");
    printString(L"Работа с выдачей книг:");
    printString(L" 15. Регистрация выдачи экземпляра книги читателю");
    printString(L" 16. Регистрация приема экземпляра книги от читателя");
    printString(L"");
    printString(L" 0. Выход");
    printString(L"");
}


int library_ui::run() {
    while (true) {
        printMenu();
        int choice = readInt(L"Выберите действие:");
        switch (choice) {
            case 1: handleAddReader(); break;
            case 2: handleEditReader(); break;
            case 3: handleRemoveReader(); break;
            case 4: handleViewAllReaders(); break;
            case 5: handleClearReaders(); break;
            case 6: handleSearchReaderById(); break;
            case 7: handleSearchReader(); break;
            case 8: handleAddBook(); break;
            case 9: handleEditBook(); break;
            case 10: handleRemoveBook(); break;
            case 11: handleViewAllBooks(); break;
            case 12: handleClearBooks(); break;
            case 13: handleSearchBookByCode(); break;
            case 14: handleSearchBook(); break;
            case 15: handleIssueBook(); break;
            case 16: handleReturnBook(); break;
            case 0:
                std::wcout << L"Выход из программы." << std::endl;
                return 0;
            default:
                std::wcout << L"Неверный выбор. Попробуйте снова." << std::endl;
        }
    }
}

void library_ui::handleAddReader() {
    printString(L"=== Регистрация нового читателя ===");
    try {
        std::wstring readerAccess = readString(L"Тип читательского билета (формат: А / Ч / В): ");
        short regYear = readInt(L"Год регистрации (формат: [NN]NN): ");
        std::wstring fullName = readString(L"ФИО (формат: Фамилия Имя Отчество): ");
        short yearOfBirth = readInt(L"Год рождения (формат NNNN): ");
        std::wstring address = readString(L"Адрес: ");
        std::wstring counterparty = readString(L"Место работы: ");
        service.registerReader(readerAccess, regYear, fullName, yearOfBirth, address, counterparty);
        printString(L"Читатель успешно зарегистрирован!");
    } catch (const std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}

void library_ui::handleEditReader() {
    printString(L"=== Редактирование данных читателя ===");
    try {
        std::wstring readerId = readString(L"Читательский билет (формат: (А / Ч / В)NNNN-NN): ");
        std::wstring access = readString(L"Новый тип читательского билета (формат: А / Ч / В): ");
        std::wstring fullName = readString(L"ФИО (формат: Фамилия Имя Отчество): ");
        short yearOfBirth = readInt(L"Год рождения (формат NNNN): ");
        std::wstring address = readString(L"Адрес: ");
        std::wstring counterparty = readString(L"Место работы: ");
        service.editReader(readerId, access, fullName, yearOfBirth, address, counterparty);
        printString(L"Читатель успешно зарегистрирован!");
    } catch (const std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}

void library_ui::handleRemoveReader() {
    printString(L"=== Снятие с обслуживания читателя ===");
    try {
        std::wstring readerId = readString(L"Номер читательского билета: ");
        service.removeReader(readerId);
        printString(L"Читатель успешно удален!");
    } catch (const std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}

void library_ui::handleViewAllReaders() {
    printString(L"=== Просмотр всех зарегистрированных читателей ===");
    try {
        auto readers = service.getAllReaders();
        if (readers.empty()) {
            printString(L"Читатели не найдены.");
            return;
        }
        viewReadersPages(readers);
    } catch (const std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}

void library_ui::printReaderInfo(const reader_info &r) {
    printString(L"Номер билета: " + r.readerId);
    printString(L"ФИО: " + r.fullName);
    printString(L"Год рождения: " + std::to_wstring(r.yearOfBirth));
    printString(L"Адрес: " + r.address);
    printString(L"Место работы: " + r.counterparty);
    if (!r.issuedBookCodes.empty()) {
        printString(L"Книги на руках: ");
        for (size_t j = 0; j < r.issuedBookCodes.size(); j++) {
            printString(L"  - " + r.issuedBookCodes[j]);
        }
    }
}

void library_ui::viewReadersPages(const std::vector<reader_info> &readers) {
    int page = 0;
    int pageSize = 10;
    int total = readers.size();
    while (true) {
        int fromOffset = page * pageSize;
        int toOffset = std::min(fromOffset + pageSize, total);
        printString(
            L"=== Найденные читатели (Записи: "
            + std::to_wstring(fromOffset + 1) + L" - " + std::to_wstring(toOffset)
            + L" / " + std::to_wstring(total)
            + L") ==="
        );
        for (int i = fromOffset; i < toOffset; i++) {
            const reader_info &r = readers[i];
            printString(L"[№ " + std::to_wstring(i + 1) + L".]");
            printReaderInfo(r);
        }
        printString(L"");
        printString(L"Работа с читателями:");
        printString(L"  0. Выход");
        printString(L"  1. Просмотр предыдущей страницы");
        printString(L"  2. Просмотр следующей страницы");
        int action = readInt(L"Введите действие:");
        switch (action) {
            case 0: {
                return;
            }
            case 1: {
                if (fromOffset > 0) {
                    page = page - 1;
                    break;
                }
            };
            case 2: {
                if (toOffset < total) {
                    page = page + 1;
                    break;
                }
            };
            default: {
                break;
            }
        }
    }
}

void library_ui::handleClearReaders() {
    printString(L"=== Очистка данных о читателях ===");
    printString(L"Также будет очищена история выдачи книг");
    try {
        std::wstring confirm = readString(L"Вы уверены? (yYдД/nNнН):");
        if (confirm == L"y" || confirm == L"Y" || confirm == L"д" || confirm == L"Д") {
            service.clearReaders();
            service.clearIssues();
            std::wcout << L"Данные о читателях очищены!" << std::endl;
        }
    } catch (const std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}

void library_ui::handleSearchReaderById() {
    printString(L"=== Поиск читателя по номеру билета ===");
    try {
        std::wstring readerId = readString(L"Номер читательского билета: ");
        auto optReader = service.findReaderById(readerId);
        if (optReader.has_value()) {
            auto r = optReader.value();
            printReaderInfo(r);
        } else {
            printString(L"Читатель не найден.");
        }
    } catch (const std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}

void library_ui::handleSearchReader() {
    printString(L"=== Поиск читателей ===");
    try {
        std::wstring nameFragment = readString(L"Введите запрос:");
        auto readers = service.fullTextReaderSearch(nameFragment);
        if (readers.empty()) {
            std::wcout << L"Читатели не найдены." << std::endl;
            return;
        }
        viewReadersPages(readers);
    } catch (const std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}

void library_ui::handleAddBook() {
    printString(L"=== Добавление новой книги ===");
    try {
        short categoryId = readInt(L"Номнр категории (формат ###):");
        short bookId = readInt(L"Номер книги (формат ###):");
        std::wstring name = readString(L"Название: ");
        std::wstring author = readString(L"Автор: ");
        std::wstring publisher = readString(L"Издательство: ");
        short year = readInt(L"Год издания: ");
        short totalCopies = readInt(L"Количество копий:");
        service.addBook(categoryId, bookId, name, author, publisher, year, totalCopies);
        printString(L"Книга успешно добавлена!");
    } catch (const std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}

void library_ui::handleEditBook() {
    printString(L"=== Редактирование книги ===");
    try {
        std::wstring bookId = readString(L"Шифр книги (формат ###.###):");
        std::wstring name = readString(L"Название: ");
        std::wstring author = readString(L"Автор: ");
        std::wstring publisher = readString(L"Издательство: ");
        short year = readInt(L"Год издания: ");
        short totalCopies = readInt(L"Количество копий:");
        service.editBook(bookId, name, author, publisher, year, totalCopies);
        printString(L"Книга успешно обновлена!");
    } catch (const std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}

void library_ui::handleRemoveBook() {
    printString(L"=== Удаление сведений о книге ===");
    try {
        std::wstring code = readString(L"Шифр книги: ");
        service.removeBook(code);
        printString(L"Книга успешно удалена!");
    } catch (const std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}

void library_ui::printBookInfo(const book_info &b) {
    printString(L"Шифр: " + b.code);
    printString(L"Название: " + b.name);
    printString(L"Автор(ы): " + b.author);
    printString(L"Издательство: " + b.publisher);
    printString(L"Год издания: " + std::to_wstring(b.year));
    printString(L"Всего экземпляров: " + std::to_wstring(b.totalCopies));
    printString(L"В наличии: " + std::to_wstring(b.available));
    if (!b.issuedToReaders.empty()) {
        printString(L"Выдано читателям: ");
        for (size_t i = 0; i < b.issuedToReaders.size(); i++) {
            printString(std::to_wstring(i + 1) + L". " // 1.
                + b.issuedToReaders[i].first // A0000-00
                + L" (" + b.issuedToReaders[i].second + L")" // (Ааа Ббб Ввв)
            );
        }
    }
    printString(L"");
}

void library_ui::viewBookPages(const std::vector<book_info> &books) {
    int page = 0;
    int pageSize = 10;
    int total = books.size();
    while (true) {
        int fromOffset = page * pageSize;
        int toOffset = std::min(fromOffset + pageSize, total);
        printString(
            L"=== Найденные книги (Записи: "
            + std::to_wstring(fromOffset + 1) + L" - " + std::to_wstring(toOffset)
            + L" / " + std::to_wstring(total)
            + L") ==="
        );
        for (int i = fromOffset; i < toOffset; i++) {
            const book_info &b = books[i];
            printString(L"[№ " + std::to_wstring(i + 1) + L".]");
            printBookInfo(b);
        }
        printString(L"");
        printString(L"Работа с книгами:");
        printString(L"  0. Выход");
        printString(L"  1. Просмотр предыдущей страницы");
        printString(L"  2. Просмотр следующей страницы");
        int action = readInt(L"Введите действие:");
        switch (action) {
            case 0: {
                return;
            }
            case 1: {
                if (fromOffset > 0) {
                    page = page - 1;
                    break;
                }
            };
            case 2: {
                if (toOffset < total) {
                    page = page + 1;
                    break;
                }
            };
            default: {
                break;
            }
        }
    }
}

void library_ui::handleViewAllBooks() {
    printString(L"=== Все имеющиеся книги ===");
    try {
        auto books = service.getAllBooks();
        if (books.empty()) {
            std::wcout << L"Книги не найдены." << std::endl;
            return;
        }
        viewBookPages(books);
    } catch (std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}

void library_ui::handleClearBooks() {
    printString(L"=== Очистка данных о книгах ===");
    printString(L"Также будет очищена история выдачи книг!");
    try {
        std::wstring confirm = readString(L"Вы уверены? (yYдД/nNнН):");
        if (confirm == L"y" || confirm == L"Y" || confirm == L"д" || confirm == L"Д") {
            service.clearBooks();
            service.clearIssues();
            std::wcout << L"Данные о книгах очищены!" << std::endl;
        }
    } catch (const std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}

void library_ui::handleSearchBookByCode() {
    printString(L"=== Поиск книги по шифру ===");
    try {
        std::wstring code = readString(L"Шифр книги: ");
        auto optBook = service.findBookByCode(code);
        if (optBook.has_value()) {
            printBookInfo(optBook.value());
        } else {
            printString(L"Книга не найдена.");
        }
    } catch (const std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}

void library_ui::handleSearchBook() {
    std::wcout << std::endl << L"=== Поиск книги ===" << std::endl;
    try {
        std::wstring fragment = readString(L"Введите строку поиска: ");
        auto books = service.fullTextBookSearch(fragment);
        if (books.empty()) {
            printString(L"Книги не найдены.");
            return;
        }
        viewBookPages(books);
    } catch (const std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}

void library_ui::handleIssueBook() {
    printString(L"=== Регистрация выдачи книги ===");
    try {
        std::wstring bookCode = readString(L"Шифр книги: ");
        std::wstring readerId = readString(L"Номер читательского билета: ");
        service.issueBook(bookCode, readerId);
        printString(L"Книга успешно выдана!");
    } catch (const std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}

void library_ui::handleReturnBook() {
    printString(L"=== Регистрация приема книги ===");
    try {
        std::wstring bookCode = readString(L"Шифр книги: ");
        std::wstring readerId = readString(L"Номер читательского билета: ");
        service.returnBook(bookCode, readerId);
        printString(L"Книга успешно принята!");
    } catch (const std::exception &e) {
        printString(L"Ошибка: ");
        printString(toWideString(e.what()));
    }
}
