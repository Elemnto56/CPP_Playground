#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "pugixml-1.15/src/pugixml.hpp"

using namespace ftxui;
int main() {
    pugi::xml_document library; library.load_file("/home/jaydog/CLionProjects/CPP_Playground/library.xml");

    Components books;
    Components book_info = {Container::Vertical({
        Renderer([]() {return text("No book to display") | italic | center;})
    })};
    int i;
    int tab_select = i = 0;

    for (pugi::xml_node book : library.child("root").children()) {
        books.push_back(Button(book.attribute("name").value(), [&]{tab_select = 1;}));

        book_info.push_back(Container::Vertical({
            Renderer([book] {return text(book.attribute("name").value()) | center;}),
            Renderer([] {return separator();}),
            Renderer([book] {
                const std::string author = book.child("Author").text().as_string();
                return text("By "+author) | italic | center;
            }),
            Renderer([] {return separator();}),
            Renderer([book]  {
                return paragraph(book.child("Synopsis").text().as_string());
            }),
            Collapsible("misc", Container::Vertical({
                Renderer([book] {std::string genre = book.child("Genre").text().as_string(); return text("Genre: "+genre);}),
                Renderer([book] {std::string pub = book.child("Published").text().as_string();return text("Publication Date: "+pub);})
            }))
        }));
        ++i;
    }

    auto screen = ScreenInteractive::Fullscreen();

    auto layout = Container::Vertical({
        Container::Horizontal({
            Container::Vertical({
                books
            }) | size(WIDTH, EQUAL, Terminal::Size().dimx/4),
            Renderer([]() {return separator();}),
            Container::Tab(book_info, &tab_select) | size(WIDTH, EQUAL, Terminal::Size().dimx * 3/4)
        }) | flex,
        Renderer([](){return separator();}),
        Button("Exit", [&] () {screen.Exit();})
    }) | border;

    screen.Loop(layout);
}