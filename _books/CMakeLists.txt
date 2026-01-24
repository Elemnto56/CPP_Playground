cmake_minimum_required(VERSION 3.6)
project(books)

set(CMAKE_CXX_STANDARD 20)

add_executable(books bookshop.cpp pugixml-1.15/src/pugixml.cpp)
target_link_libraries(books  PRIVATE

        ftxui::component
        ftxui::dom
        ftxui::screen
)
