cmake_minimum_required(VERSION 3.6)
project(books)
project(student)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

add_executable(books bookshop.cpp pugixml-1.15/src/pugixml.cpp)
target_link_libraries(books  PRIVATE

        ftxui::component
        ftxui::dom
        ftxui::screen
)
add_executable(student studentManage.cpp)