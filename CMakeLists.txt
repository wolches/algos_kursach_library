cmake_minimum_required(VERSION 3.20)
project(algos_kursach)

set(CMAKE_CXX_STANDARD 20)

# Source files
set(SOURCES
    src/main.cpp
    src/app/ui/library_ui.cpp
    src/app/ui/io.cpp
    src/app/service/library_service.cpp
    src/book/book.cpp
    src/book/book_code.cpp
    src/book/book_repository.cpp
    src/reader/reader.cpp
    src/reader/reader_id.cpp
    src/reader/full_name.cpp
    src/reader/reader_repository.cpp
    src/book_issue/book_issue.cpp
    src/book_issue/book_issue_repository.cpp
    src/utils/utils.cpp
    src/utils/short_value_object.cpp
    src/utils/boyer_moore.cpp
    src/utils/hash_map.h
    src/utils/tree_map.h
    src/utils/single_linked_list.h
)

add_executable(algos_kursach ${SOURCES})
