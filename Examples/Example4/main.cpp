#include <CubbyMenu/CubbyMenu.hpp>

#include <iostream>

int main()
{
    CubbyMenu::Menu menu;

    menu.add_item("Option 0", []() { std::cout << "Option 0 is called!\n"; });
    menu.add_item("Option 1", []() { std::cout << "Option 1 is called!\n"; });
    menu.add_item("Option 2", []() { std::cout << "Option 2 is called!\n"; });

    menu.print();
}