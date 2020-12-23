#include <CubbyMenu/CubbyMenu.hpp>

#include <iostream>

int main()
{
    auto f{ [](auto const& e) {
        return [e]() { std::cout << e << std::endl; };
    } };

    CubbyMenu::Menu{ "MyMenu" }
        .add_header_ex("Main Menu")
        .add_item_ex("Option 0", f("Option 0 is called."))
        .add_item_ex("Option 1", f("Option 1 is called."))
        .add_item_ex(
            CubbyMenu::Menu{ "Sub Menu" }
                .add_header_ex("Sub Menu")
                .add_item_ex("Option 2.0", f("Option 2.0 is called."))
                .add_item_ex(
                    CubbyMenu::Menu{ "Sub Sub Menu" }
                        .add_header_ex("Sub Sub Menu")
                        .add_item_ex("Option 2.1.0", f("Option 2.1.0 is called."))
                        .add_item_ex("Option 2.1.1", f("Option 2.1.1 is called."))
                        .add_item_ex("Option 2.1.2", f("Option 2.1.2 is called."))
                        .add_item_ex("Option 2.1.3", f("Option 2.1.3 is called."))
                        .add_item_ex("Option 2.1.4", f("Option 2.1.4 is called."))
                )
                .add_item_ex("Option 2.2", f("Option 2.2 is called."))
                .add_item_ex("Option 2.3", f("Option 2.3 is called."))
        )
        .add_item_ex("Option 3", f("Option 3 is called."))
        .print()
        ;
}