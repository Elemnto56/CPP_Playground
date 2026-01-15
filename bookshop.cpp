#include <random>

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "pugixml-1.15/src/pugixml.hpp"

using namespace ftxui;

bool operator==(std::string left, std::string right) {
    if (left.size() != right.size()) return false;

    std::ranges::transform(left, left.begin(), ::toupper);
    std::ranges::transform(right, right.begin(), ::toupper);

    for (int i=0; i < left.size(); i++) if (left[i] != right[i]) return false;

    return true;
}

std::string randomString(int length = 5);
std::string vigenereEncrypt(std::string text, bool encrypt);

int main() {
    pugi::xml_document library; library.load_file("/home/jaydog/CLionProjects/CPP_Playground/library.xml");

    std::vector<std::string> book_names;
    Components books;
    Components book_info;
    int screen_select;
    int tab_select = screen_select = 0;

    for (pugi::xml_node book : library.child("main").child("books").children()) {
        book_names.emplace_back(book.attribute("title").value());

        book_info.push_back(Container::Vertical({
            Renderer([book] {return text(book.attribute("title").value()) | center;}),
            Renderer([] {return separator();}),
            Renderer([book] {
                const std::string author = book.child("author").text().as_string();
                return text("By "+author) | italic | center;
            }),
            Renderer([] {return separator();}),
            Renderer([book]  {
                return paragraph(book.child("synopsis").text().as_string());
            }),
            Collapsible("misc", Container::Vertical({
                Renderer([book] {std::string genre = book.child("genre").text().as_string(); return text("Genre: "+genre);}),
                Renderer([book] {std::string pub = book.child("publication_date").text().as_string();return text("Publication Date: "+pub);})
            }))
        }));
    }

    //region LoginStuff
    int login_pick = 0;
    std::string id_num, password;
    enum AccessLevel {
        PATRON,
        STAFF,
        ADMIN,
        MANAGER
    }; AccessLevel level;
    struct {
        std::string name;
        std::string email;
        std::string password;
        AccessLevel membership = PATRON;

        void clearAll() {
            name = email = password = "";
            membership = PATRON;
        }
    } loginData;
    bool no_id;
    bool bad_pwd = no_id = false;

    auto login_prompts = ScreenInteractive::Fullscreen();

    auto createAccount = Container::Vertical({
        Input(&loginData.name,"Full Name"),
        Input(&loginData.email, "Email"),
        Input(&loginData.password, "Password"),
        Dropdown(std::vector<std::string>{"Patron/Student", "Staff", "Admin", "Manager"}, reinterpret_cast<int*>(&loginData.membership)),
        Button("Create Account", [&] {
            auto mem_list = library.child("main").child("patrons");
            auto new_member = mem_list.append_child("member");
            auto accesstos = [](AccessLevel l) {switch (l) {case PATRON: return "Patron"; case STAFF: return "Staff"; case ADMIN: return "Admin"; case MANAGER: return "Manager";}return "";};

            new_member.append_attribute("id") = randomString();
            new_member.append_child("name").text() = loginData.name;
            new_member.append_child("email").text() = loginData.email;
            new_member.append_child("password").text() = vigenereEncrypt(loginData.password, true);
            new_member.append_child("membership").text() = accesstos(loginData.membership);
            new_member.append_child("join_date").text() = "12-21-25";
            new_member.append_child("expiration_date").text() = "12-21-29";

            if (!library.save_file("/home/jaydog/CLionProjects/CPP_Playground/library.xml", "    ", pugi::format_default, pugi::encoding_utf8)) login_prompts.Exit();

            loginData.clearAll();
            login_pick = 0;
        })
    });

    auto login = Container::Vertical({
        Input(&id_num, "ID Number"),
        Input(&password, "Password"),
        Button("Log In", [&] {
            bool found = false;

            for (pugi::xml_node member : library.child("main").child("patrons").children()) {
                if (member.attribute("id").value() == id_num) {
                    found = true;
                    if (password == vigenereEncrypt(member.child("password").text().as_string(), false)) {
                        std::string memship = static_cast<std::string>(member.child("membership").text().as_string());
                        if (memship == "patron" || memship == "student") {
                            level = PATRON;
                        }
                        login_prompts.Exit();
                    } else {
                        bad_pwd = true;
                        break;
                    }
                }
            }

            if (!found) {
                no_id = true;
            }
        }),
        Renderer([] {return separator();}),
        Button("Create an Account", [&] {login_pick = 1;})
    });

    login |= Modal(Container::Vertical({Renderer([] {return text("Incorrect Password");}), Button("Okay", [&] {bad_pwd = false;})}), &bad_pwd);
    login |= Modal(Container::Vertical({Renderer([] {return text("No Account was found with that ID");}), Button("Okay", [&] {no_id = false;})}), &no_id);

    login_prompts.Loop(Container::Tab({login, createAccount}, &login_pick));
    //endregion

    auto screen = ScreenInteractive::Fullscreen();

    auto book_section = Container::Vertical({
        Container::Horizontal({
            Menu(&book_names, &tab_select, MenuOption::VerticalAnimated()) | size(WIDTH, EQUAL, Terminal::Size().dimx/10),
            Renderer([]() {return separator();}),
            Container::Tab(book_info, &tab_select) | size(WIDTH, EQUAL, Terminal::Size().dimx * 9/10),
        }) | flex,
        Renderer([](){return separator();}),
        Button("Exit", [&] () {screen.Exit();})
    }) | border;

    screen.Loop(Renderer([] {return paragraph("Hello Wolrd");}));
}

std::string vigenereEncrypt(std::string text, bool encrypt) {
    std::string key = "LIBISFUN";
    std::string result;

    if (text.size() > key.size()) {
        int diff = static_cast<int>(text.size() - key.size());
        for (int i=0; i <= diff;i++) {
            key += key[i];
            if (i == 8) i = 0;
        }
    }

    if (!encrypt) {
        for (int i=0;i<text.size();i++) result += static_cast<char>(text[i] - key[i]);
        return result;
    }

    for (int i=0;i<text.size();i++) result += static_cast<char>(text[i] + key[i]);
    return result;
}

std::string randomString(int length) {
    std::vector<char> alphabet;
    std::string result;
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> range(0, 51);


    for (char upper=65;upper<=90;upper++) alphabet.push_back(upper); // ASCII from 65 to 90 is A to Z uppercase
    for (char lower=97;lower<=122;lower++) alphabet.push_back(lower); // ASCII from 97 to 122 is a to z lowercase

    while (length > 0) {
        result += alphabet[range(engine)];
        length--;
    }

    return result;
}