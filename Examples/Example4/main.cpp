#include <CubbyMenu/CubbyMenu.hpp>

#include <iostream>

int main()
{
    CubbyMenu::Menu menu;

    menu.add_item("Option 0", [](std::vector<std::string> const&) { std::cout << "Option 0 is called!\n"; });
    menu.add_item("Option 1", [](std::vector<std::string> const&) { std::cout << "Option 1 is called!\n"; });
    menu.add_item("Option 2", [](std::vector<std::string> const&) { std::cout << "Option 2 is called!\n"; });

    menu.print();
}