#include <CubbyMenu/CubbyMenu.hpp>

#include <iostream>

int main()
{
    auto f{ [](auto fo) {
        return [fo](std::vector<std::string> const& args) {
            if (std::size(args) < 3)
            {
                std::cout << "Number of arguments must be at least 3\n";

                return;
            }

            try
            {
                std::invoke(fo, std::stoi(args[1]), std::stoi(args[2]));
            }
            catch (std::exception const& e)
            {
                std::cout << e.what() << std::endl;
            }
        };
    } };

    CubbyMenu::Menu{ "MyMenu" }
        .add_header_ex("Main Menu")
        .add_item_ex(
            "Arguments Test",
            [](std::vector<std::string> const& args) { 
                for (auto i{ 0u }; i < std::size(args); ++i)
                    std::cout << "arg " << i << ": " << args[i] << std::endl;
            }
        )
        .add_item_ex("Add(int + int)", f([](auto a, auto b) { std::cout << a << " + " << b << " = " << a + b << '\n';}))
        .add_item_ex("Sub(int - int)", f([](auto a, auto b) { std::cout << a << " - " << b << " = " << a - b << '\n';}))
        .add_item_ex("Mul(int * int)", f([](auto a, auto b) { std::cout << a << " * " << b << " = " << a * b << '\n';}))
        .add_item_ex("Div(int / int)", f([](auto a, auto b) { std::cout << a << " / " << b << " = " << a / b << '\n';}))
        .print()
        ;
}