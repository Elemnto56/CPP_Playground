#include <iostream>

#include "pugixml-1.15/src/pugixml.hpp"

int main() {
    pugi::xml_document doc;
    pugi::xml_parse_result res = doc.load_file("library.xml");

    std::cout << res.description() << std::endl;
}