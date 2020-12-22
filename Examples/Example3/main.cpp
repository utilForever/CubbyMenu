#include <CubbyMenu/CubbyMenu.hpp>

#include <iostream>

void option0()
{
    std::cout << "Option 0 is called!\n";
}

void option1()
{
    std::cout << "Option 1 is called!\n";
}

void option2()
{
    std::cout << "Option 2 is called!\n";
}

int main()
{
    CubbyMenu::Menu menu;

    menu.add_item("Option 0", &option0);
    menu.add_item("Option 1", &option1);
    menu.add_item("Option 2", &option2);

    menu.print();
}