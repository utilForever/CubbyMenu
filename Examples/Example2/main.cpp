#include <CubbyMenu/CubbyMenu.hpp>

int main()
{
    CubbyMenu::Menu menu;
    menu.add_header("Header");

    menu.add_item("Option 0");
    menu.add_item("Option 1");
    menu.add_item("Option 2");

    menu.print();
}